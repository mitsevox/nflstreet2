#!/usr/bin/env python3
"""Compile Nintendo SDK units with the pinned CodeWarrior compiler, without modifying objects."""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile

# Release-library options supported by the reviewed SDK profile.
OPTIONS = {"-proc": {"gekko"}, "-fp": {"hard"}, "-Cpp_exceptions": {"off"},
           "-enum": {"int"}, "-char": {"unsigned", "signed"}, "-warn": {"pragmas"},
           "-pragma": {"cats off"}, "-inline": {"auto"}, "-lang": {"c"}}
SWITCHES = {"-nodefaults", "-requireprotos", "-O4,p", "-O3,p", "-I-",
            "-D__GEKKO__", "-DSDK_REVISION=1", "-lang=c"}


def validate_flags(flags):
    index = 0
    while index < len(flags):
        flag = flags[index]
        if flag in SWITCHES:
            index += 1
        elif flag in OPTIONS and index + 1 < len(flags) and flags[index + 1] in OPTIONS[flag]:
            index += 2
        else:
            raise ValueError(f"Unsupported SDK compiler option: {flag}")


def dependency_paths(text):
    """Decode CodeWarrior's Wibo paths; retain source and all -MD header dependencies."""
    lines = text.replace("\r\n", "\n").splitlines()
    if not lines or ": " not in lines[0]:
        raise ValueError("SDK compiler did not produce a dependency list")
    lines[0] = lines[0].split(": ", 1)[1]
    paths = []
    for line in lines:
        value = line.strip()
        if value.endswith("\\"):
            value = value[:-1].rstrip()
        if not value:
            continue
        value = value.replace("\\", "/")
        if re.match(r"^[Zz]:/", value):
            value = value[2:]
        elif re.match(r"^[A-Za-z]:", value):
            raise ValueError(f"Unsupported SDK dependency drive: {value}")
        paths.append(value)
    if not paths:
        raise ValueError("SDK compiler dependency list is empty")
    return list(dict.fromkeys(paths))


def compile(directory, wrapper, source, output, depfile, flags, includes, workdir):
    validate_flags(flags)
    output, depfile = Path(output), Path(depfile)
    output.unlink(missing_ok=True)
    depfile.unlink(missing_ok=True)
    with tempfile.TemporaryDirectory(prefix="sdk-", dir=output.parent) as temporary:
        command = [str(wrapper), str(directory / "mwcceppc.exe"), *flags]
        for include in includes:
            command += ["-i", str(include)]
        command += ["-MD", "-c", str(source), "-o", temporary]
        result = subprocess.run(command, cwd=workdir, stdin=subprocess.DEVNULL,
                                capture_output=True, text=True, timeout=60)
        diagnostics = result.stdout + result.stderr
        if result.returncode or re.search(r"warning|error", diagnostics, re.IGNORECASE):
            raise RuntimeError(f"SDK compilation failed for {source}: {diagnostics}")
        stem = Path(source).stem
        native = Path(temporary) / f"{stem}.o"
        dependencies = Path(temporary) / f"{stem}.d"
        if not native.is_file() or not native.stat().st_size or not dependencies.is_file():
            raise RuntimeError(f"SDK compiler did not produce fresh output and dependencies for {source}")
        paths = dependency_paths(dependencies.read_text())
        escaped = [path.replace(" ", "\\ ") for path in paths]
        depfile.write_text("unit.o: " + " ".join(escaped) + "\n")
        shutil.copyfile(native, output)
