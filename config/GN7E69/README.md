# Original-object baseline

`baseline.json` records the DOL's section addresses, entry point, complete size, and hash. Section names are toolkit placeholders, not recovered original names or compilation-unit boundaries. The small-data bases are loaded into r13 and r2 at `0x80003108`–`0x80003114` in the target entry code.

The baseline splits the original executable into relocatable objects, links them with GNU binutils, converts the ELF back to DOL, and compares every output byte with the verified target. This demonstrates a working original-object relink, not the original compiler or linker identity, recovered source, or matching progress.

The provisional working compiler is ProDG 3.9.3, with Wibo 1.0.3 on the supported hosts. Downloads are verified against `tools/compiler-tools.json`. The isolated-stage wrapper produces native-driver-equivalent C/C++ objects, validates arguments and fresh outputs, normalizes dependency line endings, and stops the process group on timeout. It never retries with different flags or modifies compiled instructions. Compiler stages currently support POSIX hosts; macOS uses the x86-64 Wibo executable through the host's existing Rosetta support.

CI also checks ngcld's original-object relink against the complete target. A 48-byte diagnostic source reproduction is compatible with all five available ProDG versions and multiple optimization settings; it rejects `-G0` for that case. This establishes a usable toolchain, not a unique original compiler version or project-wide flag profile. Reconstructed units still need evidence for their compiler settings and source boundaries before entering the combined build.

Toolkit v1.8.4's full function analysis fails on nonlocal control flow near `0x801ABD9C`. `quick_analysis` omits that inference pass for this baseline; relocation processing and the complete executable comparison still run. Function boundaries and source compilation must be established separately before using CI to accept reconstructed code. Generated objects, assembly, symbols, and binaries stay under ignored `build/`.
