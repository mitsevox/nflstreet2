# Original-object baseline

Curated name and boundary claims belong in [evidence.tsv](evidence.tsv), using the [evidence format](../README.md). The table does not apply symbols or splits to this baseline.

`baseline.json` records the DOL's section addresses, entry point, complete size, and hash. Section names are toolkit placeholders, not recovered original names or compilation-unit boundaries. The small-data bases are loaded into r13 and r2 at `0x80003108`–`0x80003114` in the target entry code.

The baseline splits the original executable into relocatable objects, links them with GNU binutils, converts the ELF back to DOL, and compares every output byte with the verified target. This demonstrates a working original-object relink, not the original compiler or linker identity, recovered source, or matching progress.

The provisional working compiler is ProDG 3.9.3, with Wibo 1.0.3 on the supported hosts. Downloads are verified against `tools/compiler-tools.json`. The isolated-stage wrapper produces native-driver-equivalent C/C++ objects, validates arguments and fresh outputs, normalizes dependency line endings, and stops the process group on timeout. It never retries with different flags or modifies compiled instructions. Compiler stages currently support POSIX hosts; macOS uses the x86-64 Wibo executable through the host's existing Rosetta support.

CI also checks ngcld's original-object relink against the complete target. A 48-byte diagnostic source reproduction is compatible with all five available ProDG versions and multiple optimization settings; it rejects `-G0` for that case. This establishes a usable toolchain, not a unique original compiler version or project-wide flag profile. Reconstructed units still need evidence for their compiler settings and source boundaries before entering the combined build.

The baseline uses `quick_analysis`; relocation processing and the complete executable comparison still run. Function boundaries and source compilation must be established separately before using CI to accept reconstructed code. Generated objects, assembly, symbols, and binaries stay under ignored `build/`.

## Function analysis

Run `python3 tools/analyze.py --original /path/to/main.dol` to generate a provisional inventory and verify its complete original-object relink with the pinned tools. Each run starts from the small seed set in `analysis.json`, rather than reusing a previous inferred inventory. Results and logs stay in `build/analysis/`.

Three constant/string ranges in `.text` are annotated as data. Function inference and inferred relocations are disabled only within those ranges; every byte remains linked and compared. A separate loop routine is seeded so exception code branching to it does not acquire an oversized function extent. The [evidence table](evidence.tsv) records these annotations and unresolved thunk edges.

For the analyzed relink, ngcld requires small-data output section names. Absolute references `lbl_803ED681` and the toolkit's `_stack_end` resolve to `0x803ED681`, the target value loaded at `0x8000315C`–`0x80003160`; this is not a recovered stack-symbol name. The script does not substitute a generated SDK stack formula.

An identical analyzed relink validates the mechanics, not the inventory's names, total function count, source units, or reconstructed source. Toolkit signatures and assembly boundary guesses still require review. In particular, the twelve branch/return pairs at `0x801AC9A0`–`0x801AC9FC` retain unresolved ownership of their unreachable returns; no source split is made there.
