#!/usr/bin/env python3
"""Generate provisional function metadata and verify the complete analyzed relink."""

import argparse
import hashlib
import json
import platform
import re
import shutil
import subprocess
from collections import Counter
from pathlib import Path

import baseline
import setup_compiler


ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build" / "analysis"


def run(command, log):
    with log.open("w") as output:
        result = subprocess.run(command, cwd=ROOT, stdout=output,
                                stderr=subprocess.STDOUT, timeout=600)
    if result.returncode:
        raise RuntimeError(f"Command failed ({result.returncode}); see {log}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    args = parser.parse_args()
    (BUILD / "summary.json").unlink(missing_ok=True)
    original = args.original.resolve()
    target_dir = ROOT / "config" / "GN7E69"
    target = json.loads((target_dir / "baseline.json").read_text())
    plan = json.loads((target_dir / "analysis.json").read_text())
    data = original.read_bytes()
    if len(data) != target["size"] or hashlib.sha1(data).hexdigest() != target["sha1"]:
        raise RuntimeError("Original executable does not match the configured target")
    system = f"{platform.system().lower()}-{platform.machine().lower()}"
    system = {"darwin-arm64": "macos-arm64", "linux-amd64": "linux-x86_64"}.get(system, system)
    lock = json.loads((ROOT / "tools" / "baseline-tools.json").read_text())
    if system not in lock["dtk"]:
        raise RuntimeError(f"Unsupported analysis host: {system}")
    dtk = baseline.get_tool("dtk", lock, system)
    compiler, wrapper = setup_compiler.setup()
    BUILD.mkdir(parents=True, exist_ok=True)
    split = BUILD / "split"
    if split.exists():
        shutil.rmtree(split)
    symbols = BUILD / "symbols.txt"
    splits = BUILD / "splits.txt"
    symbols.write_text("".join(
        f"{item['symbol']} = .text:{item['start']}; // type:{kind} "
        f"size:0x{int(item['end'], 16) - int(item['start'], 16):X}\n"
        for key, kind in (("data_ranges", "object"), ("function_seeds", "function"))
        for item in plan[key]
    ))
    splits.write_text("Sections:\n" + "".join(
        f"\t{name} type:{kind} align:4\n" for name, kind in plan["section_kinds"].items()
    ))
    config = BUILD / "config.yml"
    config.write_text(
        f"object: {json.dumps(str(original))}\nhash: {target['sha1']}\n"
        f"symbols: {json.dumps(str(symbols))}\nsplits: {json.dumps(str(splits))}\n"
        "write_asm: false\nskip_cfa_ranges:\n"
        + "".join(f"  - start: .text:{r['start']}\n    end: .text:{r['end']}\n"
                  for r in plan["data_ranges"])
        + "block_relocations:\n"
        + "".join(f"  - source: .text:{r['start']}\n    end: .text:{r['end']}\n"
                  for r in plan["data_ranges"])
    )
    run([str(dtk), "dol", "split", "-j", "1", str(config), str(split)], BUILD / "analysis.log")
    rows = symbols.read_text().splitlines()
    functions = [r for r in rows if "type:function" in r]
    for region in plan["data_ranges"]:
        for row in functions:
            address = int(re.search(r"= [^:]+:(0x[0-9A-Fa-f]+)", row)[1], 16)
            if int(region["start"], 16) <= address < int(region["end"], 16):
                raise RuntimeError(f"Function inferred inside annotated data: {row}")
    units = json.loads((split / "config.json").read_text())["units"]
    script = BUILD / "link.ld"
    script.write_text(
        f"ENTRY(__start)\nSECTIONS {{\n__start = {target['entry']};\n"
        f"_SDA_BASE_ = {target['sda_base']};\n_SDA2_BASE_ = {target['sda2_base']};\n"
        + "".join(f"{plan['output_sections'].get(name, name)} {address} : {{ *({name}) }}\n"
                  for name, address in target["sections"].items())
        + "".join(f"{name} = {address};\n" for name, address in plan["absolute_symbols"].items())
        + "}\n"
    )
    elf, output = BUILD / "main.elf", BUILD / "main.dol"
    for path in (elf, output):
        path.unlink(missing_ok=True)
    run([str(wrapper), str(compiler / "ngcld.exe"), "-T", str(script), "-o", str(elf)]
        + [u["object"] for u in units], BUILD / "link.log")
    run([str(dtk), "elf2dol", str(elf), str(output)], BUILD / "convert.log")
    result = output.read_bytes()
    if result != data or hashlib.sha1(result).hexdigest() != target["sha1"]:
        raise RuntimeError("Analyzed relink differs from the complete target")
    counts = Counter(re.search(r"type:(\w+)", r)[1] for r in rows if "type:" in r)
    (BUILD / "summary.json").write_text(json.dumps({
        "target_sha1": target["sha1"], "toolkit": lock["dtk"]["version"],
        "complete_relink": "identical", "inventory": "provisional",
        "candidate_counts": counts,
    }, indent=2) + "\n")
    print(f"Analyzed relink verified: {len(result)} bytes, SHA-1 {target['sha1']}")
    print("Generated names, function boundaries and source ownership remain provisional.")


if __name__ == "__main__":
    main()
