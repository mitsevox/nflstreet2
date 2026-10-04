# Work in progress

Reconstructions that are not linked into the source build yet. Each one is
kept here, outside `src/` and `include/`, so the original bytes stay linked
and the file earns no progress credit until it matches. The layout mirrors
the main tree: move `wip/src/...` and `wip/include/...` back into `src/` and
`include/` and configure the unit in `config/GN7E69/units.json` once it
matches in the complete source build.

| Unit | Files | Open gap |
| --- | --- | --- |
| cu_80068154 (SndgPathfinder) | `src/game/SndgPathfinder.cpp`, `include/game/SndgPathfinder.h` | two .rodata pool items, see evidence.tsv and issue #159 |
