#!/usr/bin/env python3
"""Compile a C/C++ translation unit through isolated ProDG stages.

`--dump-dir DIR` keeps cc1's per-pass RTL dumps for the unit in DIR (GCC 2.95's `-d` flags; `--dump`
picks them, comma-separated, default `-da` for every pass; `-dr,-dl,-dg` for single passes). The
dumps contain the game's code, so DIR must lie outside the repository or under its ignored build/
or scratch/ folders. Dumps change nothing in the compiled object."""

import os
import re
import shutil
import signal
import struct
import subprocess
import sys
import tempfile
from pathlib import Path


CPP_COMMON = ["-D__GNUC__=2", "-D__GNUC_MINOR__=95", "-D__NOASMPP__"]
CPP_TARGET = [
    "-DPPC", "-D__PPC__", "-D__PPC", "-Acpu(powerpc)", "-Amachine(powerpc)",
    "-D__CHAR_UNSIGNED__", "-D_BIG_ENDIAN", "-D__BIG_ENDIAN__", "-Amachine(bigendian)",
    "-D__PTRDIFF_TYPE__=int", "-D__SIZE_TYPE__=unsigned", "-D_CALL_SYSV",
    "-DSN_TARGET_NGC", "-D__SN__",
]
CPP_LANG = {
    "c": (["-lang-c"], ["-D_LANGUAGE_C", "-D__LANGUAGE_C", "-DLANGUAGE_C"]),
    "c++": (["-D__GNUG__=2", "-lang-c++", "-D__cplusplus"],
            ["-D_LANGUAGE_C_PLUS_PLUS", "-D__LANGUAGE_C_PLUS_PLUS"]),
}
OPTIONS = {"--wrapper", "--dir", "--depfile", "-c", "-o", "-x", "--dump-dir", "--dump"}
CPP_WITH_ARG = {"-I", "-D", "-U", "-isystem", "-include"}
COMPILER_WITH_ARG = {"-G"}
STAGE_TIMEOUT = 30
DUMP_FLAG = re.compile(r"-d[A-Za-z]+")
ROOT = Path(__file__).resolve().parents[1]
PRIVATE = ("build", "scratch")


def dump_options(options):
    """Validate the dump options; return (flags, directory) or (None, None)."""
    if "--dump" in options and "--dump-dir" not in options:
        raise ValueError("--dump needs --dump-dir")
    if "--dump-dir" not in options:
        return None, None
    flags = options.get("--dump", "-da").split(",")
    if not all(DUMP_FLAG.fullmatch(flag) for flag in flags):
        raise ValueError("--dump takes GCC -d flags such as -da or -dl,-dg")
    directory = Path(options["--dump-dir"]).resolve()
    if directory.is_relative_to(ROOT.resolve()) and \
            directory.relative_to(ROOT.resolve()).parts[:1] not in [(name,) for name in PRIVATE]:
        raise ValueError("--dump-dir must be outside the repository or under build/ or scratch/; "
                         "dumps contain the game's code")
    return flags, directory


def parse(args):
    options, cpp_flags, compiler_flags = {}, [], []
    i = 0
    while i < len(args):
        flag = args[i]
        if flag in OPTIONS | CPP_WITH_ARG | COMPILER_WITH_ARG:
            if i + 1 == len(args) or (args[i + 1].startswith("-") and flag != "--dump"):
                raise ValueError(f"{flag} requires a value")
            value = args[i + 1]
            if flag in OPTIONS:
                if flag in options:
                    raise ValueError(f"Duplicate option: {flag}")
                options[flag] = value
            elif flag in CPP_WITH_ARG:
                cpp_flags.extend([flag, value])
            else:
                compiler_flags.extend([flag, value])
            i += 2
            continue
        if flag.startswith(("-I", "-D", "-U")) or flag == "-nostdinc":
            cpp_flags.append(flag)
        elif flag.startswith("-Wp,"):
            cpp_flags.extend(flag[4:].split(","))
        elif flag.startswith("-"):
            compiler_flags.append(flag)
        else:
            raise ValueError(f"Unexpected argument: {flag}")
        i += 1
    for required in ("--dir", "-c", "-o"):
        if required not in options:
            raise ValueError(f"{required} is required")
    language = options.get("-x")
    if language is None:
        extension = Path(options["-c"]).suffix.lower()
        if extension == ".c":
            language = "c"
        elif extension in {".cpp", ".cc", ".cxx", ".cp"}:
            language = "c++"
        else:
            raise ValueError("Specify -x c or -x c++ for this source extension")
    if language not in CPP_LANG:
        raise ValueError("Language must be c or c++")
    dump_options(options)
    return options, cpp_flags, compiler_flags, language


def stage(command, output):
    process = subprocess.Popen(command, stdin=subprocess.DEVNULL, start_new_session=True)
    try:
        status = process.wait(timeout=STAGE_TIMEOUT)
    except subprocess.TimeoutExpired:
        os.killpg(process.pid, signal.SIGKILL)
        process.wait()
        raise RuntimeError(f"Compiler stage timed out producing {output.name}")
    except BaseException:
        os.killpg(process.pid, signal.SIGKILL)
        process.wait()
        raise
    if status != 0:
        raise RuntimeError(f"Compiler stage failed with exit {status}")
    if not output.is_file():
        raise RuntimeError(f"Compiler stage did not produce {output.name}")


def compile_unit(options, cpp_flags, compiler_flags, language):
    # A relative source path reaches the preprocessor as given (relative to the working
    # directory), so __FILE__ keeps the build's relative spelling.
    source = Path(options["-c"])
    if source.is_absolute():
        source = source.resolve()
    directory = Path(options["--dir"]).resolve()
    output = Path(options["-o"]).resolve()
    depfile = Path(options["--depfile"]).resolve() if "--depfile" in options else None
    wrapper = [str(Path(options["--wrapper"]).resolve())] if "--wrapper" in options else []
    dump_flags, dump_directory = dump_options(options)
    output.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix=output.stem + "-", dir=output.parent) as temporary:
        temporary = Path(temporary)
        preprocessed = temporary / (output.stem + ".i")
        assembly = temporary / (output.stem + ".s")
        compiled = temporary / output.name
        dependencies = temporary / "dependencies.d"
        cpp = wrapper + [str(directory / "CPP.exe")]
        if any(flag.startswith("-O") and flag != "-O0" for flag in compiler_flags):
            cpp.append("-D__OPTIMIZE__")
        cpp += CPP_COMMON + CPP_LANG[language][0] + CPP_TARGET + CPP_LANG[language][1]
        if depfile:
            cpp += ["-MMD", str(dependencies)]
        stage(cpp + cpp_flags + [str(source), "-o", str(preprocessed)], preprocessed)
        compiler = "cc1plus.exe" if language == "c++" else "cc1.exe"
        stage(wrapper + [str(directory / compiler)] + compiler_flags + (dump_flags or [])
              + ["-quiet", str(preprocessed), "-o", str(assembly)], assembly)
        if dump_flags:
            keep(temporary, {preprocessed, assembly, dependencies}, dump_directory, output.stem)
        stage(wrapper + [str(directory / "NgcAs.exe"), str(assembly), "-o", str(compiled)], compiled)
        header = compiled.read_bytes()[:20]
        if len(header) != 20 or header[:7] != b"\x7fELF\x01\x02\x01" or struct.unpack_from(">HH", header, 16) != (1, 20):
            raise RuntimeError("Compiler output is not a relocatable PowerPC ELF32 object")
        if depfile:
            if not dependencies.is_file():
                raise RuntimeError("Preprocessor did not produce dependency information")
            dependencies.write_bytes(dependencies.read_bytes().replace(b"\r\n", b"\n"))
            depfile.parent.mkdir(parents=True, exist_ok=True)
            with tempfile.NamedTemporaryFile(dir=depfile.parent, delete=False) as pending:
                pending.write(dependencies.read_bytes())
            os.replace(pending.name, depfile)
        os.replace(compiled, output)


def keep(temporary, inputs, directory, stem):
    """Move cc1's dump files (named after the preprocessed input) into the dump directory."""
    dumps = sorted(p for p in temporary.iterdir() if p.is_file() and p not in inputs)
    if not dumps:
        raise RuntimeError("cc1 wrote no dump files")
    directory.mkdir(parents=True, exist_ok=True)
    for dump in dumps:
        shutil.copyfile(dump, directory / (stem + dump.name[len(stem):] if dump.name.startswith(stem) else dump.name))
    shutil.copyfile(temporary / (stem + ".s"), directory / (stem + ".s"))


def main():
    if os.name == "nt":
        raise RuntimeError("This wrapper currently supports POSIX hosts only")
    compile_unit(*parse(sys.argv[1:]))


if __name__ == "__main__":
    try:
        main()
    except (ValueError, OSError, RuntimeError) as error:
        sys.exit(f"prodg_cc: {error}")
