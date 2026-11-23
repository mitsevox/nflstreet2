#!/usr/bin/env python3
"""List every unmapped data range with the code and data that refer to it.

    python3 tools/data_owners.py                 after `python3 build.py`; writes build/<target>/data_owners.tsv
    python3 tools/data_owners.py --file SOURCE   prints only the ranges SOURCE (a source path or a
                                                 `Candidate / ...` unit name) refers to

Data bytes are Unmapped on the site while no linked file places them. Most of them belong to files
that are not linked yet and move over when those files link; the rest are referred to only by
linked files, or by nothing at all. This report tells each lane which unmapped data its file uses
before it links, and lists the ranges no file work will reach.

The ranges are the report's `Unmapped / <section>` extents (build/<target>/report.json), cut into
pieces at every address something refers to. A reference is an absolute address formed in a
function by `lis` and a later displacement (addi, ori or a load or store through that register),
an r13 or r2 small-data displacement, or a pointer word in a loaded data section (a word that
points at itself is ignored). Only whole functions the report lists are scanned. The scan follows
no branches, so it is a guide for reading the code, not evidence: an object addressed only through
a register base it does not see (an array element, a member of a larger object) shows as part of
the piece before it, and a stale `lis` can name a false user.

Each piece gets a status:
- `pending`: at least one user is a function or data word of a file that is not wholly linked
  (a candidate unit, a file linked with holdouts, or unmapped code), or a data word in unmapped
  data or in no unit; it moves with that file.
- `linked-only`: every user is in a wholly linked file; that file already decided to leave it
  (an extern, an asset kept out of Git) or the piece is a member of a larger object.
- `orphan`: nothing refers to it: the data of a linker-discarded function, padding, or an object
  reached only through computed addresses.
"""
import argparse
import bisect
import csv
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
TARGET = "GN7E69-rev0"

# Primary opcodes of D-form instructions whose displacement may complete a `lis` address.
LOADS_GPR = {32, 33, 34, 35, 40, 41, 42, 43, 46}       # lwz lwzu lbz lbzu lhz lhzu lha lhau lmw
STORES = {36, 37, 38, 39, 44, 45, 47}                  # stw stwu stb stbu sth sthu stmw
FLOAT = {48, 49, 50, 51, 52, 53, 54, 55}               # lfs lfsu lfd lfdu stfs stfsu stfd stfdu
ADDI, ORI, LIS, LMW = 14, 24, 15, 46
UPDATE_FORMS = {33, 35, 41, 43, 37, 39, 45, 49, 51, 53, 55}
VOLATILE = (0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)


def dol_segments(binary):
    offsets = struct.unpack_from(">18I", binary, 0)
    addresses = struct.unpack_from(">18I", binary, 0x48)
    sizes = struct.unpack_from(">18I", binary, 0x90)
    return [(addresses[i], addresses[i] + sizes[i], offsets[i], i < 7) for i in range(18) if sizes[i]]


class Image:
    def __init__(self, binary):
        self.binary = binary
        self.segments = dol_segments(binary)

    def word(self, address):
        for start, end, offset, _ in self.segments:
            if start <= address and address + 4 <= end:
                return struct.unpack_from(">I", self.binary, offset + address - start)[0]
        return None


def function_references(words, start, sda_bases):
    """Absolute data addresses one function's instructions form: [(instruction address, target)]."""
    high, found = {}, []
    for index, word in enumerate(words):
        if word is None:
            high.clear()
            continue
        op, rd, ra = word >> 26, (word >> 21) & 31, (word >> 16) & 31
        immediate = word & 0xFFFF
        signed = immediate - 0x10000 if immediate & 0x8000 else immediate
        if op == LIS:
            # lis rD,imm (addis rD,0,imm) sets an address high half; addis from a register does not.
            if ra == 0:
                high[rd] = immediate << 16
            else:
                high.pop(rd, None)
            continue
        if op in (ADDI, ORI) or op in LOADS_GPR or op in STORES or op in FLOAT:
            base_register = rd if op == ORI else ra      # ori rA, rS, imm: the source is rS
            if op != ORI and ra == 0:
                base = None                              # rA = 0 means the literal 0, not r0
            elif base_register in sda_bases:
                base = sda_bases[base_register]
            else:
                base = high.get(base_register)
            if base is not None:
                found.append((start + index * 4, (base + (immediate if op == ORI else signed)) & 0xFFFFFFFF))
            # The written register no longer holds a `lis` value.
            if op == ORI:
                high.pop(ra, None)
            elif op == LMW:
                for register in range(rd, 32):
                    high.pop(register, None)
            elif op in (ADDI,) or op in LOADS_GPR:
                high.pop(rd, None)
            if op in UPDATE_FORMS:
                high.pop(ra, None)
        elif op in (56, 57, 60, 61):
            if op in (57, 61):                           # psq_lu, psq_stu rewrite rA
                high.pop(ra, None)
        elif op == 18:
            if word & 1:                                 # bl: a call clobbers the volatile registers
                for register in VOLATILE:
                    high.pop(register, None)
        elif op == 31 or op in (7, 8, 12, 13, 20, 21, 23, 25, 26, 27, 28, 29):
            # Register-writing arithmetic and logic: forget the destination conservatively.
            high.pop(ra if op in (20, 21, 23, 25, 26, 27, 28, 29) else rd, None)
            if op == 31:
                high.pop(ra, None)
    return found


def load_report(root):
    report = json.loads((root / f"build/{TARGET}/report.json").read_text())
    linked = {}
    with (root / f"build/{TARGET}/files.tsv").open() as handle:
        for row in csv.DictReader(handle, delimiter="\t"):
            linked[row["source"]] = row["linked"]
    owners, functions, unmapped = [], [], []
    for unit in report["units"]:
        name = unit["name"]
        if name.startswith("Unmapped"):
            status = "pending"
        elif name.startswith("Candidate"):
            status = "pending"
        else:
            status = "linked" if linked.get(name) == "yes" else "pending"
        for section in unit["sections"]:
            start = int(section["metadata"]["virtual_address"])
            end = start + int(section["size"])
            owners.append((start, end, name, status))
            if name.startswith("Unmapped") and "Code" not in section["name"]:
                unmapped.append((start, end, section["name"]))
        for function in unit.get("functions", []):
            start = int(function["metadata"]["virtual_address"])
            functions.append((start, start + int(function["size"]), function["name"], name, status))
    return sorted(owners), sorted(functions), sorted(unmapped)


def analyse(root):
    binary = (root / f"orig/{TARGET}/sys/main.dol").read_bytes()
    image = Image(binary)
    target = json.loads((root / f"config/{TARGET}/baseline.json").read_text())
    sda = {13: int(target["sda_base"], 16), 2: int(target["sda2_base"], 16)}
    owners, functions, unmapped = load_report(root)
    starts = [owner[0] for owner in owners]

    def owner(address):
        at = bisect.bisect_right(starts, address) - 1
        if at >= 0 and owners[at][0] <= address < owners[at][1]:
            return owners[at]
        return None

    data_extents = [(lo, hi) for lo, hi, _, code in image.segments if not code]
    bss_start, bss_size = struct.unpack_from(">II", binary, 0xD8)
    data_extents.append((bss_start, bss_start + bss_size))

    def is_data(address):
        return any(lo <= address < hi for lo, hi in data_extents)

    users = {}   # target address -> set of (user unit, user status, user label)
    for start, end, name, unit, status in functions:
        words = [image.word(address) for address in range(start, end, 4)]
        for _, address in function_references(words, start, sda):
            if is_data(address):
                users.setdefault(address, set()).add((unit, status, name))
    for lo, hi, offset, code in image.segments:
        if code:
            continue
        for address in range(lo, hi - 3, 4):
            value = struct.unpack_from(">I", binary, offset + address - lo)[0]
            if value != address and is_data(value):
                holder = owner(address)
                label = f"data 0x{address:08X}"
                users.setdefault(value, set()).add(
                    (holder[2], holder[3], label) if holder else ("?", "pending", label))
    referenced = sorted(users)
    pieces = []
    for lo, hi, section in unmapped:
        cuts = [lo] + referenced[bisect.bisect_right(referenced, lo):bisect.bisect_left(referenced, hi)] + [hi]
        for start, end in zip(cuts, cuts[1:]):
            who = sorted(users.get(start, ()))
            if not who:
                status = "orphan"
            elif any(user_status == "pending" for _, user_status, _ in who):
                status = "pending"
            else:
                status = "linked-only"
            pieces.append({"section": section, "start": start, "end": end, "status": status, "users": who})
    return pieces


def write(pieces, path):
    with path.open("w") as handle:
        handle.write("section\tstart\tend\tsize\tstatus\tfiles\tusers\n")
        for piece in pieces:
            files = sorted({unit for unit, _, _ in piece["users"]})
            labels = sorted({label for _, _, label in piece["users"]})
            handle.write(f"{piece['section']}\t0x{piece['start']:08X}\t0x{piece['end']:08X}\t"
                         f"{piece['end'] - piece['start']}\t{piece['status']}\t{', '.join(files) or '-'}\t"
                         f"{', '.join(labels[:8]) + (' ...' if len(labels) > 8 else '') or '-'}\n")


def summary(pieces):
    totals = {}
    for piece in pieces:
        key = (piece["section"], piece["status"])
        totals[key] = totals.get(key, 0) + piece["end"] - piece["start"]
    statuses = ("pending", "linked-only", "orphan")
    lines = ["Unmapped data by status (bytes): " + ", ".join(
        f"{status} {sum(v for (s, st), v in totals.items() if st == status)}" for status in statuses)]
    for section in sorted({s for s, _ in totals}):
        lines.append(f"  {section}: " + ", ".join(f"{status} {totals.get((section, status), 0)}" for status in statuses))
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--file", help="print only the ranges this source path or report unit refers to")
    parser.add_argument("--output", type=Path, default=ROOT / f"build/{TARGET}/data_owners.tsv")
    args = parser.parse_args()
    pieces = analyse(ROOT)
    if args.file:
        names = {args.file, "Candidate / " + args.file}
        for piece in pieces:
            if any(unit in names for unit, _, _ in piece["users"]):
                labels = sorted({label for unit, _, label in piece["users"] if unit in names})
                others = sorted({unit for unit, _, _ in piece["users"]} - names)
                print(f"{piece['section']}\t0x{piece['start']:08X}-0x{piece['end']:08X}\t"
                      f"{piece['end'] - piece['start']}\t{piece['status']}\t{', '.join(labels)}"
                      + (f"\talso: {', '.join(others)}" if others else ""))
        return
    write(pieces, args.output)
    print(summary(pieces))
    output = args.output.resolve()
    print(f"Per-range detail: {output.relative_to(ROOT) if output.is_relative_to(ROOT) else output}")


if __name__ == "__main__":
    main()
