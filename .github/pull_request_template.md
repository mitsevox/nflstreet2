## Scope

Tier (A, B or C), task or issue, affected units or tools, dependencies, and unresolved work.

Closes: none
<!-- A PR that finishes files names them here, e.g. `Closes: src/engine/hash.c, src/game/FELoop.cpp`. CI fails unless each is closed in this build (tools/files_closed.py: linked, descriptive file name, every function and label named with an evidence row); the header comment, naming conventions, unit rows and both reviews are checked by the reviewers. CI reads this line at each push, not on a body edit: push after adding or changing it. Keep the claim on a line of its own that starts with `Closes:`, with every file on that line; any other line that pairs `closes:` with a file name fails the check; close an issue with `Closes #123`, without the colon. -->

<!-- Where contributors are on, a line `Credits: @login, @login` names who made this PR's functions exact; without it the PR author is credited. -->

## Targets

One row per active target. A shared change is safe for a target only when its row is filled from a build of that target.

| Target | Byte-identical | Units touched (Matching state there) | Progress delta (from the target's report) | Evidence rows added |
| --- | --- | --- | --- | --- |
| GN7E69-rev0 | yes / no | | | |

## Evidence and validation

Evidence records and the test and build commands with their results, per target. Identify what was checked; a baseline relink does not validate reconstructed source. For a file with a new `#if VERSION_` block, the `python3 tools/versions.py diff` output was read.

## Review

- Reviewed revision: full commit SHA
- Accuracy record (tier A): link, or justified N/A
- Hostile record (tiers A and B): link and verdict

Request the owner's decision only after the records and required CI cover the final revision. New substantive changes require renewed review. Contributors do not merge.
