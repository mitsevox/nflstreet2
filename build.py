#!/usr/bin/env python3
"""Build, verify and measure one target. This is the repository's build entry (the kit's
`build.py`, in place of dtk-template's configure.py and ninja):

    python3 build.py configure [--dtk PATH --binutils DIR --compilers DIR --wibo PATH --objdiff PATH]
    python3 build.py [--target GN7E69-rev0]        source build, inventory, comparisons, report
    python3 build.py check [--target GN7E69-rev0]  the checks that need the toolchain

`configure` records tools already installed (the build image's) in build/toolchain.json; without it
the scripts download the versions pinned in tools/*-tools.json. The build fails unless the complete
executable built from source is byte-identical to the original; it ends with
`build/<target id>/main.dol: OK` and writes build/<target id>/report.json, the report the site's
publish action reads. The original is read from orig/<target id>/sys/main.dol."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "tools"))


def default_target():
    return json.loads((ROOT / "config/targets.json").read_text())["defaultTarget"]


def run(*args, **options):
    print("+ " + " ".join(str(a) for a in args), flush=True)
    subprocess.run([sys.executable, *map(str, args)], cwd=ROOT, check=True, **options)


def revision():
    return subprocess.check_output(["git", "-c", "safe.directory=*", "rev-parse", "HEAD"],
                                   cwd=ROOT, text=True).strip()


def configure(args):
    import toolchain
    recorded = toolchain.record({"dtk": args.dtk, "binutils": args.binutils, "compilers": args.compilers,
                                 "wibo": args.wibo, "objdiff": args.objdiff})
    for name, path in sorted(recorded.items()):
        print(f"{name}: {path}")


def build(target):
    original = ROOT / "orig" / target / "sys/main.dol"
    out = ROOT / "build" / target
    # A failed build cannot leave an earlier success behind.
    for stale in (out / "main.dol", out / "report.json"):
        stale.unlink(missing_ok=True)
    run("tools/source_build.py", "--original", original)
    run("tools/analyze.py", "--original", original, "--reuse-inventory",
        "--cache-context", os.environ.get("BUILD_IMAGE", ""))
    run("tools/matching.py", "--original", original)
    run("tools/export_progress.py", "--dol", ROOT / "build/source/main.dol", "--revision", revision(),
        "--source-report", ROOT / "build/source/report.json", "--analysis-dir", ROOT / "build/analysis",
        "--comparison-report", ROOT / "build/matching/report.json", "--output", out / "report.json")
    expected, path = (ROOT / "config" / target / "build.sha1").read_text().split()
    out.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(ROOT / "build/source/main.dol", ROOT / path)
    if hashlib.sha1((ROOT / path).read_bytes()).hexdigest() != expected:
        (ROOT / path).unlink()
        (out / "report.json").unlink(missing_ok=True)
        sys.exit(f"{path}: FAILED (SHA-1 differs from config/{target}/build.sha1)")
    print(f"{path}: OK")


def check(target):
    """The checks that need the toolchain: the original-object relinks with GNU ld and with SN's
    ngcld, and the tool tests that skip on a runner without it. The report's conversion into the
    site's contract is CI's `Check the report` step (the site's check-report action, on every
    event), not this command's."""
    import setup_compiler
    original = ROOT / "orig" / target / "sys/main.dol"
    run("tools/baseline.py", "--original", original)
    compiler, wibo = setup_compiler.setup()
    run("tools/baseline.py", "--original", original, "--sn-linker", compiler / "ngcld.exe", "--wrapper", wibo)
    run("-m", "unittest", "discover", "-s", "tests")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("command", nargs="?", choices=("build", "configure", "check"), default="build")
    parser.add_argument("--target", default=None)
    for name in ("dtk", "binutils", "compilers", "wibo", "objdiff"):
        parser.add_argument("--" + name)
    args = parser.parse_args()
    target = args.target or default_target()
    if args.command == "configure":
        configure(args)
    elif args.command == "check":
        check(target)
    else:
        build(target)


if __name__ == "__main__":
    main()
