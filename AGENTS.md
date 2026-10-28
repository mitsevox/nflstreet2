# Agent instructions

Read [CONTRIBUTING.md](CONTRIBUTING.md) before working: it defines the review tiers, the task loop, matching integrity, the evidence records and the hostile-review checklist. The [README](README.md) names the targets, the owner and the build commands.

- Keep original executables, disc images, assets, official SDK files (headers, libraries, documentation) and trial output out of public Git, and never discuss leaked material in public. Use the pinned, owner-approved build environment and do not alter supporting dependencies or their access controls; report dependency problems in an issue for the owner's decision.
- Work on a dedicated branch in your own checkout or worktree. Open a draft PR early with the unit names and target ids in its title; check open PRs before starting. Preserve unrelated changes and coordinate live overlaps on shared files.
- Keep recovered facts, hypotheses, function-level matches, combined-build results and review verdicts distinct. Report what was actually checked, on which revision and for which targets.
- Preserve useful partial reconstruction in normal source files as `NonMatching` objects so CI measures it. Original bytes stay in the verified linked build until promotion. Matching incompleteness alone is not a review failure.
- Record evidence for names, boundaries, types and compiler profiles in `config/<target id>/evidence.tsv` ([format](config/README.md)) in the same PR as the change it supports.
- State the PR's tier in its Scope line and complete the records that tier requires. An author cannot provide its own independent review. A `SHIP` verdict means that review passed; it does not approve a merge.
- **Only the project owner authorizes and performs merges into `main`.** No agent enables auto-merge, pushes to `main`, force-pushes `main` or another contributor's branch, or changes branch rules, repository settings, the build image or its digest. Push a work branch or open a PR only when authorized for the task, then leave it for the owner's decision.
- Address review feedback without weakening checks, hiding mismatches or changing project rules to accommodate a patch. Propose workflow improvements through a separate PR.
- Keep handoffs concise: changes, evidence, validation per target, unresolved findings and review state. Do not add running status diaries to the repository.
- A function becomes exact only with its name, its evidence and its comment in the same PR; there is no later naming pass.
- Never delete a file you have not checked first: make the delete depend on the check. Edit C, C++ and headers with an editor or a saved script whose diff you read, never with sed, heredocs, echo or `python -c` (they mangle backslashes).
- Ask the owner before downloads, purchases, posts or messages anywhere. Tokens and secrets are the owner's to create and store; never ask for their values.
- Working with the owner: plain, short English that says what each code area does in the game; the concept first, then the owner's green light, then small steps; numbers exactly as measured, never estimated by feel. At every change of project phase, re-read these rules and ask the owner about any rule written for the previous phase.

Before calling a shared change safe for every target, an agent has done four things, per active target:

1. Built every active target and confirmed `config/<target id>/build.sha1` on each.
2. Run objdiff per target for each touched unit and reported the `Matching` state and progress delta in the PR's Targets table.
3. Run `python3 tools/versions.py diff` on every file it added a `#if VERSION_` block to, and read the result.
4. Added evidence rows to each affected target's `evidence.tsv`.

## Project

- **What it is.** NFL Street 2 for the GameCube (EA, 2004). One target, `GN7E69-rev0` (USA, revision 0; `main.dol` SHA-1 `3561e946e9ff785b68692f87d2ba85d81fd2dcf4`). The build needs `orig/GN7E69-rev0/sys/main.dol`.
- **Build.** This repository has no `configure.py` or dtk-template: `python3 build.py` is the build entry (README). It runs `tools/source_build.py` (the units in `config/GN7E69-rev0/units.json` linked with SN's `ngcld` in place of their address ranges, every other byte from the original), the provisional function inventory (`tools/analyze.py`), the comparisons (`tools/matching.py`) and the report; `python3 build.py check` runs the original-object relinks and the toolchain tests; CI's `Check the report` step does the report check on every event. Without `build.py configure` the scripts download the tools pinned in `tools/*-tools.json`. [config/GN7E69-rev0/README.md](config/GN7E69-rev0/README.md) is the reference for every rule below.
- **Toolchain.** EA game code is SN ProDG 3.9.3 through Wibo; the imported Nintendo SDK units are CodeWarrior GC/1.2.5n. Flags are named profiles in `units.json`, each with evidence; per-unit or per-function flags are rejected. `source_root` reproduces EA's `../../../Source/...` spelling of `__FILE__`.
- **Partial work is a registered comparison, not a `NonMatching` object.** Register a partial or exact-but-unlinked function in `config/GN7E69-rev0/comparisons.json`; in a file that already contributes linked source, keep the draft bodies behind `#if defined(DECOMP_COMPARE)`. Promotion removes the guard and adds the range to `units.json`; the source path never changes. The header's `NonMatching` rule means this here.
- **Exact and linked.** A function is exact when its compiled bytes equal the target's; it is linked only when its range is in the byte-identical source build. A unit is complete on the site when all of it is linked; `confirmed` additionally needs `unit` evidence for its exact boundaries.
- **Owner exceptions.** The `folded` map and its two `Class_802938C0` folds in `cu_80005668` are the owner's approved exception (config README, Nintendo SDK reuse); any further use needs separate approval.
- **Investigation.** Choose by the open question: disassembly, references and Ghidra for what the target does; ProDG RTL dumps for why plausible source compiles differently; a bounded headless-Dolphin trace for runtime behavior. Record the question, tool version, result and remaining uncertainty in the evidence or the review record; keep databases and dumps private.
- **References.** `references/` holds strings, symbols and an `ANALYSIS.md` per related EA build (NFL Street, NFL Street 3, FIFA 2005, NASCAR 2005, GoldenEye: Rogue Agent, Medal of Honor: European Assault, other NFL Street 2 builds and a prototype). A related build is corroboration, not proof of this target's layout.
- **Credits are on.** Every exact function is credited (CONTRIBUTING.md, Credits); the credits from the earlier ledger are carried into the data repository unchanged by mitsevox/decomp-data#1.
