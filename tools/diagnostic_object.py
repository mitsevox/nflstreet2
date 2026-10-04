"""Preserve native bytes/relocations in a private, independently positioned comparison fragment."""
import struct
import source_build as sb


def fragment(native, section, offset, size, target_start, functions, targets, placements, externals, output, target_sections):
    sections, symbols = sb.read_elf(native)
    referenced = {}
    relocations = []
    small_references = set()
    for relocation_section in sections:
        if relocation_section['type'] == 9 and relocation_section['info'] == section['index']:
            raise ValueError('Comparison requires explicit-addend PowerPC relocations')
        if relocation_section['type'] != 4 or relocation_section['info'] != section['index']:
            continue
        for at in range(relocation_section['offset'], relocation_section['offset'] + relocation_section['size'], 12):
            position, info, addend = struct.unpack_from('>IIi', native, at)
            if not offset <= position < offset + size:
                continue
            index, kind = info >> 8, info & 255
            if not 0 < index <= len(symbols):
                raise ValueError('Invalid native relocation symbol')
            symbol = symbols[index - 1]
            name = symbol['name']
            value = symbol['value'] + addend
            if symbol['shndx'] == sb.SHN_UNDEF:
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
                else:
                    placement = placements.get(owned['name'])
                    if placement is None or not 0 <= value < placement['end'] - placement['start']:
                        raise ValueError('Same-file data reference lacks target placement')
                    address = placement['start'] + value
            if not 0 <= address <= 0xFFFFFFFF:
                raise ValueError('Comparison relocation exceeds target address space')
            alias = f'__comparison_reference_{address:08X}'
            referenced[alias] = address
            if kind in (32, 106, 107, 109, 116):
                small_references.add(alias)
            relocations.append((position-offset, kind, alias))
    fragment_section = dict(section, size=size, data=section['data'][offset:offset+size])
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
