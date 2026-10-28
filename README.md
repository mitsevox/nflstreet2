# NFL Street 2

A matching decompilation of **NFL Street 2** (GameCube, 2004). The goal is source that compiles back to a byte-identical copy of the original executable, with names, types and source structure supported by evidence.

## Targets

| Id | Region | Revision | Status | Original SHA-1 |
| --- | --- | --- | --- | --- |
| `GN7E69-rev0` | USA | 0 | active | `3561e946e9ff785b68692f87d2ba85d81fd2dcf4` |

`config/targets.json` is the registry; the target's inputs are in `config/GN7E69-rev0/`, described in its [README](config/GN7E69-rev0/README.md).

## Building

You need your own copy of the game disc. Keep disc images and extracted files outside public Git. The tools support Python 3.9 or newer on Linux x86-64 and macOS ARM64 (macOS runs Wibo through Rosetta).

1. Place the original at `orig/GN7E69-rev0/sys/main.dol`.
2. `python3 build.py` builds the reconstructed units in place of their original bytes, analyzes the executable, measures every registered comparison and writes `build/GN7E69-rev0/report.json`. It fails unless the complete executable matches `config/GN7E69-rev0/build.sha1`, and ends with `build/GN7E69-rev0/main.dol: OK`.
3. `python3 build.py check` relinks the original objects with GNU ld and with SN's ngcld, runs the tool tests that need the toolchain, and checks that the site's publish script accepts the report.

The tools are downloaded on first use and checked against the versions and hashes pinned in `tools/baseline-tools.json`, `tools/compiler-tools.json` and `tools/matching-tools.json`. `python3 build.py configure --dtk PATH --binutils DIR --compilers DIR --wibo PATH --objdiff PATH` uses tools already installed instead; the build image does this.

## CI and the progress site

`.github/workflows/validate.yml` builds the target in the private build image and publishes each measurement to the [progress site](https://mitsevox.github.io/games/nflstreet2/) on `main`. Pull requests publish nothing.

## Contributing

The project owner is **[mitsevox](https://github.com/mitsevox)**, the sole merge authority. See [CONTRIBUTING.md](CONTRIBUTING.md) for the tiers, the task loop and the review checklist; agents start with [AGENTS.md](AGENTS.md).

## Layout

| Directory | Purpose |
| --- | --- |
| `src/`, `include/` | Reconstructed source and headers; version differences under `#if VERSION_<ID>` (`include/version.h`) |
| `config/GN7E69-rev0/` | The target's units, comparisons, analysis inputs, `build.sha1` and `evidence.tsv` |
| `orig/GN7E69-rev0/` | Where the original goes locally; ignored by Git |
| `build/` | Generated; ignored |
| `build.py`, `tools/`, `tests/` | The build entry, the kit tools and the project's own, with their tests |
| `docs/`, `references/` | Durable project knowledge and reference material from related builds |

## Credits and licenses

Imported source is credited in [CREDITS.md](CREDITS.md).
