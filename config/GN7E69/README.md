# Original-object baseline

`baseline.json` records the DOL's section addresses, entry point, complete size, and hash. Section names are toolkit placeholders, not recovered original names or compilation-unit boundaries. The small-data bases are loaded into r13 and r2 at `0x80003108`–`0x80003114` in the target entry code.

The baseline splits the original executable into relocatable objects, links them with GNU binutils, converts the ELF back to DOL, and compares every output byte with the verified target. This demonstrates a working original-object relink, not the original compiler or linker identity, recovered source, or matching progress.

Toolkit v1.8.4's full function analysis fails on nonlocal control flow near `0x801ABD9C`. `quick_analysis` omits that inference pass for this baseline; relocation processing and the complete executable comparison still run. Function boundaries and source compilation must be established separately before using CI to accept reconstructed code. Generated objects, assembly, symbols, and binaries stay under ignored `build/`.
