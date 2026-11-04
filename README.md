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
3. `python3 build.py check` relinks the original objects with GNU ld and with SN's ngcld, runs the tool tests that need the toolchain, and checks that the committed unit-boundary proposal in `config/GN7E69-rev0/boundaries/` equals a fresh run of `tools/boundaries.py` (`python3 tools/boundaries.py --write` updates it). That the site's publish script accepts the report is CI's `Check the report` step, on every pull request and push.

The tools are downloaded on first use and checked against the versions and hashes pinned in `tools/baseline-tools.json`, `tools/compiler-tools.json` and `tools/matching-tools.json`. `python3 build.py configure --dtk PATH --binutils DIR --compilers DIR --wibo PATH --objdiff PATH` uses tools already installed instead; the build image does this.

## Tools for closing a file

After one `python3 build.py`:

| Command | What it does |
| --- | --- |
| `python3 tools/trial.py src/game/X.cpp [function ...] [--diff]` | Compiles one file and compares each function (all of them, or the ones named by symbol or `0x` address) with the original in about a second; exit 0 when all are identical and use the original's constants. |
| `python3 tools/trial.py src/game/X.cpp fn --dump DIR` | The same, keeping ProDG's per-pass RTL dumps (`-da`, or `--dump-flags dl,dg`) in `DIR`, outside the repository or under `build/`: why a register or an instruction order differs. |
| `python3 tools/rename.py OLD NEW --evidence "..."` | Renames a function, label, type or class in `src/`, `include/`, `evidence.tsv` subjects and the unit configs, mangled spellings included, and records `--evidence` as the new name's own row (evidence text is never rewritten); `--check` lists compiled names, externals and evidence rows that disagree. |
| `python3 tools/files_closed.py` | Counts closed files (linked, descriptive file name, every function and label named with an evidence row; Nintendo SDK data labels keep the SDK's names without a row each) and writes what keeps each other file open to `build/GN7E69-rev0/files.tsv`; `build.py` runs it. |
| `python3 tools/sibling_tables.py nascar-units` / `ps2-map --ps2 DIR` | Regenerates NASCAR 2005's compile-unit table and the GameCube-to-PS2 function map under `references/`. |

A function that is exact but unlinked also has its constants checked: each literal it loads from its own file's data must hold the original's bytes, or the build fails.

## CI and the progress site

`.github/workflows/validate.yml` builds the target in the private build image and publishes each measurement to the [progress site](https://mitsevox.github.io/games/nflstreet2/) on `main`. Pull requests publish nothing.

## Contributing

The project owner is **[mitsevox](https://github.com/mitsevox)**, the sole merge authority. See [CONTRIBUTING.md](CONTRIBUTING.md) for the tiers, the task loop and the review checklist; agents start with [AGENTS.md](AGENTS.md).

## Layout

| Directory | Purpose |
| --- | --- |
| `src/`, `include/` | Reconstructed source and headers; version differences under `#if VERSION_<ID>` (`include/version.h`) |
| `src/game/` | NFL Street 2's own game code, mostly C++ (front end, gameplay, AI, replay, audio direction, rendering of players and field), 0x800034A0-0x801AA640 |
| `src/engine/` | EA Tiburon's shared engine and libraries in C and C++ (memory, resources, T3DB database, TM renderer, particles, sound, input, animation, the viewport manager at 0x8002AE90) and the SN and C runtime support code, mostly 0x801AA640-0x8023873C and 0x8025E148-0x80285A90 |
| `src/dolphin/` | Nintendo's GameCube SDK (OS, DVD, GX, VI, PAD, CARD, AX and the rest), built with CodeWarrior |
| `src/Common/` | EA code shared across titles under its original `Source/Common` path: the UIStudio menu engine |
| `docs/` | [subsystems.md](docs/subsystems.md): the map of the executable by area, with file names, ladder rungs and held areas |
| `config/GN7E69-rev0/` | The target's units, comparisons, analysis inputs, `build.sha1` and `evidence.tsv` |
| `orig/GN7E69-rev0/` | Where the original goes locally; ignored by Git |
| `build/` | Generated; ignored |
| `build.py`, `tools/`, `tests/` | The build entry, the kit tools and the project's own, with their tests |
| `references/` | Reference material from related builds |

## Credits and licenses

Imported source is credited in [CREDITS.md](CREDITS.md).
