# Contributing

Recover plausible original source, supported by evidence. A byte match establishes compiler equivalence; it does not establish correct names, types, source boundaries or intent. The [README](README.md) identifies the targets, the project owner and the build setup.

## Authority and tiers

Contributions contain source, tools and reviewed metadata. Do not publish original game binaries, disc images or assets. Keep experiments and bulk research out of public Git. Clone the repository and follow the [build setup](README.md#building); use your own checkout and a dedicated branch (`git switch -c your-task`). Contribution branches, PRs, reviews and required CI checks belong in this repository: CI builds only branches of this repository, and a fork's pull request is rejected before any private input is used. Use the owner-approved build environment at its pinned digest; report missing inputs or tooling problems in an issue for the owner's decision rather than changing a dependency.

**Only the project owner ([mitsevox](https://github.com/mitsevox)) authorizes and performs merges into `main`.** Contributors and agents prepare branches, submit PRs and review changes. A reviewer verdict or passing CI never grants merge authority. Nobody pushes to `main`, enables automatic merging, or changes branch rules, repository settings or the build image.

What protects matching integrity, in order: CI proves the complete executable of every affected target is byte-identical and measures each unit per target; the matching-integrity rules below; a reviewer who did not write the code reads reconstructed source against the disassembly and the evidence before an inferred name or boundary is published; the owner decides what merges. Everything else is proportionate to what a PR touches. State the tier in the PR's Scope line (`Tier A`, `Tier B` or `Tier C`). CI's `Check the declared tier` step fails a PR that claims less than its diff needs: `splits.txt`, `symbols.txt`, an `inferred` evidence row or a compiler or linker profile means at least A, other source means at least B. The floor is a minimum; reviewers and the owner raise the tier when the change calls for it.

| Tier | Touches | Required before merge |
| --- | --- | --- |
| A | `src/` or `include/` with new or changed inferred names, types, fields or unit boundaries; `splits.txt`; `symbols.txt`; compiler profiles | CI green, one blind accuracy record, one hostile record |
| B | `src/` or `include/` where every name and layout is `target`, `signature` or `related` (library imports, already-named code); promotions from `NonMatching` to `Matching` | CI green, one hostile record |
| C | `tools/`, `tests/`, `docs/`, `references/`, workflows, `config/*.json`, root documents | CI green |

## The task loop

1. **Claim.** Check open PRs and branches. Open a draft PR early with the unit names and target ids in its title; that is the reservation, and it ends when the PR closes.
2. **Establish boundaries and types.** Inspect the target and the reference evidence before reconstructing. Search existing headers and accepted units before declaring a shared address. A related build is corroboration, not proof of the target layout.
3. **Reconstruct and match.** Recover source in the original codebase's style. Compile, compare instructions and data with objdiff, and investigate the remaining uncertainty with controlled experiments. Keep discarded variants local; retain useful partial reconstruction as a `NonMatching` object so CI measures it. Promotion to `Matching` does not move the source file.
4. **Name and explain.** Record provenance for recovered names, types, fields and boundaries in `config/<target id>/evidence.tsv` using the [evidence format](config/README.md). Cite the actual loads, stores and caller or callee behavior for inferred widths and signatures. Keep readable names distinct from claims of original names; unresolved functions keep the tool's address label. Comments explain intent and invariants, never scores, compiler notes or process; the one exception is the `// FAKEMATCH:` label (Matching integrity).
5. **Check every target.** Build every active target and confirm `build.sha1` on each; run objdiff per target for each touched unit; run `python3 tools/versions.py diff` on every file you added a version block to; add evidence rows to each affected target's `evidence.tsv`. Fill the Targets table of the PR template from these results.
6. **Review.** Tier A: an independent reviewer interprets the scoped functions with the proposed names and comments withheld, reconciles that interpretation with the submission and posts an `Accuracy:` record; then a fresh reviewer applies the hostile checklist and posts a `Hostile:` record. Tier B: the hostile record only. Tier C: none. Resolve every finding by fixing it or providing evidence.
7. **Submit for the owner's decision.** Required CI passes on the final revision with no unexplained regression; the records cover that revision and name the targets they checked.

In this repository the loop works one whole file at a time, and a file is not finished when it matches and links. AGENTS.md, "Closing a file", gives the seven steps every file PR follows in order: match every function, link the file, name and place the file, name every function, label and type, give each name, type and boundary its evidence row, work the file to `closed` in `build/GN7E69-rev0/files.tsv`, then the two reviews. All seven happen in the same PR, and the owner's rule asks for both the accuracy and the hostile record on it whatever tier the table above would give. Until a file closes, a function nobody has read may keep its address label (step 4 above); closing the file names it.

Partial reconstructed functions may be committed, submitted and merged before reaching 100% byte equality. A measured mismatch alone is not a review failure. Review source fidelity, evidence and comparison integrity separately from completeness; document mismatches and open questions.

A version difference lives in the shared file under `#if VERSION_<DEFINE>` (`include/version.h` states the rule). When a function would carry three or more blocks, or more than about a third of its lines inside blocks, write the whole function once per variant under one function-level `#if`, in the same file. A unit that matches on some targets only is `Object(MatchingFor("<id>"), ...)`; a unit absent from a target is absent from that target's `splits.txt`.

## Matching integrity

Nobody will know exactly what the original source looked like, and there is rarely direct evidence for it. The working test for every source form, compiler profile and build choice is the owner's (2026-11-14): the developers could reasonably, in theory, have written or built it this way, and it gives the best result available. Reviewers accept what passes that test and keep the lines below.

**Accepted.** These need an evidence row that gives the reasoning; best-evidence hunches are accepted when nothing in the target contradicts them.

- Compiler choices at the file or library level: a file or library that builds with its own flags gets its own named profile (for example `-fno-strength-reduce` for the speech, sound and CSIS code, or fast math for `CurveList.c`), and a separately built library may use another compiler version (CodeWarrior GC/1.3 for the VM library). Real builds made these choices per file and per library.
- Source forms that 2004 game code plausibly contains even when nothing else shows them: a dead store, accessor definitions that inline away, an unused static, an extern that only a discarded function reads. A form like these that is present only to reproduce the bytes, such as an unused stack object for the frame size, a repeated test or a flag that is never set, is a fake match and needs both labels below.
- Labeled fake matches, under the conditions below.

**Fake matches.** A fake match is a form that is in the source only to reproduce the bytes and that nothing in the target or a related build shows the original had: an unused stack object that sets the frame size, an unreachable repeated test, a never-set flag that keeps strings referenced. It is accepted only when all four hold:

1. The function is truly stuck: natural forms were tried within the time box and none matches.
2. It does not change the logic. The function and its file do exactly what the target does on every path, so a port built from this source behaves the same.
3. It is not egregious (see below).
4. It is labeled twice: a `// FAKEMATCH: <what is fake and why>` comment on the line or block it affects (`/* FAKEMATCH: ... */` where a compiler rejects `//`), and a `source-form` evidence row at the function whose evidence column starts with `FAKEMATCH:` and says what was tried. `git grep -n "FAKEMATCH:"` lists every site, in source and in `evidence.tsv`. This comment is the one exception to keeping matching notes out of source.

A fake match that meets these conditions is not a review failure; one that is unlabeled, changes logic or is egregious is.

**Still banned.** These are egregious, and a function that needs one stays a registered partial:

- Per-function flags, `#pragma`s (optimization, scheduling, peephole and the like) or compiler attributes that steer one function's code generation. The only exception is a form the original source is shown to have used, with the owner's approval; a guess that the SDK might have had one is not that (`GXPerf.c`, ruled on #1334).
- Inline assembly, embedded instruction bytes or patched compiler output standing in for compiled source. Originally handwritten assembly needs provenance.
- Altered symbol boundaries, excluded comparisons or progress categories that conceal mismatches.
- Any change to behavior made to satisfy the compiler.

A declaration or statement order found by trying variants is an ordinary source form when it reads naturally, otherwise a labeled fake match. Reviewers judge what is egregious; when a form is in doubt, the PR asks the owner. Build-tool mechanisms that link a derived object instead of the untouched compiler object (the `folded` map, and the COMMON storage map and `kept_locals` that #1338 adds) are owner exceptions, each use named in AGENTS.md, and a new use needs the owner's approval. A new compiler version, such as CodeWarrior GC/1.3, is a tool and pin change made in its own PR.

Outside `// FAKEMATCH:` comments, put compiler reasoning, exception evidence and matching experiments in metadata or the PR, not in reconstructed source. Preserve original assertions and diagnostics when the target requires them.

## Evidence

Each target keeps its claims in `config/<target id>/evidence.tsv`; [config/README.md](config/README.md) defines the columns, kinds and origins, and `python3 tools/evidence.py check` enforces the format in CI. A row is a claim a reviewer can challenge: an inferred name, a unit boundary, a type or field layout, a compiler profile. Tool output is one row per tool run, naming the tool, its inputs and revision and the regenerable report, not one row per hit.

## Hostile-review checklist

The first reviewer must be independent of the reconstruction and its prior reasoning. Supply the scoped source and headers, target disassembly and relevant data, provenance records, unit boundaries, compiler settings, comparison configuration and validation results for an identified revision. References must be accessible to the reviewer; absent essential evidence is a blocked check, not permission to assume correctness.

Review all submitted reconstructed functions, including partial ones:

| Check | Required result |
| --- | --- |
| Source fidelity | Behavior and source structure are supported by the target and references and pass the Matching integrity test. Every fake-match form carries its `// FAKEMATCH:` comment and `source-form` row and leaves the logic unchanged; nothing on the banned list is used. A labeled, logic-preserving fake match is not a failure. |
| Compiler settings | Compiler and flags are chosen per file or per library through named profiles, each with an evidence row that gives its reasoning; a plausible, uncontradicted profile is accepted. Per-function overrides fail unless the original is shown to have used them and the owner approved. |
| Types and layouts | Declarations reflect available evidence, including sizes, offsets, signatures and shared ownership. Unknowns are explicit; no fabricated layouts or match-only substitutes. |
| Provenance and licence | Imported code names its source repository, pinned commit and licence in `CREDITS.md` ("no licence" is stated, not omitted); a licence that requires its text has it under `licenses/`; copyright and licence notices in imported files are intact. Check the source repository itself, not only the PR's claim. |
| Names | Provenance supports original-name claims. Inferred names are reasoned in their evidence rows, uncontradicted by the target and not presented as recovered facts, to the target's declared evidence regime; a rejection names a contradicting observation, a better-supported name, or a row that gives no reason. |
| Comments | Comments clarify meaning and readability without obvious narration, speculation, compiler explanations or process notes; `// FAKEMATCH:` labels are required where they apply and are not a failure. Absence of an unnecessary comment is not a failure. |
| Unit boundaries | Splits and code/data ownership are supported to the target's declared evidence regime. Provisional boundaries are identified; no artificial fragmentation or grouping to inflate progress; a rejection names a contradicting observation, a better-supported edge, a row that gives no reason, or an `exact` grade its evidence does not establish. |
| Comparison integrity | No patched output, excluded comparisons, altered symbol ranges or misleading categories conceal mismatches. Partial and linked results remain distinct. |
| Validation | Required checks cover the reviewed revision, complete target output, unit code/data and regressions against the base revision. No substituted scores or unverified success claims. |

Report `PASS`, `FAIL`, `BLOCKED` or a justified `N/A` for each check. Findings identify the file/line or configuration location, supporting evidence, and required correction or missing information. Do not invent what the original author would have written or treat stylistic preference as evidence.

End with the reviewed revision and one verdict: `SHIP` (no unresolved failures or blocked checks), `FIX` (localized corrections), `REDO` (unsupported tricks or fundamental reconstruction problems) or `BLOCKED` (essential evidence or validation unavailable). A verdict does not authorize merging.

After fixes, apply the delta recheck rules above. In the final record, cite the earlier review, list the checked changes and finding resolutions, and identify carried-forward coverage. Newly discovered defects may still be reported on unchanged code. Additional changes require coverage and validation for the resulting revision; an old verdict alone does not cover new changes.

## Review records

Post each pass as a separate PR comment. The first line is `Revision: FULL_COMMIT_SHA`, the second `Targets: <ids checked>`, the third the verdict: `Accuracy: PASS` or `Accuracy: N/A - <reason>` for the accuracy pass, `Hostile: SHIP`, `Hostile: FIX`, `Hostile: REDO` or `Hostile: BLOCKED` for the hostile pass. Each header occurs once, outside quotes and code fences. Then the reviewer's identity and prior involvement, the scope, the evidence used, the findings and their resolution. A record covering one target never reads as covering another. Do not write a successful record before the review happens.

For an inferred name or edge, 'not enough evidence' alone is not a finding: a rejection names a contradicting observation, an alternative the target supports better, a row that gives no reason, or an edge graded `exact` that its evidence does not establish; a reviewer who prefers another name or edge without one records a note, not a `FIX`.

**Rechecks.** After fixes, the reviewer checks each prior finding, the correction and its affected behavior, declarations, callers, boundaries and evidence, and carries unchanged coverage forward by linking the earlier record and its revision. A replacement reviewer may continue from that record. A full restart needs a concrete reason that invalidates coverage across the PR; a localized defect is not one.

**Refreshes.** After refreshing from `main`, verify the diff, conflict resolutions and affected shared declarations, then post final-revision records that cite the earlier ones and name the checked delta. An earlier verdict alone does not cover the new head. When source or build inputs change, earlier CI cannot substitute for final-revision validation.

**Batches.** Compatible bounded contributions may be integrated in one PR with each original PR, author revision and review coverage identified. Review the combined delta and affected dependencies and require final-revision records and CI. Compiler-profile and comparison changes get their own review and never ride along in unrelated work.

## Credits

A repository that sets `"contributors": true` in `config/site.json` publishes who made each exact function exact; the site ranks them. A function is credited to the people of the merge that made it exact in the earliest `main` build where it was exact, so a function that regresses and returns keeps its first credit. Name them on one line of the PR body, `Credits: @login, @login`; without that line the PR author is credited. When credits are switched on, every function already exact is credited to the owner. A batch that carries other people's work, an import, or a correction lists its functions in `config/<target id>/credits.tsv` (address, comma-separated logins, reason), which wins over the merge's credit and is reviewed like any other record. CI's `Check the credits` step checks the line and the file before merge.

## Feedback

Use PR discussions for review findings and issues for unresolved research or recurring tool problems. Keep detailed failed experiments in private research. Correct recurring failures at their cause instead of repeating workarounds. Change permanent instructions through a focused PR when the agreed process needs correction; do not rewrite the rules to justify the current patch.
