# decomp.dev reporting

The Baseline workflow exports `build/GN7E69/report.json` and uploads it as the
`GN7E69_report` artifact, independently of the `github-pages` artifact. After the
owner merges this integration and a default-branch run succeeds, a repository
admin can register the project at <https://decomp.dev/manage/new>.

The exporter uses [objdiff's v2 protobuf JSON schema](https://github.com/encounter/objdiff/blob/main/objdiff-core/protos/report.proto).
See the [integration guide](https://decomp.wiki/tools/decomp-dev). The private
build environment and its permissions do not need to change.

To export locally after a verified source build:

```sh
python3 tools/decomp_report.py --dol build/source/main.dol --revision "$(git rev-parse HEAD)"
```

Both exports call `tools/progress.py`'s validation of the complete executable,
source manifest, source and dependency hashes, build-tool hashes, and measured
ranges. Original-object relinking earns no source progress. Code/data totals
include the entire executable's loaded sections and non-overlapping BSS; only
verified source ranges earn matched and complete byte credit.

Both maps display measured source units, SDK mappings, and bounded candidate
unit records from `evidence.tsv`. Candidate names do not claim recovered source
paths; their units remain incomplete and `auto_generated`. Ambiguous overlapping
candidate ranges remain unmapped. Mapping never grants source progress or alters
the executable denominator. The Baseline workflow checks both exports against
current mapping before uploading either artifact, on PRs and every merge to `main`.
