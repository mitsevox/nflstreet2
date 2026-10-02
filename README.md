# NFL Street 2

A faithful matching decompilation of **NFL Street 2 for the Nintendo GameCube**. The goal is to reconstruct source that compiles back to a byte-identical copy of the original game executable, with names, types, and source structure supported by evidence.

## Progress

See the [build page](https://mitsevox.github.io/nflstreet2/) for current matching progress and the latest build results.

## Target

USA release, **GN7E69**, disc revision **0**.

Original `main.dol` SHA-1:

```text
3561e946e9ff785b68692f87d2ba85d81fd2dcf4
```

## Building

You will need your own copy of the game. The initial original-object baseline supports Python 3.9 or newer on macOS ARM64 and Linux x86-64:

```sh
python3 tools/baseline.py --original /path/to/main.dol
```

This relinks and verifies the complete executable. Source compilation and matching-progress checks are still pending; see the [baseline scope](config/GN7E69/README.md).

To prepare the pinned working compiler and verify its stages:

```sh
python3 tools/setup_compiler.py
python3 -m unittest discover -s tests -v
```

Compiler verification does not establish flags for reconstructed source units.

## Contributing

The project owner is **Lucas ([mitsevox](https://github.com/mitsevox))**, the sole merge authority.

See [CONTRIBUTING.md](CONTRIBUTING.md) for the work and review process. AI agents start with [AGENTS.md](AGENTS.md).
