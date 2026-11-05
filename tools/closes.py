#!/usr/bin/env python3
"""Check a pull request's `Closes:` line against the closed-file count of the build just made.

    python3 tools/closes.py                      in CI, after `python3 build.py`
    python3 tools/closes.py --body FILE          locally: check a PR body you are writing

A PR that finishes a file says so in its body with one line, `Closes: src/engine/hash.c` (several
files separated by commas; `Closes: none` or no line when it closes nothing). Every file it names
must be closed on this revision as tools/files_closed.py measures it (build/<target>/files.tsv):
linked, descriptive file name, every function and label named with an evidence row. A file that
is not closed fails the check with what keeps it open. The rest of the done rule (header comment,
naming conventions, unit rows, both reviews) is the reviewers' to confirm, as AGENTS.md says.
Outside pull requests the check passes.

The check reads the body CI was started with, on each push (validate.yml runs on GitHub's default
pull_request types, which leave out `edited`, as for tools/tier.py's Tier line). A `Closes:` line
added or changed after the last push is checked only by the next push, so push after editing it,
and the owner's clearance confirms the final body against the final run. Running the check on body
edits would need either a second workflow, which the site's scaffold check rejects (validate.yml is
the only one), or `edited` runs of validate.yml. Those are safe only when they run the whole
pipeline (a skipped job's result would replace the push run's on the same commit), which costs a
full build for every body edit; that is the owner's call.
"""
import argparse
import json
import os
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
TARGET = 'GN7E69-rev0'
# A `Closes:` line, also as a list item, quote or heading and in bold or italics. The keyword may
# be in inline code (`Closes:` or `Closes`:) only when a source path or `none` follows it; otherwise
# a code-formatted keyword is a mention of the syntax, as in prose about this check.
LINE = re.compile(r'^[ \t>#*_-]*(?:(?P<code>`Closes`[ \t]*:|`Closes:`)|[*_]*Closes[*_]*[ \t]*:[*_]*)[ \t]*(?P<rest>.*)$',
                  re.IGNORECASE)
MENTION = re.compile(r'\bcloses[*_]*\s*:', re.IGNORECASE)
COMMENT = re.compile(r'<!--.*?-->', re.DOTALL)
PATH = re.compile(r'`?(?:none|[\w.-]+(?:/[\w.-]+)+\.\w+)`?[,\s]*', re.IGNORECASE)


def claimed(body):
    """The source paths a PR body's `Closes:` lines name, in order; [] when none. Text inside HTML
    comments (the template's example) and in inline code is ignored. A line that mentions `closes:`
    in any other form is refused rather than skipped, so a claim can never pass unchecked."""
    files = []
    for line in COMMENT.sub('', body or '').splitlines():
        match = LINE.match(line)
        if match and match['code'] and not PATH.match(match['rest']):
            match = None  # `Closes:` followed by words: a mention of the syntax, not a claim.
        if match is None:
            if MENTION.search(re.sub(r'`[^`]*`', '', line)):  # Inline code is a mention, not a claim.
                raise ValueError(f'cannot read this Closes line; write it as `Closes: <path>, <path>`: {line.strip()}')
            continue
        for item in re.split(r'[,\s]+', match['rest'].strip()):
            item = item.strip('`*_')
            if item and item.lower() not in ('none', '-', 'n/a'):
                files.append(item)
    return files


def check(files, table):
    """Problems for each named file that files.tsv does not list as closed."""
    rows = {}
    lines = table.read_text().splitlines()
    header = lines[0].split('\t')
    for line in lines[1:]:
        row = dict(zip(header, line.split('\t')))
        rows[row['source']] = row
    problems = []
    for path in files:
        row = rows.get(path)
        if row is None:
            problems.append(f'{path}: not a source file the build links or the comparisons register')
        elif row['closed'] != 'yes':
            reasons = []
            if row['linked'] != 'yes':
                reasons.append('not wholly linked' if row['linked'] == 'partly' else 'not linked')
            if row['file_named'] != 'yes':
                reasons.append('the file name is built on an address')
            if row['placeholders'] != '0':
                reasons.append(f"{row['placeholders']} placeholder name(s)")
            if row['unevidenced'] != '0':
                reasons.append(f"{row['unevidenced']} name(s) without an evidence row")
            examples = f" (e.g. {row['examples']})" if row.get('examples') else ''
            problems.append(f"{path}: not closed: {', '.join(reasons)}{examples}")
    return problems


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--body', type=Path, help='a PR body to check instead of the pull request event')
    args = parser.parse_args()
    if args.body:
        body = args.body.read_text()
    elif os.environ.get('GITHUB_EVENT_NAME') == 'pull_request':
        body = json.loads(Path(os.environ['GITHUB_EVENT_PATH']).read_text())['pull_request'].get('body')
    else:
        print('closes: not a pull request, nothing to check')
        return 0
    try:
        files = claimed(body)
    except ValueError as error:
        sys.exit(f'closes: {error}')
    if not files:
        print('closes: the PR closes no file')
        return 0
    table = ROOT / 'build' / TARGET / 'files.tsv'
    if not table.is_file():
        sys.exit(f'closes: {table.relative_to(ROOT)} is missing; run python3 build.py first')
    problems = check(files, table)
    for problem in problems:
        print(problem)
    if problems:
        print(f'closes: {len(problems)} of {len(files)} file(s) the PR closes are not closed on this revision')
        return 1
    print(f"closes: {', '.join(files)} closed on this revision (reviews and the rest of the rule: see AGENTS.md)")
    return 0


if __name__ == '__main__':
    sys.exit(main())
