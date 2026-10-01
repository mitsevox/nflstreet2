#!/usr/bin/env python3
"""Compile a C/C++ translation unit through isolated ProDG stages."""

import os
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
OPTIONS = {"--wrapper", "--dir", "--depfile", "-c", "-o", "-x"}
CPP_WITH_ARG = {"-I", "-D", "-U", "-isystem", "-include"}
COMPILER_WITH_ARG = {"-G"}
STAGE_TIMEOUT = 30


def parse(args):
    options, cpp_flags, compiler_flags = {}, [], []
    i = 0
    while i < len(args):
        flag = args[i]
        if flag in OPTIONS | CPP_WITH_ARG | COMPILER_WITH_ARG:
            if i + 1 == len(args) or args[i + 1].startswith("-"):
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
    source = Path(options["-c"]).resolve()
    directory = Path(options["--dir"]).resolve()
    output = Path(options["-o"]).resolve()
    depfile = Path(options["--depfile"]).resolve() if "--depfile" in options else None
    wrapper = [str(Path(options["--wrapper"]).resolve())] if "--wrapper" in options else []
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
        stage(wrapper + [str(directory / compiler)] + compiler_flags
              + ["-quiet", str(preprocessed), "-o", str(assembly)], assembly)
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


def main():
    if os.name == "nt":
        raise RuntimeError("This wrapper currently supports POSIX hosts only")
    compile_unit(*parse(sys.argv[1:]))


if __name__ == "__main__":
    try:
        main()
    except (ValueError, OSError, RuntimeError) as error:
        sys.exit(f"prodg_cc: {error}")
