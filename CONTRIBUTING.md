# Contributing

Recover plausible original source, supported by evidence. A byte match establishes compiler equivalence; it does not establish correct names, types, source boundaries, or intent. The [README](README.md) identifies the target, project owner, and build setup.

## Setup and authority

Contributions contain source, tools, and reviewed metadata. Do not publish original game binaries, assets, or complete debug exports. Keep experiments and bulk research out of public Git.

Clone the repository and follow the [build setup](README.md#building). Arrange access to any required reference material with the project owner. Checkout locations are a local choice; a contributor workflow must not depend on another person's absolute paths.

Contribution branches, PRs, reviews, and required CI checks belong in this repository. Use the owner-approved build environment at its pinned version. Supporting build dependencies are maintained by the owner; contributors and agents must not change them to accommodate a patch. Report missing inputs or tooling problems in an issue here for the owner's decision.

**Only the project owner authorizes and performs merges into `main`.** Contributors and agents may prepare branches, submit PRs, and review changes. A reviewer verdict or passing CI never grants merge authority. Contributors must not push directly to `main` or enable automatic merging.

## Work and review passes

1. **Claim a bounded task.** Use an issue or draft PR to state the unit, scope, and shared-file dependencies. Work on a dedicated branch from current `main`, in your own checkout or worktree. Coordinate overlapping changes before starting.
2. **Establish boundaries and types.** Inspect the target and reference evidence before reconstructing the unit. Use shared declarations; do not invent local substitutes to obtain a match. Record unknowns explicitly. A related build is corroboration, not proof of the target layout.
3. **Reconstruct and match.** Recover source in the original codebase's style. Keep trial variants local. Per-function comparisons are diagnostic; the combined build is the final output check.
4. **Name and explain.** Include provenance for recovered names, types, fields, and boundaries in reviewed metadata. Keep readable names distinct from claims of original names. Comments follow the standard below.
5. **Self-check.** Verify the complete target binary, unit code and data, and regressions against the base revision. List unresolved functions and shared-file changes. Do not claim a function score proves a complete unit.
6. **Blind accuracy review.** An independent reviewer examines the scoped functions with proposed names and comments withheld, then reconciles its interpretation against the evidence. Record disagreements and their resolution in the PR.
7. **Hostile review.** A fresh reviewer applies the checklist below. Resolve every finding by fixing it or providing evidence. The same reviewer rechecks findings and affected code after fixes; substantive reconstruction changes return through the relevant passes.
8. **Submit for the owner's decision.** Required CI must pass on the final PR revision, with no unexplained regression. Attach the reviewed revision, validation results, accuracy review, and hostile-review verdict. Only the project owner may accept and merge it.

Partial units follow the same accuracy and hostile-review gates. Their original assembly remains linked until replacement is validated; partial source is not reported as a completed unit. Retain unresolved identifiers when evidence is insufficient rather than fabricate recovery.

For changes with dependencies on other PRs, identify those dependencies and tested revisions. Documentation-only changes require appropriate checks, not an invented binary-validation result.

## Matching integrity

Do not manufacture a match through unsupported compiler or comparison manipulation:

- No per-function flags, optimization pragmas, or compiler attributes introduced to force code generation.
- No inline assembly, embedded instruction bytes, or patched compiler output substituting for originally compiled source.
- No invented helpers, casts, volatile qualifiers, padding, or control flow whose only justification is obtaining matching bytes.
- No altered symbol boundaries, excluded comparisons, or progress categories that conceal mismatches.
- No behavioral changes made to satisfy the compiler.

Compiler versions and flags need evidence at the original compilation-unit or library level. A function-specific exception requires evidence that the original used it and the project owner's explicit approval. Originally handwritten assembly likewise requires provenance.

An evidence-supported source form may be identified through its compiler output. A suspected fake match remains a local experiment, outside accepted source, unless the project owner explicitly authorizes a documented exception. A `fake match` label is not permission. Otherwise leave the original assembly linked and the recovery unresolved.

Put compiler reasoning, exception evidence, and matching experiments in metadata or the PR, not explanatory matching comments in reconstructed source. Preserve original assertions and diagnostics when the target requires them.

## Source readability and comments

Names, types, and structure should carry most of the readability. The source should read as a coherent original codebase with helpful clarification.

Comments explain intent, meaningful behavior, invariants, or non-obvious relationships using vocabulary supported by the code and references. Do not narrate obvious statements or require a comment on every function.

Keep matching scores, compiler explanations, agent notes, review history, and speculative claims out of source comments. Uncertainty and provenance belong in evidence records or the PR. Do not turn a hypothesis into an authoritative name or comment.

## Hostile-review checklist

The first reviewer must be independent of the reconstruction and its prior reasoning. Supply the scoped source and headers, target disassembly and relevant data, provenance records, unit boundaries, compiler settings, comparison configuration, and validation results for an identified revision. References must be accessible to the reviewer; absent essential evidence is a blocked check, not permission to assume correctness.

Review all submitted reconstructed functions, including partial ones:

| Check | Required result |
| --- | --- |
| Source fidelity | Behavior and source structure are supported by the target and references; no unsupported matching tricks. |
| Compiler settings | Compiler and flags have evidence at the appropriate scope. Inspect per-function overrides and verify evidence and owner approval for any exception. |
| Types and layouts | Declarations reflect available evidence, including sizes, offsets, signatures, and shared ownership. Unknowns are explicit; no fabricated layouts or match-only substitutes. |
| Names | Provenance supports original-name claims. Inferred names describe what the code establishes without presenting guesses as recovered facts. |
| Comments | Comments clarify meaning and readability without obvious narration, speculation, compiler explanations, or process notes. Absence of an unnecessary comment is not a failure. |
| Unit boundaries | Splits and code/data ownership have evidence. Provisional boundaries are identified; no artificial fragmentation or grouping to inflate progress. |
| Comparison integrity | No patched output, excluded comparisons, altered symbol ranges, or misleading categories conceal mismatches. Partial and linked results remain distinct. |
| Validation | Required checks cover the reviewed revision, complete target output, unit code/data, and regressions against the base revision. No substituted scores or unverified success claims. |

Report `PASS`, `FAIL`, `BLOCKED`, or a justified `N/A` for each check. Findings identify the file/line or configuration location, supporting evidence, and required correction or missing information. Do not invent what the original author would have written or treat stylistic preference as evidence.

End with the reviewed revision and one verdict: `SHIP` (no unresolved failures or blocked checks), `FIX` (localized corrections), `REDO` (unsupported tricks or fundamental reconstruction problems), or `BLOCKED` (essential evidence or validation unavailable). A verdict does not authorize merging.

After fixes, the same reviewer rechecks previous findings and affected code. Newly discovered defects may still be reported on unchanged code. Additional changes require review coverage and validation for the resulting revision; an old verdict does not cover new changes.

## Feedback

Use PR discussions for review findings and issues for unresolved research or recurring tool problems. Keep detailed failed experiments in private research. Correct recurring failures at their cause instead of repeating workarounds.

Change permanent instructions through a focused PR when the agreed process needs correction. Identify affected accepted code or tools and propose the necessary revalidation; do not rewrite the rules to justify the current patch. Workflow changes also require the project owner's approval.
