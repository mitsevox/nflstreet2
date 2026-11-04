"""What counts as a name: placeholder labels, compiler-generated symbols and GCC 2.95 demangling,
shared by tools/rename.py and tools/files_closed.py."""
import re

# A label that claims nothing: a name built on a game address (fn_8000ABCD, lbl_, data_, Class_, Block_,
# Record_, cu_, sUnknown803EC0F0) or a virtual-slot number (vfn_01).
PLACEHOLDER = re.compile(r'[A-Za-z]_?8[01][0-9A-Fa-f]{6}(?![0-9A-Fa-f])|(?<![A-Za-z0-9])vfn_\d+(?![A-Za-z0-9])'
                         r'|Unknown(?![a-z])')
# Symbols the compiler or assembler makes, which no person names: GCC's unit marker, static
# constructor and destructor wrappers, numbered unnamed statics and CodeWarrior's @123 literals.
GENERATED = re.compile(r'gcc2_compiled\.|_GLOBAL_\.|__static_initialization_and_destruction|__tcf_|__sinit|__sterm'
                       r'|_\.tmp_|\.\.\.(?:data|bss|rodata|sdata|sbss)|@\d')


def placeholder(name):
    return bool(PLACEHOLDER.search(name))


def generated(symbol):
    return bool(GENERATED.match(symbol))


def base_name(symbol):
    """A function-local static's name without GCC's numeric suffix: sInstance.105 -> sInstance."""
    return re.sub(r'\.\d+$', '', symbol)


def demangle(symbol):
    """`Class::name` (or `name`) for the GCC 2.95 spellings our sources produce; None when generated."""
    if generated(symbol):
        return None
    match = re.match(r'(_\._|__)(\d+)([A-Za-z_]\w*)', symbol)
    if match and int(match[2]) <= len(match[3]):
        name = match[3][:int(match[2])]
        return f"{name}::{'~' if match[1] == '_._' else ''}{name}"
    match = re.match(r'(.+?)__(\d+)([A-Za-z_]\w*)', symbol)
    if match and int(match[2]) <= len(match[3]):
        return f'{match[3][:int(match[2])]}::{match[1]}'
    match = re.match(r'(.+?)__(?:F|C|Q)', symbol)
    return match[1] if match else symbol


def evidence_names(evidence_path):
    """{address: names} from the evidence rows that can name a thing at an address: name, function,
    external and data rows. A subject may carry a note (`WriteCallback (src/dolphin/card/CARDDir.c)`,
    `__piReg storage`), so each of its words counts as well as the whole."""
    given = {}
    lines = evidence_path.read_text().splitlines()
    header = lines[0].split('\t')
    kind, start, subject = header.index('kind'), header.index('start'), header.index('subject')
    for line in lines[1:]:
        row = line.split('\t')
        if row[kind] in ('name', 'external', 'function', 'data') and row[start] != '-':
            given.setdefault(int(row[start], 16), set()).update({row[subject], *row[subject].split()})
    return given
