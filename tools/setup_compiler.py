#!/usr/bin/env python3
"""Prepare the pinned working compiler; this does not select source-unit flags."""

import hashlib
import json
import platform
import shutil
import urllib.request
import zipfile
from pathlib import Path

import toolchain


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


# The reviewed CodeWarrior versions: the SDK default, and the ones an SDK profile may select
# with "compiler_version" (each such profile carries its own compiler evidence row).
SDK_DEFAULT = "GC/1.2.5n"
SDK_PROFILE_VERSIONS = {"GC/1.3"}


def sdk_versions(lock=None):
    """(default SDK compiler, versions an SDK profile may select) from the pinned lock file."""
    lock = lock or json.loads((ROOT / "tools/compiler-tools.json").read_text())
    default = lock.get("sdk_compiler_version")
    extra = lock.get("sdk_profile_compiler_versions", [])
    if default != SDK_DEFAULT:
        raise RuntimeError("Unsupported pinned SDK compiler")
    if not isinstance(extra, list) or len(set(extra)) != len(extra) \
            or not set(extra) <= SDK_PROFILE_VERSIONS:
        raise RuntimeError("Unsupported pinned SDK profile compiler")
    return default, set(extra)


def setup_sdk(version=None):
    """The directory of one pinned CodeWarrior version (the SDK default when version is None)."""
    lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    default, extra = sdk_versions(lock)
    version = default if version is None else version
    if version != default and version not in extra:
        raise RuntimeError(f"SDK compiler {version} is not pinned in tools/compiler-tools.json")
    compilers = toolchain.recorded("compilers")
    if compilers is not None:
        if not (compilers / version / "mwcceppc.exe").is_file():
            raise RuntimeError(f"The recorded compiler pack has no {version}")
        return compilers / version
    archive = DESTINATION / "compilers.zip"
    fetch(lock["compilers"], archive)
    return extract(archive, version)


def setup_sdks(versions):
    """{version: directory} for each SDK compiler version the given units use."""
    return {version: setup_sdk(version) for version in sorted(set(versions))}


def setup():
    lock = json.loads((ROOT / "tools/compiler-tools.json").read_text())
    compilers, wibo = toolchain.recorded("compilers"), toolchain.recorded("wibo")
    if compilers is not None:
        # The build image's compiler pack and Wibo (build.py configure).
        if wibo is None:
            raise RuntimeError("build/toolchain.json records the compilers without Wibo")
        return compilers / f"ProDG/{lock['compiler_version']}", wibo
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
