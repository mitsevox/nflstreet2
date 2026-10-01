#!/usr/bin/env python3
"""Relink original objects and verify the entire target; no source progress is claimed."""

import argparse
import hashlib
import json
import platform
import shutil
import subprocess
import urllib.request
import zipfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build" / "baseline"


def digest(path, algorithm):
    return hashlib.new(algorithm, path.read_bytes()).hexdigest()


def get_tool(name, lock, system):
    spec = lock[name][system]
    archive = BUILD / "tools" / (name + (".zip" if name == "binutils" else ""))
    archive.parent.mkdir(parents=True, exist_ok=True)
    if not archive.exists() or digest(archive, "sha256") != spec["sha256"]:
        temporary = archive.with_suffix(".download")
        with urllib.request.urlopen(spec["url"], timeout=120) as response:
            with temporary.open("wb") as output:
                shutil.copyfileobj(response, output)
        if digest(temporary, "sha256") != spec["sha256"]:
            temporary.unlink()
            raise RuntimeError(f"Checksum mismatch for {name}")
        temporary.replace(archive)
    if name == "binutils":
        executable = archive.parent / "powerpc-eabi-ld"
        with zipfile.ZipFile(archive) as package:
            executable.write_bytes(package.read("powerpc-eabi-ld"))
    else:
        executable = archive
    executable.chmod(0o755)
    return executable


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--original", type=Path, required=True)
    args = parser.parse_args()
    target = json.loads((ROOT / "config/GN7E69/baseline.json").read_text())
    original = args.original.resolve()
    if original.stat().st_size != target["size"] or digest(original, "sha1") != target["sha1"]:
        raise RuntimeError("Original executable does not match the configured target")
    system = f"{platform.system().lower()}-{platform.machine().lower()}"
    system = {"darwin-arm64": "macos-arm64", "linux-amd64": "linux-x86_64"}.get(system, system)
    lock = json.loads((ROOT / "tools/baseline-tools.json").read_text())
    if system not in lock["dtk"]:
        raise RuntimeError(f"Unsupported baseline host: {system}")
    BUILD.mkdir(parents=True, exist_ok=True)
    dtk = get_tool("dtk", lock, system)
    linker = get_tool("binutils", lock, system)
    split = BUILD / "split"
    if split.exists():
        shutil.rmtree(split)
    symbols = BUILD / "symbols.txt"
    splits = BUILD / "splits.txt"
    symbols.write_text("")
    splits.write_text("")
    config = BUILD / "config.yml"
    config.write_text(
        f"object: {json.dumps(str(original))}\n"
        f"hash: {target['sha1']}\n"
        f"symbols: {json.dumps(str(symbols))}\n"
        f"splits: {json.dumps(str(splits))}\n"
        "quick_analysis: true\n"
    )
    subprocess.run([str(dtk), "dol", "split", str(config), str(split)], check=True, cwd=ROOT)
    units = json.loads((split / "config.json").read_text())["units"]
    script = BUILD / "link.ld"
    script.write_text(
        "SECTIONS {\n"
        f"_SDA_BASE_ = {target['sda_base']};\n"
        f"_SDA2_BASE_ = {target['sda2_base']};\n"
        + "".join(f"{name} {address} : {{ *({name}) }}\n" for name, address in target["sections"].items())
        + "}\n"
    )
    elf = BUILD / "main.elf"
    output = BUILD / "main.dol"
    subprocess.run(
        [str(linker), "-T", str(script), "-e", target["entry"], "-o", str(elf)]
        + [unit["object"] for unit in units], check=True, cwd=ROOT,
    )
    subprocess.run([str(dtk), "elf2dol", str(elf), str(output)], check=True, cwd=ROOT)
    if output.read_bytes() != original.read_bytes() or digest(output, "sha1") != target["sha1"]:
        raise RuntimeError("Relinked executable differs from the complete target")
    print(f"Baseline verified: {target['size']} bytes, SHA-1 {target['sha1']}")
    print("Original objects only; reconstructed source and progress are not validated by this check.")


if __name__ == "__main__":
    main()
