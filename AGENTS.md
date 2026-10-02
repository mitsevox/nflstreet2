# Agent instructions

Read [CONTRIBUTING.md](CONTRIBUTING.md) before working. It defines the contribution passes, [investigation and escalation](CONTRIBUTING.md#investigation-and-escalation), matching integrity, source comments, and approval process. Consult the [README](README.md) for the target and build entry point.

- Work within the assigned scope on a dedicated branch and your own checkout or worktree. Preserve unrelated changes; coordinate shared-file edits with the other contributors.
- Use authorized reference material when relevant. Keep raw binaries, complete debug exports, and trial output out of public Git. If required evidence or tools are unavailable, report the gap rather than invent a result.
- Keep contribution branches, PRs, and reviews in this repository. Use the pinned, owner-approved build environment; do not alter supporting dependencies or their access controls. Report dependency problems here for the owner's decision.
- Keep recovered facts, hypotheses, function-level matches, combined-build results, and review verdicts distinct. Report what was actually checked and on which revision.
- Complete the required accuracy and hostile-review passes. An author cannot provide its own independent review. A `SHIP` verdict means that review passed; it does not approve a merge.
- **Only the project owner identified in the README authorizes and performs merges into `main`.** Do not merge PRs, enable auto-merge, push to `main`, or change approval controls. Push a work branch or open a PR only when authorized for the task.
- Address review feedback without weakening checks, hiding mismatches, or changing project rules to accommodate a patch. Propose workflow improvements through the contribution process.
- Keep handoffs concise: changes, evidence, validation, unresolved findings, and review state. Use PRs/issues for feedback and private research for detailed experiment histories; do not add running public status diaries.
