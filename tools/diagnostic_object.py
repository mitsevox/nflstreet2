"""Preserve native bytes/relocations in a private, independently positioned comparison fragment."""
import math
import struct
import source_build as sb


# Bytes a D-form load or store moves, by primary opcode: lwz lwzu lbz lbzu stw stwu stb stbu lhz lhzu
# lha lhau sth sthu lfs lfsu lfd lfdu stfs stfsu stfd stfdu; lmw and stmw (46, 47) move four bytes
# for each register from rD to r31 (access_width). Any other instruction that carries a low-half
# relocation (addi, ori) takes the address.
ACCESS_WIDTH = {32: 4, 33: 4, 34: 1, 35: 1, 36: 4, 37: 4, 38: 1, 39: 1, 40: 2, 41: 2, 42: 2, 43: 2, 44: 2, 45: 2,
                46: None, 47: None, 48: 4, 49: 4, 50: 8, 51: 8, 52: 4, 53: 4, 54: 8, 55: 8}
STORES = {36, 37, 38, 39, 44, 45, 47, 52, 53, 54, 55}
# The update forms, which also write the accessed address to rA: lwzu lbzu stwu stbu lhzu lhau sthu lfsu lfdu stfsu
# stfdu. Their indexed forms (lwzux, ...) are X-form instructions with the base in rA, which base_uses refuses.
UPDATES = {33, 35, 37, 39, 41, 43, 45, 49, 51, 53, 55}
VOLATILE = set(range(0, 13))  # r0 and r3-r12 do not survive a call (r1, r2 are never a pool base).
BLR = 0x4E800020


def access_width(word):
    opcode = word >> 26
    return 4 * (32 - ((word >> 21) & 31)) if opcode in (46, 47) else ACCESS_WIDTH[opcode]


def stores_register(word, register):
    """Whether a multiple or string store, through any rA, can write `register` to memory: stmw stores
    rS..r31, stswi stores rS onward for NB bytes (32 when NB is 0), wrapping from r31 to r0, and
    stswx stores a length held in XER, which cannot be known here."""
    opcode, source = word >> 26, (word >> 21) & 31
    if opcode == 47:
        return source <= register
    extended = (word >> 1) & 0x3FF
    if opcode == 31 and extended == 725:
        count = (word >> 11) & 31 or 32
        return (register - source) % 32 < (count + 3) // 4
    return opcode == 31 and extended == 661


def base_uses(code, at, register, strict=False):
    """The (displacement, width) of each D-form access through `register` after the instruction at
    `at` set it to an address, until an instruction overwrites it, a call clobbers it (a volatile
    register) or the function returns. None when the address is used any other way (passed on,
    indexed), or when a branch, or a call that a callee-saved base survives, ends the straight line
    while the register still holds the address: later loads through it cannot be followed. With
    `strict` (register_base), storing the address itself to memory is also None, as it is passed
    on: a store of the register, or a stmw, stswi or stswx through any register whose range can
    cover it (stores_register). So is an update form (lwzu, stwu, ...) through it, which moves the
    register to the accessed address so that later displacements no longer count from the address."""
    uses = []
    for position in range(at + 4, len(code) - 3, 4):
        word = struct.unpack_from('>I', code, position)[0]
        opcode, target, base = word >> 26, (word >> 21) & 31, (word >> 16) & 31
        if strict and stores_register(word, register):
            return None
        if opcode in ACCESS_WIDTH and base == register:
            if strict and (opcode in UPDATES or opcode in STORES and target == register):
                return None
            displacement = word & 0xFFFF
            uses.append((displacement - 0x10000 if displacement & 0x8000 else displacement, access_width(word)))
            if opcode not in STORES and (target == register or opcode == 46 and target <= register):
                break
            continue
        if word == BLR:
            break
        if opcode == 18 and word & 1 and register in VOLATILE:  # bl clobbers a volatile base.
            break
        if opcode in (16, 18, 19):  # Any other branch: the address may still be used beyond it.
            return None
        if register in ((word >> 16) & 31, (word >> 11) & 31) or target == register:
            return None
    return uses


# R_PPC_ADDR16_LO, and R_PPC_ADDR16_HI/_HA: the low and high halves of an address formed in a register (lis/addi).
ADDRESS_LOW = 4
ADDRESS_HIGH = (5, 6)


def register_base(code, at, value, size):
    """Whether the R_PPC_ADDR16_LO at byte `at` of `code` forms a base register whose every use lands
    in the compiled section's [0, size): the relocation must sit in the low half of an addi, and
    every displacement load or store through the register it sets must lie inside the section,
    until a load redefines the register, a call clobbers it (a volatile register) or the function
    returns. GCC forms object+0x10000 for an object
    larger than 32 KiB and addresses its fields with negative displacements, so such a base lies
    past the section's end. A low half on a load or store is the accessed address itself, not a
    base, and a base that is passed on, stored (also by an stmw, stswi or stswx through any register
    whose range can cover it), indexed, moved by an update form, overwritten any
    other way or live across a branch, or a callee-saved base live past a call, cannot be bounded."""
    if at % 4 != 2 or not 0 <= at - 2 <= len(code) - 4:
        return False
    word = struct.unpack_from('>I', code, at - 2)[0]
    if word >> 26 != 14:  # addi rD, rA, symbol@l
        return False
    uses = base_uses(code, at - 2, (word >> 21) & 31, strict=True)
    return bool(uses) and all(0 <= value + d and value + d + w <= size for d, w in uses)


def fragment(native, section, offset, size, target_start, functions, targets, placements, externals, output, target_sections,
             storage=None):
    sections, symbols = sb.read_elf(native)
    referenced = {}
    relocations = []
    small_references = set()
    native_relocations = []
    for relocation_section in sections:
        if relocation_section['type'] == 9 and relocation_section['info'] == section['index']:
            raise ValueError('Comparison requires explicit-addend PowerPC relocations')
        if relocation_section['type'] != 4 or relocation_section['info'] != section['index']:
            continue
        for at in range(relocation_section['offset'], relocation_section['offset'] + relocation_section['size'], 12):
            position, info, addend = struct.unpack_from('>IIi', native, at)
            if offset <= position < offset + size:
                native_relocations.append((position, info, addend))
    # Only code holds a register base (register_base); a data fragment's offsets stay inside the section.
    code = section['data'][offset:offset + size] if section['flags'] & sb.SHF_EXECINSTR else b''
    for position, info, addend in native_relocations:
        index, kind = info >> 8, info & 255
        if not 0 < index <= len(symbols):
            raise ValueError('Invalid native relocation symbol')
        symbol = symbols[index - 1]
        name = symbol['name']
        value = symbol['value'] + addend
        if symbol['shndx'] == sb.SHN_COMMON:
            # COMMON storage has no section; only an evidenced storage address locates it.
            if storage is None or index - 1 not in storage:
                raise ValueError(f'Comparison common symbol {name} lacks an evidenced storage address')
            address = storage[index - 1] + addend
        elif symbol['shndx'] == sb.SHN_UNDEF:
            neutral = sb.NEUTRAL.fullmatch(name)
            if name in externals:
                address = externals[name] + addend
            elif neutral:
                address = int(neutral[1], 16) + addend
            else:
                raise ValueError(f'Unresolved comparison reference {name}')
        elif symbol['shndx'] == sb.SHN_ABS:
            address = value
        else:
            owned = next(s for s in sections if s['index'] == symbol['shndx'])
            if owned['flags'] & sb.SHF_EXECINSTR:
                if owned['index'] == section['index'] and offset <= value < offset + size:
                    address = target_start + value - offset
                else:
                    functions_at = [f for f in functions.values() if f['shndx'] == owned['index']
                                    and f['value'] <= value < f['value'] + f['size']]
                    if len(functions_at) != 1 or functions_at[0]['name'] not in targets:
                        raise ValueError('Same-file code reference lacks target identity')
                    function = functions_at[0]
                    a, b = targets[function['name']]
                    address = a + value - function['value']
                    if not a <= address < b:
                        raise ValueError('Same-file code reference exceeds evidenced target function')
            elif storage is not None and owned['type'] == sb.SHT_NOBITS:
                # With a storage map, uninitialized objects resolve individually, not by section.
                mapped = [i for i in storage if symbols[i]['shndx'] == owned['index']
                          and symbols[i]['value'] <= value < symbols[i]['value'] + symbols[i]['size']]
                if len(mapped) != 1:
                    raise ValueError('Uninitialized data reference lacks an evidenced storage address')
                address = storage[mapped[0]] + value - symbols[mapped[0]]['value']
            else:
                placement = placements.get(owned['name'])
                extent = None if placement is None else placement['end'] - placement['start']
                # An offset outside the section is accepted only for a register base whose uses all
                # land in the compiled section, placed whole; a high half needs such a low half on
                # the same symbol and addend.
                if extent is None or not (0 <= value < extent or owned['size'] <= extent and (
                        kind == ADDRESS_LOW and register_base(code, position - offset, value, owned['size'])
                        or kind in ADDRESS_HIGH and any(
                            other >> 8 == index and other & 255 == ADDRESS_LOW and more == addend
                            and register_base(code, at - offset, value, owned['size'])
                            for at, other, more in native_relocations))):
                    raise ValueError('Same-file data reference lacks target placement')
                address = placement['start'] + value
        if not 0 <= address <= 0xFFFFFFFF:
            raise ValueError('Comparison relocation exceeds target address space')
        alias = f'__comparison_reference_{address:08X}'
        referenced[alias] = address
        if kind in (32, 106, 107, 109, 116):
            small_references.add(alias)
        relocations.append((position-offset, kind, alias))
    # An isolated comparison starts at its evidenced target address, which need not be an
    # original section boundary. Prevent the linker from inserting a prefix before its bytes.
    fragment_section = dict(section, size=size, data=section['data'][offset:offset+size],
                            align=math.gcd(max(section['align'], 1), target_start))
    symbols_out = [{'name': 'function' if section['flags'] & sb.SHF_EXECINSTR else 'data',
                    'value': 0, 'size': size, 'shndx': 1, 'type': 2 if section['flags'] & sb.SHF_EXECINSTR else 1}]
    symbols_out += [{'name': name, 'value': 0 if name in small_references else address,
                     'shndx': sb.SHN_UNDEF if name in small_references else sb.SHN_ABS}
                    for name, address in referenced.items()]
    reference_objects, reference_script = [], []
    for target in target_sections:
        names = {name: referenced[name] for name in small_references
                 if target['start'] <= referenced[name] < target['end']}
        if not names:
            continue
        if target['output'] not in ('.sdata', '.sdata2', '.sbss', '.sbss2'):
            raise ValueError('Small-data relocation lacks a small-data target section')
        if section['name'] == target['output']:
            raise ValueError('Small-data-relative initialized data comparison is unsupported')
        reference = output.with_name('reference' + target['output'] + '.o')
        size = target['end']-target['start']
        reference_section = {'name': target['output'], 'flags': sb.SHF_ALLOC | sb.SHF_WRITE,
                             'size': size, 'align': 1, 'type': sb.SHT_NOBITS if target['kind']=='bss' else sb.SHT_PROGBITS}
        if target['kind'] != 'bss':
            reference_section['data'] = target['contents']
        sb.write_object(reference, [reference_section],
                        [{'name': name, 'value': address-target['start'], 'shndx': 1} for name, address in names.items()])
        reference_objects.append(reference)
        reference_script.append(f"{target['output']} 0x{target['start']:08X} : {{ *({target['output']}) }}")
        small_references -= set(names)
    if small_references:
        raise ValueError('Small-data relocation is outside the target')
    sb.write_object(output, [fragment_section], symbols_out)
    if not relocations:
        return symbols_out[0]['name'], reference_objects, reference_script
    # Append native relocation records with remapped symbol indices and offsets.
    # The instruction/data payload remains exactly the compiler-produced fragment.
    data = bytearray(output.read_bytes())
    shoff = struct.unpack_from('>I', data, 32)[0]
    _, count, strings_index = struct.unpack_from('>HHH', data, 46)
    headers = [list(struct.unpack_from('>IIIIIIIIII', data, shoff+i*40)) for i in range(count)]
    parsed, _ = sb.read_elf(data)
    symtab = next(s['index'] for s in parsed if s['type'] == sb.SHT_SYMTAB)
    data = data[:shoff]
    string_header = headers[strings_index]
    strings = data[string_header[4]:string_header[4]+string_header[5]]
    name_offset = len(strings)
    strings += ('.rela' + section['name']).encode('ascii') + b'\0'
    string_header[4], string_header[5] = len(data), len(strings)
    data += strings + b'\0' * (-len(strings) % 4)
    relocation_offset = len(data)
    first_user_symbol = 3  # null, file, section
    indices = {s['name']: first_user_symbol+i for i, s in enumerate(symbols_out)}
    for position, kind, alias in relocations:
        data += struct.pack('>IIi', position, (indices[alias] << 8) | kind, 0)
    headers.append([name_offset, 4, 0, 0, relocation_offset, len(relocations)*12, symtab, 1, 4, 12])
    struct.pack_into('>I', data, 32, len(data))
    struct.pack_into('>H', data, 48, len(headers))
    for header in headers:
        data += struct.pack('>IIIIIIIIII', *header)
    output.write_bytes(data)
    return symbols_out[0]['name'], reference_objects, reference_script
