# Original-object baseline

Curated name and boundary claims belong in [evidence.tsv](evidence.tsv), using the [evidence format](../README.md). The table does not apply symbols or splits to this baseline.

`baseline.json` records the DOL's section addresses, entry point, complete size, and hash. Section names are toolkit placeholders, not recovered original names or compilation-unit boundaries. The small-data bases are loaded into r13 and r2 at `0x80003108`–`0x80003114` in the target entry code.

The baseline splits the original executable into relocatable objects, links them with GNU binutils, converts the ELF back to DOL, and compares every output byte with the verified target. This demonstrates a working original-object relink, not the original compiler or linker identity, recovered source, or matching progress.

The provisional working compiler is ProDG 3.9.3, with Wibo 1.0.3 on the supported hosts. Downloads are verified against `tools/compiler-tools.json`. The isolated-stage wrapper produces native-driver-equivalent C/C++ objects, validates arguments and fresh outputs, normalizes dependency line endings, and stops the process group on timeout. It never retries with different flags or modifies compiled instructions. Compiler stages currently support POSIX hosts; macOS uses the x86-64 Wibo executable through the host's existing Rosetta support.

CI also checks ngcld's original-object relink against the complete target. A 48-byte diagnostic source reproduction is compatible with all five available ProDG versions and multiple optimization settings; it rejects `-G0` for that case. This establishes a usable toolchain, not a unique original compiler version or project-wide flag profile. Reconstructed units still need evidence for their compiler settings and source boundaries before entering the combined build.

The baseline uses `quick_analysis`; relocation processing and the complete executable comparison still run. Function boundaries and source compilation must be established separately before using CI to accept reconstructed code. Generated objects, assembly, symbols, and binaries stay under ignored `build/`.

## Function analysis

Discovery is a research task, separate from PR CI. The command below has reproduced the complete target on macOS ARM64, including from a fresh source directory. Full discovery currently exceeds available memory on hosted Linux runners; Linux analysis remains unresolved. Normal builds will consume a curated symbol and split map once its claims have passed review, rather than rediscovering boundaries on every PR.

Run `python3 tools/analyze.py --original /path/to/main.dol` to generate a provisional inventory and verify its complete original-object relink with the pinned tools. Each run starts from the small seed set in `analysis.json`, rather than reusing a previous inferred inventory. Results and logs stay in `build/analysis/`.

Three constant/string ranges in `.text` are annotated as data. Function inference and inferred relocations are disabled only within those ranges; every byte remains linked and compared. A separate loop routine is seeded so exception code branching to it does not acquire an oversized function extent. The [evidence table](evidence.tsv) records these annotations and unresolved thunk edges.

For the analyzed relink, ngcld requires small-data output section names. Absolute references `lbl_803ED681` and the toolkit's `_stack_end` resolve to `0x803ED681`, the target value loaded at `0x8000315C`–`0x80003160`; this is not a recovered stack-symbol name. The script does not substitute a generated SDK stack formula.

An identical analyzed relink validates the mechanics, not the inventory's names, total function count, source units, or reconstructed source. Toolkit signatures and assembly boundary guesses still require review. In particular, the twelve branch/return pairs at `0x801AC9A0`–`0x801AC9FC` retain unresolved ownership of their unreachable returns; no source split is made there.

## Source build

`tools/source_build.py` compiles each unit in [units.json](units.json) with the pinned ProDG wrapper, links the objects in place of exactly their configured address ranges with ngcld through Wibo, converts the ELF with the pinned dtk, and compares every output byte with the verified target. Every other byte comes verbatim from the verified original executable as a generated raw object without relocations, so the original data's pointers need no reanalysis. With no units, the build is the complete original image and must still match.

The manifest records:

- `profiles`: named compiler flag sets, each with an `evidence` locator. Units name a profile; per-unit or per-function flags are not accepted. Each unit compiles once; there is no retry.
- An optional profile `source_root` (`directory`, `file_prefix`, `evidence`) compiles the library the way the original build did. For example, `{"directory": "src", "file_prefix": "../../../Source"}` compiles `src/Common/UIStudio/UISEvent.c` as `../../../Source/Common/UIStudio/UISEvent.c`. The compile runs from a generated directory three levels below a staging directory, whose `Source` is a symlink to the repository's `src/`. `__FILE__` then expands to the original relative spelling. The evidence for this convention is the target strings at `0x802B1DC4` and `0x802B1DF0` (`../../../Source/Common/UIStudio/…`; see the `unit-anchor` rows in [evidence.tsv](evidence.tsv)). Dependencies are resolved through the link, so the report still names repository files. Include directories are passed as absolute paths.
- `units`: a repository-relative `source`, its `profile`, an `evidence` locator for the boundaries, and one entry per compiled section: compiler `section` (`.text`, `.rodata`, `.sdata`, `.bss`, ...), placeholder `placement`, and exclusive `start`/`end` addresses. For example, a unit's `.rodata` may be placed in `.data3`. Every non-empty allocated compiled section must be configured, its size must equal its range, its alignment must fit the start address, code must go to a code section and uninitialized data to an uninitialized section. Ranges must lie inside one placeholder section and must not overlap.
- `externals`: curated non-neutral names with an address and evidence. Undefined references named `fn_XXXXXXXX` or `lbl_XXXXXXXX` (uppercase hexadecimal) resolve to that address without claiming a name. C++ sources must declare such labels `extern "C"`. Any other undefined symbol fails the build.

Resolved externals are defined at their offsets inside the original-byte object containing the address, which lets ngcld apply small-data relocations; `.data5` and `.data6` use the small-data section names from [analysis.json](analysis.json). A reference into another unit's configured range must name that unit's own symbol. Unit symbols may not duplicate externals, linker symbols, or another unit's definitions; a neutral label must be placed at its own address, and every defined unit symbol is checked at its final address in the linked ELF. Common symbols, unconfigured sections, size or alignment differences, linker diagnostics, and any output difference fail the build.

The report, `build/source/report.json`, records each unit's source and dependency hashes, profile and flags, and each section's configured range, compiled size, linked bytes and status. It also records the resolved externals and the linked/matched code and data totals. Bytes count as matched only when the complete output is identical; a failed comparison still writes the report with `complete: mismatch`, zero matched bytes, and per-range diagnostics. Uninitialized ranges have no bytes to compare; they count when their size and symbol placement check out and the complete output is identical.

dtk 1.8.4 quick analysis was evaluated for cutting original sections. With unit ranges in `splits.txt`, it stops because the inferred extents of relocation targets cross unit edges. It succeeds only after synthesized boundary symbols are added, and then it emits relocations whose targets may lie inside replaced ranges. GNU ld relinks the zero-unit image but rejects ProDG objects (`.symtab local symbol at index >= sh_info`), so source builds use ngcld only.

## Public progress

Successful builds of `main` publish the progress page. Until reviewed file/function mapping exists, its map represents executable sections, not original source units. Code totals use executable section sizes; data totals include loaded data and uninitialized memory, with overlapping loaded ranges excluded from BSS. Linked and matched measure source-object bytes from the source-build report, attributed to the executable sections that contain them; original bytes contribute zero. The report records SHA-256 hashes of the build inputs it trusts: `source_build.py`, `prodg_cc.py`, `setup_compiler.py`, `baseline.py`, both tool locks, `baseline.json` and `analysis.json`. The exporter rejects a report whose tooling hashes differ, whose unit ranges are not exactly the manifest's configured sections, or whose ranges overlap. It also rejects a report for another target or unit manifest, a report without an identical complete output, stale source or dependency hashes, and files under `src/` that are neither unit sources nor recorded dependencies. Configured units or source files without a report also stop the export. With no units, it reports zero.

### Nintendo SDK reuse

SDK imports retain the provenance in [CREDITS.md](../../CREDITS.md) and target ownership evidence in `evidence.tsv`. The public source build selects a reviewed library compiler profile: ProDG for the existing EA unit and CodeWarrior GC/1.2.5n for the imported Nintendo units. Both compilers come from the same pinned archive and use the same pinned Wibo; supporting build dependencies remain unchanged. The SDK path preserves native compiler objects, tracks source/header dependencies, and uses the existing complete-target comparison and measured progress checks.

To screen existing compiled SDK objects for reuse, write the candidate inventory to local research:

```sh
python3 tools/sdk_scan.py --original /path/to/main.dol --object-root /path/to/compiled/sdk --output scratch/sdk/candidates.json
```

The scanner masks only recognized relocation fields and distinguishes unique, ambiguous and absent fingerprints. A unique hit requires inspection of calls, globals, used types, data ownership and original unit boundaries before import. Short functions below 32 bytes need separate evidence. An absent hit can reflect dead stripping or a different SDK version. Candidate output is private research and never supplies progress. Matching SDK code still receives the accuracy and hostile-review passes; unsupported matching tricks in a reference remain excluded.

SDK units with `link_roots` support retained code and static data. Static section sizes, symbol identities and offsets must remain consistent with native compiler output; SN-generated BSS metadata is excluded from source ownership. The roots identify target-retained entry points; SN’s original linker retains their dependencies and discards unused library functions. A relocatable partial link determines placement using temporary SDA anchors chosen for SN’s range checks; those inspection addresses do not supply target addresses or progress. The final link consumes untouched native objects with target SDA bases. Retention is a linker operation, not a function-specific compiler setting. Source, headers, roots and tools are bound to the full-build report; no progress is accepted until the complete target matches.
