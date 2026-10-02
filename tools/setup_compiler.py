#!/usr/bin/env python3
"""Prepare the pinned working compiler; this does not select source-unit flags."""

import hashlib
import json
import platform
import shutil
import urllib.request
import zipfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
DESTINATION = ROOT / "build" / "toolchain"


def fetch(spec, path):
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists() and hashlib.sha256(path.read_bytes()).hexdigest() == spec["sha256"]:
        return
    temporary = path.with_suffix(".download")
    with urllib.request.urlopen(spec["url"], timeout=120) as response:
        with temporary.open("wb") as output:
            shutil.copyfileobj(response, output)
    if hashlib.sha256(temporary.read_bytes()).hexdigest() != spec["sha256"]:
        temporary.unlink()
        raise RuntimeError("Toolchain download checksum mismatch")
    temporary.replace(path)


def extract(archive, version):
    directory = DESTINATION / version
    prefix = version + "/"
    with zipfile.ZipFile(archive) as package:
        members = [name for name in package.namelist() if name.startswith(prefix) and not name.endswith("/")]
        if not members:
            raise RuntimeError(f"Pinned archive does not contain compiler {version}")
        for name in members:
            output = directory / name[len(prefix):]
            if not output.resolve().is_relative_to(directory.resolve()):
                raise RuntimeError("Invalid compiler archive path")
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_bytes(package.read(name))
    return directory


def setup_sdk():
    lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    version = lock.get("sdk_compiler_version")
    if version != "GC/1.2.5n":
        raise RuntimeError("Unsupported pinned SDK compiler")
    archive = DESTINATION / "compilers.zip"
    fetch(lock["compilers"], archive)
    return extract(archive, version)


def setup():
    lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    archive = DESTINATION / "compilers.zip"
    fetch(lock["compilers"], archive)
    directory = extract(archive, f"ProDG/{lock['compiler_version']}")
    system = f"{platform.system().lower()}-{platform.machine().lower()}"
    system = {"darwin-arm64": "macos-arm64", "linux-amd64": "linux-x86_64"}.get(system, system)
    if system not in lock["wibo"]:
        raise RuntimeError(f"Unsupported compiler host: {system}")
    wrapper = DESTINATION / "wibo"
    fetch(lock["wibo"][system], wrapper)
    wrapper.chmod(0o755)
    return directory, wrapper


if __name__ == "__main__":
    directory, wrapper = setup()
    print(f"Compiler: {directory}\nWrapper: {wrapper}")
