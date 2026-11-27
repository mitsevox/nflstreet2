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
# The loads whose rD is a general register (lwz lwzu lbz lbzu lhz lhzu lha lhau lmw): only these overwrite a
# base. lfs lfsu lfd lfdu (48-51) load a floating-point register, so `lfs f31,0(r3)` leaves r31 alone.
GPR_LOADS = {32, 33, 34, 35, 40, 41, 42, 43, 46}
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
            if opcode in GPR_LOADS and (target == register or opcode == 46 and target <= register):
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


def flow_uses(code, at, register, branches=None):
    """register_base's uses of the address the instruction at `at` sets in `register`, following
    the function's branches: every path from `at` is walked (each instruction once) while the
    register still holds the address, with base_uses(strict=True)'s rules for each instruction.
    A branch that carries a relocation goes where `branches` maps its position (a position in
    `code`, or None for a target outside it); in a relocatable object its field is not the
    displacement.
    A path ends where the register is overwritten (an li, lis or a general-register load into it,
    an addi rB,rB,imm, or an rlwinm/ori-type instruction writing it from another register; an addi
    into it from another register is refused), at a return, or at a call when the register is volatile. An addi from
    the register forms a derived address, returned as a one-byte use at its immediate: it must lie
    in the section like any address formed there. None when any path uses the address any other
    way (passed on, stored, indexed, moved by an update form), leaves the function's bytes, runs
    through a computed or conditional-return branch, or keeps a callee-saved base past a call."""
    if register == 0:  # r0 as rA reads as zero: an address in r0 is never a base.
        return None
    branches = branches or {}

    def destination(position, field):
        to = branches[position] if position in branches else position + field
        return to if to is not None and 0 <= to <= len(code) - 4 and to % 4 == 0 else None

    uses, seen, pending = [], set(), [at + 4]
    while pending:
        position = pending.pop()
        while True:
            # The end of the bytes ends a path, as in base_uses; a branch out of them is refused.
            if position in seen or position > len(code) - 4:
                break
            seen.add(position)
            word = struct.unpack_from('>I', code, position)[0]
            opcode, target, base = word >> 26, (word >> 21) & 31, (word >> 16) & 31
            if stores_register(word, register):
                return None
            if opcode in ACCESS_WIDTH and base == register:
                if opcode in UPDATES or opcode in STORES and target == register:
                    return None
                displacement = word & 0xFFFF
                uses.append((displacement - 0x10000 if displacement & 0x8000 else displacement, access_width(word)))
                if opcode in GPR_LOADS and (target == register or opcode == 46 and target <= register):
                    break
                position += 4
                continue
            if opcode == 14 and base == register:  # addi rD, base, imm: an address derived from the base.
                immediate = word & 0xFFFF
                uses.append((immediate - 0x10000 if immediate & 0x8000 else immediate, 1))
                if target == register:
                    break
                position += 4
                continue
            if word == BLR:
                break
            if opcode == 18:  # b / bl
                if word & 2:  # absolute
                    return None
                if word & 1:
                    if register in VOLATILE:
                        break
                    return None
                displacement = word & 0x03FFFFFC
                position = destination(position, displacement - 0x04000000 if displacement & 0x02000000 else displacement)
                if position is None:
                    return None
                continue
            if opcode == 16:  # bc
                if word & 3:  # absolute or bcl
                    return None
                displacement = word & 0xFFFC
                taken = destination(position, displacement - 0x10000 if displacement & 0x8000 else displacement)
                if taken is None:
                    return None
                pending.append(taken)
                if target & 0x14 == 0x14:  # branch always
                    break
                position += 4
                continue
            if opcode == 19:  # bclr, bcctr and the condition-register operations
                return None
            if opcode in (14, 15) and base == 0 and target == register or opcode in GPR_LOADS and \
                    (target == register or opcode == 46 and target <= register):
                break  # li, lis, or a GPR load (lmw from a lower register) into the register: the address is gone.
            if opcode in (21, 23, 24, 25, 26, 27, 28, 29) and base == register and target != register and not (
                    opcode == 23 and (word >> 11) & 31 == register):
                break  # rlwinm, rlwnm, ori, oris, xori, xoris, andi., andis. write rA from rS (and rB): gone.
            if register in (base, (word >> 11) & 31) or target == register:
                return None
            position += 4
    return uses


# R_PPC_ADDR16_LO, and R_PPC_ADDR16_HI/_HA: the low and high halves of an address formed in a register (lis/addi).
ADDRESS_LOW = 4
ADDRESS_HIGH = (5, 6)
# R_PPC_REL24 and R_PPC_REL14 (plain, BRTAKEN, BRNTAKEN): a branch's destination.
BRANCH_RELOCATIONS = (10, 11, 12, 13)


def register_base(code, at, value, size, branches=None):
    """Whether the R_PPC_ADDR16_LO at byte `at` of `code` forms a base register whose every use lands
    in the compiled section's [0, size): the relocation must sit in the low half of an addi, and
    every displacement load or store through the register it sets must lie inside the section,
    until a load redefines the register, a call clobbers it (a volatile register) or the function
    returns, on every path through the function's branches (flow_uses); an address derived from it
    by an addi must lie in the section too. GCC forms object+0x10000 for an object
    larger than 32 KiB and addresses its fields with negative displacements, so such a base lies
    past the section's end. A low half on a load or store is the accessed address itself, not a
    base, and a base that is passed on, stored (also by an stmw, stswi or stswx through any register
    whose range can cover it), indexed, moved by an update form, overwritten any
    other way or live into a branch that leaves the function or cannot be followed, or a
    callee-saved base live past a call, cannot be bounded."""
    if at % 4 != 2 or not 0 <= at - 2 <= len(code) - 4:
        return False
    word = struct.unpack_from('>I', code, at - 2)[0]
    if word >> 26 != 14:  # addi rD, rA, symbol@l
        return False
    uses = flow_uses(code, at - 2, (word >> 21) & 31, branches)
    return bool(uses) and all(0 <= value + d and value + d + w <= size for d, w in uses)


def fragment(native, section, offset, size, target_start, functions, targets, placements, externals, output, target_sections,
             storage=None, commons=None):
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
    # Where each relocated branch of the fragment goes, as a position in `code` (None: outside it).
    branches = {}
    for position, info, addend in native_relocations:
        if info & 255 in BRANCH_RELOCATIONS and 0 < info >> 8 <= len(symbols):
            symbol = symbols[(info >> 8) - 1]
            destination = symbol['value'] + addend - offset
            inside = symbol['shndx'] == section['index'] and 0 <= destination < size
            branches[position - offset] = destination if inside else None
    for position, info, addend in native_relocations:
        index, kind = info >> 8, info & 255
        if not 0 < index <= len(symbols):
            raise ValueError('Invalid native relocation symbol')
        symbol = symbols[index - 1]
        name = symbol['name']
        value = symbol['value'] + addend
        if symbol['shndx'] == sb.SHN_COMMON:
            # COMMON storage has no section; only an evidenced storage address locates it: the
            # comparison's own storage map, or commons, the addresses the verified source build placed
            # linked units' mapped COMMON symbols at (function_compare.accepted_references). That covers
            # a holdouts file whose COMMON lies outside its own uninitialized placements. A configured
            # external of the same name (externals) never places a COMMON symbol.
            if storage is not None and index - 1 in storage:
                address = storage[index - 1] + addend
            elif commons is not None and name in commons:
                address = commons[name] + addend
            else:
                raise ValueError(f'Comparison common symbol {name} lacks an evidenced storage address')
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
                        kind == ADDRESS_LOW and register_base(code, position - offset, value, owned['size'], branches)
                        or kind in ADDRESS_HIGH and any(
                            other >> 8 == index and other & 255 == ADDRESS_LOW and more == addend
                            and register_base(code, at - offset, value, owned['size'], branches)
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
