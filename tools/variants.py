#!/usr/bin/env python3
"""Run tools/trial.py on many source variants of one function and rank them.

    python3 tools/variants.py SOURCE FUNCTION SPEC [--jobs N] [--limit N] [--seed S] [--first]
    python3 tools/variants.py src/game/CollideSegment.cpp CollideSegmentClosestPoints orders.txt
    python3 tools/variants.py src/game/Foo.cpp 0x80012345 forms.txt --list      count and name the variants

SOURCE is the file as units.json or comparisons.json names it, FUNCTION a symbol or a 0x target
address, as trial.py takes them. SPEC names regions of SOURCE and what to try in each (format
below). The variants are every combination of the regions' options, the unchanged file first;
with more than --limit of them, a seeded random sample of --limit is run, the unchanged file
always among it.

Each worker owns a private copy of this checkout (left out: .git, build/trial, build/variants,
build/matching, build/analysis and build/GN7E69-rev0; every symlink into the checkout repointed
into the copy). It writes a variant into its copy's SOURCE, runs its copy's trial.py on FUNCTION
with --diff, records the verdict, the score and the first differing instruction, and restores
the file before the next variant. The checkout this command runs from is only read, apart from
the results folder (--out, by default build/variants/<source>_<function>_<spec name>/):
results.tsv (one row per variant, written as each finishes), summary.txt (the ranked table of
this run's selection and the elapsed time) and best.diff (the best variant against the original
file). Credit still comes only from `python3 build.py`.

Results and reused --work copies are stamped with a hash of what trial.py reads besides the
variant: src/, include/, tools/ (but this file), config/ and build/source/report.json. A rerun with the same
spec, function, source text and stamp resumes, skipping the variants already done (TIMEOUT rows
are retried, ERROR rows only with --retry-errors); a changed stamp refuses the results (pass
--fresh) and recopies a reused copy. One run at a time holds a results folder or a --work folder.

A variant changes source text only. Before any trial, the command is refused when an option of
the spec adds a `#pragma`, `_Pragma`, `__attribute__` (or types.h's ATTRIBUTE_ALIGN and
AT_ADDRESS), `asm` or `##` token paste that the original file does not have. Occurrences are
the lines holding a form, found after line splices, comments, literals and digraphs are taken
out and compared with their literals kept: a line holding a form may move, but one that is
added or changed in any way (a pragma swapped, an asm register renamed) counts. Each variant is
checked the same way again just before its trial. This guards against plain and accidental forms; it is not a C preprocessor, so a
macro that builds such a form from innocent pieces defined elsewhere is the reviewer's to catch.
Compiler flags and profiles live in config/ and are never touched.

Spec format. Lines starting with `%%` are directives; the lines between them are source text,
copied exactly. Text outside a region is ignored (use it for notes).

    %% replace NAME           a region with alternatives; its option `orig` is the text as listed
    %% after ANCHOR           optional: find the region after the one occurrence of ANCHOR
    ...original lines...
    %% with ALT               an alternative named ALT (no lines: the region is deleted)
    ...replacement lines...
    %% end

    %% permute NAME           a region whose items are tried in every order
    %% after ANCHOR           optional, as above
    %% item ID
    ...lines...
    %% item ID
    ...lines...
    %% end

A region's original text (for a permute region, its items joined in the listed order) must
occur in SOURCE exactly once, or exactly once after its ANCHOR; regions may not overlap. Names
of regions, alternatives and items use letters, digits and `_ . + -`. A JSON
spec (a file ending in .json) holds the same thing:
{"regions": [{"replace": NAME, "after": ANCHOR, "old": TEXT, "with": {ALT: TEXT}},
             {"permute": NAME, "items": [[ID, TEXT], ...]}]}.
"""
import argparse
import hashlib
import collections
import fcntl
import json
import math
import os
from pathlib import Path
import queue
import random
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import threading
import time

ROOT = Path(__file__).resolve().parents[1]
# Left out of a worker's copy: history, other runs' outputs, and build outputs trial.py does not
# read (the comparison pairs, the inventory and the linked DOL), which are most of build/.
SKIPPED = {'.git', 'build/trial', 'build/variants', 'build/matching', 'build/analysis', 'build/GN7E69-rev0'}
# Source forms a variant may not add: per-function pragmas and attributes, inline assembly, and
# token pasting (which could build them). Each is matched in normalized text (normalize) and
# compared as a multiset of the lines it occurs on, so swapping one pragma for another is caught.
# ATTRIBUTE_ALIGN and AT_ADDRESS are include/dolphin/types.h's spellings of __attribute__.
FORBIDDEN = {'#pragma': re.compile(r'^[ \t]*#[ \t]*pragma\b'), '_Pragma': re.compile(r'\b_Pragma\b'),
             '__attribute__': re.compile(r'\b(?:__attribute__|ATTRIBUTE_ALIGN|AT_ADDRESS)\b'),
             'asm': re.compile(r'\b(?:__asm__|__asm|asm)\b'), '##': re.compile(r'##')}
LEXEMES = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|/\*.*?\*/|//[^\n]*', re.S)
NAME = re.compile(r'[A-Za-z0-9_.+-]+')
# What trial.py reads besides the variant, for the stamp.
STAMPED = ('src', 'include', 'tools', 'config')
VERDICT = re.compile(r'^(\S+?)(?: 0x([0-9A-F]{8}))?: (IDENTICAL|DIFFERS|WRONG CONSTANT|MISSING)\b(.*)$')
SCORE = re.compile(r'\(([\d.]+)%')
DIFF_ROW = re.compile(r'^  ! +([0-9A-F]+)  (.*)$')
RANK = {'IDENTICAL': 0, 'WRONG CONSTANT': 1, 'DIFFERS': 2, 'MISSING': 3, 'ERROR': 4, 'TIMEOUT': 5}
COLUMNS = ['index', 'variant', 'status', 'score', 'first_diff', 'seconds']


class SpecError(ValueError):
    pass


# The spec.

def parse_text(text):
    """The regions of a text spec, as dicts in the JSON spec's form."""
    regions, region, lines, label = [], None, None, None

    def close_block():
        if region is None or lines is None:
            return
        body = '\n'.join(lines)
        if region['kind'] == 'replace':
            if label is None:
                region['old'] = body
            else:
                region['with'][label] = body
        else:
            region['items'].append([label, body])

    for number, line in enumerate(text.split('\n'), 1):
        if not line.startswith('%%'):
            if lines is not None:
                lines.append(line)
            elif region is not None and line.strip():
                raise SpecError(f'line {number}: text in region {region["name"]} before its first %% item')
            continue
        words = line[2:].strip().split(None, 1)
        word, rest = (words[0], words[1] if len(words) > 1 else '') if words else ('', '')
        if word in ('replace', 'permute'):
            if region is not None:
                raise SpecError(f'line {number}: region {region["name"]} has no %% end')
            if not rest:
                raise SpecError(f'line {number}: %% {word} needs a name')
            region = {'kind': word, 'name': rest.strip(), 'after': None}
            region.update({'old': None, 'with': {}} if word == 'replace' else {'items': []})
            lines, label = ([] if word == 'replace' else None), None
        elif region is None:
            raise SpecError(f'line {number}: %% {word} outside a region')
        elif word == 'after':
            if (region['kind'] == 'replace' and lines) or region.get('items') or label is not None or not rest:
                raise SpecError(f'line {number}: %% after ANCHOR must come right after the region line')
            region['after'] = rest
        elif word == 'with' and region['kind'] == 'replace':
            close_block()
            label, lines = rest.strip(), []
            if not label or label == 'orig' or label in region['with']:
                raise SpecError(f'line {number}: alternative needs a new name other than orig')
        elif word == 'item' and region['kind'] == 'permute':
            close_block()
            label, lines = rest.strip(), []
            if not label or label in [i[0] for i in region['items']]:
                raise SpecError(f'line {number}: item needs a new name')
        elif word == 'end':
            close_block()
            regions.append(region)
            region, lines, label = None, None, None
        else:
            raise SpecError(f'line {number}: unknown directive %% {word}')
    if region is not None:
        raise SpecError(f'region {region["name"]} has no %% end')
    return regions


def parse_json(text):
    regions = []
    for entry in json.loads(text)['regions']:
        if 'replace' in entry:
            regions.append({'kind': 'replace', 'name': entry['replace'], 'after': entry.get('after'),
                            'old': entry['old'], 'with': dict(entry['with'])})
        elif 'permute' in entry:
            regions.append({'kind': 'permute', 'name': entry['permute'], 'after': entry.get('after'),
                            'items': [list(i) for i in entry['items']]})
        else:
            raise SpecError(f'region without replace or permute: {entry}')
    return regions


def load_spec(path):
    text = Path(path).read_text()
    regions = parse_json(text) if str(path).endswith('.json') else parse_text(text)
    if not regions:
        raise SpecError('the spec has no regions')
    names = [r['name'] for r in regions]
    if len(set(names)) != len(names):
        raise SpecError('two regions share a name')
    for r in regions:
        if r['kind'] == 'replace':
            if r['old'] is None or not r['old'].strip():
                raise SpecError(f'region {r["name"]} has no original text')
            if not r['with']:
                raise SpecError(f'region {r["name"]} has no %% with alternative')
            r['options'] = ['orig'] + list(r['with'])
        else:
            if len(r['items']) < 2:
                raise SpecError(f'region {r["name"]} needs two or more items')
            r['old'] = '\n'.join(text for _, text in r['items'])
            r['options'] = None  # every order, by index
        texts = [r['old']] + list(r.get('with', {}).values()) + [t for _, t in r.get('items', [])]
        if any(line.startswith('%%') for t in texts for line in t.split('\n')):
            raise SpecError(f'region {r["name"]}: a source line starts with %%')
        labels = [r['name']] + list(r.get('with', {})) + [i for i, _ in r.get('items', [])]
        if not all(isinstance(n, str) and NAME.fullmatch(n) for n in labels):
            raise SpecError(f'region {r["name"]}: names use letters, digits and _ . + - only')
        if r['kind'] == 'replace' and 'orig' in r['with']:
            raise SpecError(f'region {r["name"]}: orig is the original text, not an alternative')
        if r['kind'] == 'permute' and len({i for i, _ in r['items']}) != len(r['items']):
            raise SpecError(f'region {r["name"]}: two items share a name')
    return regions, hashlib.sha1(text.encode()).hexdigest()


def locate(regions, source_text):
    """Set each region's (start, end) in the source text; refuse a missing, repeated or overlapping one."""
    for r in regions:
        base = 0
        if r['after']:
            if source_text.count(r['after']) != 1:
                raise SpecError(f'region {r["name"]}: its anchor occurs {source_text.count(r["after"])} times, not once')
            base = source_text.index(r['after']) + len(r['after'])
        count = source_text.count(r['old'], base)
        if count != 1:
            where = ' after its anchor' if r['after'] else ''
            raise SpecError(f'region {r["name"]}: its original text occurs {count} times{where}, not once; '
                            'add context lines or an %% after anchor')
        start = source_text.index(r['old'], base)
        r['span'] = (start, start + len(r['old']))
    spans = sorted((r['span'], r['name']) for r in regions)
    for (a, name_a), (b, name_b) in zip(spans, spans[1:]):
        if b[0] < a[1]:
            raise SpecError(f'regions {name_a} and {name_b} overlap')


def sizes(regions):
    return [len(r['options']) if r['kind'] == 'replace' else math.factorial(len(r['items'])) for r in regions]


def nth_permutation(items, n):
    """The n-th order of items in lexicographic order of their positions (n=0 is the listed order)."""
    pool, order = list(items), []
    for k in range(len(pool), 0, -1):
        f = math.factorial(k - 1)
        order.append(pool.pop(n // f))
        n %= f
    return order


def choice(regions, index):
    """Variant number index (0 = the original file) as one choice per region, mixed-radix."""
    picks = []
    for r, size in zip(reversed(regions), reversed(sizes(regions))):
        index, digit = divmod(index, size)
        picks.append(r['options'][digit] if r['kind'] == 'replace' else nth_permutation(r['items'], digit))
    return list(reversed(picks))


def describe(regions, picks):
    parts = []
    for r, pick in zip(regions, picks):
        parts.append(f"{r['name']}={pick if r['kind'] == 'replace' else ','.join(i[0] for i in pick)}")
    return ';'.join(parts)


def render(regions, picks, source_text):
    out, at = [], 0
    for r, pick in sorted(zip(regions, picks), key=lambda p: p[0]['span']):
        start, end = r['span']
        out.append(source_text[at:start])
        if r['kind'] == 'replace':
            out.append(r['old'] if pick == 'orig' else r['with'][pick])
        else:
            out.append('\n'.join(text for _, text in pick))
        at = end
    out.append(source_text[at:])
    return ''.join(out)


def normalize(text):
    """Text as the preprocessor's later phases see it, roughly, twice over: (with string and
    character literals emptied, with them kept), both with the digraphs and trigraphs for # and the
    backslash mapped, line splices joined and comments blanked. Both have the same lines."""
    text = text.replace('??=', '#').replace('%:', '#').replace('??/', '\\').replace('\\\n', '')
    def blank(keep):
        return lambda m: ' ' if m.group(0).startswith('/') else (m.group(0) if keep else m.group(0)[0] * 2)
    return LEXEMES.sub(blank(False), text), LEXEMES.sub(blank(True), text)


def occurrences(text, pattern):
    """The lines holding a form, found where literals are emptied (a string that names a form is
    none) and compared with their literals kept (a changed argument is a changed form)."""
    emptied, kept = (t.split('\n') for t in normalize(text))
    return collections.Counter(re.sub(r'#\s*', '#', ' '.join(k.split()))
                               for e, k in zip(emptied, kept) if pattern.search(e))


def forbidden_added(original, variant):
    """The forbidden forms variant has that original does not, by normalized occurrence: a line
    holding one may move, but a changed or added one counts."""
    return [name for name, pattern in FORBIDDEN.items()
            if occurrences(variant, pattern) - occurrences(original, pattern)]


def option_variants(regions):
    """One pick list per option: each region's every alternative (a permute region reversed), the
    others original, for the fast check before a run."""
    base = [('orig' if r['kind'] == 'replace' else r['items']) for r in regions]
    for n, r in enumerate(regions):
        for option in (r['options'][1:] if r['kind'] == 'replace' else [list(reversed(r['items']))]):
            yield base[:n] + [option] + base[n + 1:]


def selection(total, limit, seed):
    """The variant numbers to run, the original (0) first."""
    if limit is None or total <= limit:
        return list(range(total))
    rest = random.Random(seed).sample(range(1, total), limit - 1)
    return [0] + sorted(rest)


# The worker copies.

def stamp(root):
    """A hash of what trial.py reads besides the variant (STAMPED and build/source/report.json)."""
    root, digest = Path(root), hashlib.sha1()
    paths = [root / 'build/source/report.json']
    for top in STAMPED:
        for directory, dirnames, filenames in os.walk(root / top):
            dirnames[:] = sorted(d for d in dirnames if d != '__pycache__')
            paths += [Path(directory) / f for f in sorted(filenames)
                      if (Path(directory) / f) != root / 'tools/variants.py']  # this tool is not trial.py's input
    for path in paths:
        digest.update(path.relative_to(root).as_posix().encode() + b'\0')
        if path.is_file():
            digest.update(hashlib.sha1(path.read_bytes()).digest())
    return digest.hexdigest()


def make_copy(root, destination):
    """Copy the checkout to destination without SKIPPED, then repoint symlinks that reach into root."""
    root, destination = Path(root).resolve(), Path(destination)

    def ignore(directory, names):
        relative = Path(directory).resolve().relative_to(root)
        return [n for n in names if (relative / n).as_posix() in SKIPPED]

    shutil.copytree(root, destination, symlinks=True, ignore=ignore)
    for directory, dirnames, filenames in os.walk(destination):
        for name in dirnames + filenames:
            path = Path(directory) / name
            if not path.is_symlink():
                continue
            target = Path(os.readlink(path))
            absolute = target if target.is_absolute() else (path.parent / target)
            absolute = Path(os.path.normpath(absolute))
            if absolute.is_relative_to(root):
                path.unlink()
                path.symlink_to(destination.resolve() / absolute.relative_to(root),
                                target_is_directory=(root / absolute.relative_to(root)).is_dir())
    return destination


def escapes(copy, root):
    """Symlinks in copy that still lead into root (none after make_copy)."""
    found = []
    for directory, dirnames, filenames in os.walk(copy):
        for name in dirnames + filenames:
            path = Path(directory) / name
            if path.is_symlink() and Path(os.path.realpath(path)).is_relative_to(Path(root).resolve()):
                found.append(path)
    return found


def write_file(path, text):
    """Replace path's contents in one step, so a reader never sees a half-written file."""
    temporary = path.with_name(path.name + '.variants-tmp')
    temporary.write_text(text)
    os.replace(temporary, path)


# One trial.

def enclosed(text):
    """Whether text is one parenthesized group: its first ( closes at its last character."""
    depth = 0
    for at, character in enumerate(text):
        depth += {'(': 1, ')': -1}.get(character, 0)
        if depth == 0:
            return at == len(text) - 1 and at > 0
    return False


def parse_trial(output, returncode):
    """(status, score, first differing instruction) from trial.py's output."""
    status, score, first = None, '', ''
    for line in output.splitlines():
        match = VERDICT.match(line)
        if match and status is None:
            status = match.group(3)
            if status == 'IDENTICAL':
                score, first = '100.00', match.group(4).strip()  # a note on constants not checked
            elif status == 'DIFFERS':
                found = SCORE.search(match.group(4))
                score = found.group(1) if found else ''
            elif status == 'WRONG CONSTANT':
                first = match.group(4).strip()
                if enclosed(first):
                    first = first[1:-1]
            continue
        row = DIFF_ROW.match(line)
        if row and status == 'DIFFERS' and not first:
            first = f'{row.group(1)}: ' + re.sub(r'\s{2,}', ' | ', row.group(2).strip())
    if status is None:
        lines = [l.strip() for l in output.splitlines() if l.strip()]
        errors = [l for l in lines if re.search(r'\berror\b', l, re.I)]  # the compiler's own message first
        status, first = 'ERROR', ((errors or lines)[0] if lines else f'trial.py exited {returncode}')[:300]
    return status, score, first


LIVE = set()  # running trial processes, killed with their children on an interrupt
LIVE_LOCK = threading.Lock()


def kill_group(process):
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except (ProcessLookupError, PermissionError):
        pass


def run_trial(copy, source, function, text, original, timeout):
    """(status, score, first difference, seconds); status None when trial.py was killed by a signal."""
    path = copy / source
    write_file(path, text)
    started = time.monotonic()
    try:
        # Its own session, so a timeout or an interrupt ends the compiler and objdiff with it.
        process = subprocess.Popen([sys.executable, 'tools/trial.py', source, function, '--diff'], cwd=copy,
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, start_new_session=True)
        with LIVE_LOCK:
            LIVE.add(process)
        try:
            output, _ = process.communicate(timeout=timeout)
            if process.returncode < 0:
                status, score, first = None, '', f'killed by signal {-process.returncode}'
            else:
                status, score, first = parse_trial(output, process.returncode)
        except subprocess.TimeoutExpired:
            kill_group(process)
            process.communicate()
            status, score, first = 'TIMEOUT', '', f'over {timeout} s'
        finally:
            kill_group(process)
            with LIVE_LOCK:
                LIVE.discard(process)
    finally:
        write_file(path, original)
    return status, score, first, time.monotonic() - started


# Results.

def header(spec_hash, source, source_text, function, checkout):
    """The results file's first line: a rerun resumes only for the same spec, function, source text
    and checkout stamp."""
    source_hash = hashlib.sha1(source_text.encode()).hexdigest()
    return f'# variants spec {spec_hash} source {source} {source_hash} function {function} checkout {checkout}'


def read_results(path, expected_header):
    if not path.is_file():
        return {}
    lines = path.read_text().splitlines()
    if not lines or lines[0] != expected_header:
        raise SpecError(f'{path} is from another spec, function, version of the source or state of the checkout; '
                        'pass --fresh to start over')
    rows = {}
    for line in lines[2:]:
        values = line.split('\t')
        if len(values) == len(COLUMNS):
            rows[int(values[0])] = dict(zip(COLUMNS, values))
    return rows


def ranked(rows):
    return sorted(rows.values(), key=lambda r: (RANK[r['status']], -float(r['score'] or -1), int(r['index'])))


def summary(rows, total, elapsed, source, function):
    order = ranked(rows)
    counts = {}
    for r in rows.values():
        counts[r['status']] = counts.get(r['status'], 0) + 1
    lines = [f'{source} {function}: {len(rows)} of {total} variants run, {elapsed:.1f} s this run',
             '  ' + ', '.join(f'{n} {s}' for s, n in sorted(counts.items(), key=lambda c: RANK[c[0]]))]
    if 0 in rows:
        lines.append(f"  original file: {rows[0]['status']} {rows[0]['score']}")
    lines.append('')
    lines.append('rank\tindex\tstatus\tscore\tvariant\tfirst_diff')
    for number, r in enumerate(order[:20], 1):
        lines.append(f"{number}\t{r['index']}\t{r['status']}\t{r['score']}\t{r['variant']}\t{r['first_diff']}")
    return '\n'.join(lines) + '\n'


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('source')
    parser.add_argument('function')
    parser.add_argument('spec', type=Path)
    parser.add_argument('--jobs', type=int, default=os.cpu_count() or 1, help='workers (default: the core count)')
    parser.add_argument('--limit', type=int, help='run at most this many variants (a seeded sample)')
    parser.add_argument('--seed', type=int, default=0, help='seed for the --limit sample (default 0)')
    parser.add_argument('--first', action='store_true', help='stop at the first IDENTICAL variant')
    parser.add_argument('--timeout', type=int, default=600, help='seconds per trial (default 600)')
    parser.add_argument('--out', type=Path, help='results folder (default build/variants/<source>_<function>_<spec name>)')
    parser.add_argument('--fresh', action='store_true', help='discard earlier results in the folder')
    parser.add_argument('--work', type=Path, help='folder for the worker copies (default: a new temporary one, '
                        'removed at the end); outside this checkout. Its copyN folders are the tool\'s own: one made '
                        'from another state of the checkout is replaced, one without its copyN.stamp is refused')
    parser.add_argument('--keep-work', action='store_true', help='leave the worker copies in place')
    parser.add_argument('--retry-errors', action='store_true', help='rerun variants recorded as ERROR')
    parser.add_argument('--list', action='store_true', help='print the variants and exit without running')
    args = parser.parse_args(argv)

    given = Path(args.source)
    if '..' in given.parts:
        raise SpecError(f'{args.source}: give SOURCE without ..')
    if given.is_absolute():  # e.g. a tab-completed path: use it relative to this checkout
        if not given.is_relative_to(ROOT):
            raise SpecError(f'{args.source} is not in this checkout')
        given = given.relative_to(ROOT)
    source = given.as_posix()
    source_path = ROOT / source
    if not source_path.is_file() or not source_path.resolve().is_relative_to((ROOT / 'src').resolve()):
        raise SpecError(f'{source} is not a file under src/')
    original = source_path.read_text()
    regions, spec_hash = load_spec(args.spec)
    locate(regions, original)
    total = math.prod(sizes(regions))
    if args.limit is not None and args.limit < 1:
        raise SpecError('--limit must be 1 or more')
    indices = selection(total, args.limit, args.seed)

    if args.list:
        for index in indices:
            print(f'{index}\t{describe(regions, choice(regions, index))}')
        print(f'{len(indices)} of {total} variants')
        return 0

    # Refuse forbidden forms before any trial runs: each option against the original file.
    for picks in option_variants(regions):
        added = forbidden_added(original, render(regions, picks, original))
        if added:
            raise SpecError(f"variant {describe(regions, picks)} adds {', '.join(added)}; "
                            'variants change source forms only')
    report = ROOT / 'build/source/report.json'
    if not report.is_file() or json.loads(report.read_text()).get('complete') != 'identical':
        raise SpecError('run `python3 build.py` once first; trial.py resolves against its build')

    out = args.out or ROOT / 'build/variants' / re.sub(r'[^A-Za-z0-9]+', '_', f'{source}_{args.function}_{args.spec.stem}').strip('_')
    work = args.work.resolve() if args.work else Path(tempfile.gettempdir()).resolve()
    if work.is_relative_to(ROOT.resolve()):
        raise SpecError('--work (or the temporary folder, TMPDIR) must be outside this checkout')
    out.mkdir(parents=True, exist_ok=True)
    with (out / '.lock').open('w') as holder:  # held until the run ends
        try:
            fcntl.flock(holder, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            raise SpecError(f'another run is using {out}')
        results = out / 'results.tsv'
        if args.fresh and results.exists():
            results.unlink()
        checkout = stamp(ROOT)
        expected = header(spec_hash, source, original, args.function, checkout)
        rows = read_results(results, expected)
        if not results.exists():
            results.write_text(expected + '\n' + '\t'.join(COLUMNS) + '\n')
        retried = {'TIMEOUT', 'ERROR'} if args.retry_errors else {'TIMEOUT'}
        pending = [i for i in indices if i not in rows or rows[i]['status'] in retried]
        if args.first and any(rows[i]['status'] == 'IDENTICAL' for i in indices if i in rows):
            pending = []

        started = time.monotonic()
        if not args.work:
            work = Path(tempfile.mkdtemp(prefix='variants-'))
        work.mkdir(parents=True, exist_ok=True)
        claim = (work / '.lock').open('w')  # one run at a time in a --work folder too
        try:
            fcntl.flock(claim, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            claim.close()
            raise SpecError(f'another run is using {work}')
        jobs = max(1, min(args.jobs, len(pending)))
        lock, stop, interrupted = threading.Lock(), threading.Event(), threading.Event()
        tasks = queue.Queue()
        for index in pending:
            tasks.put(index)
        failures, finished = [], set()

        def worker(number):
            try:
                copy = work / f'copy{number}'
                marker = copy.parent / f'copy{number}.stamp'
                if copy.exists() and not marker.is_file():
                    raise RuntimeError(f'{copy} has no {marker.name}, so this tool did not make it; move it away')
                if copy.exists() and marker.read_text() != checkout:
                    shutil.rmtree(copy)  # made from another state of the checkout
                if not copy.exists():
                    marker.unlink(missing_ok=True)
                    make_copy(ROOT, copy)
                    marker.write_text(checkout)
                if escapes(copy, ROOT):
                    raise RuntimeError(f'{copy} has symlinks into the checkout')
                write_file(copy / source, original)  # a reused copy starts from this checkout's file
                while not stop.is_set():
                    try:
                        index = tasks.get_nowait()
                    except queue.Empty:
                        return
                    picks = choice(regions, index)
                    text = render(regions, picks, original)
                    added = forbidden_added(original, text)
                    if added:  # a combination the option check could not see
                        raise RuntimeError(f"variant {describe(regions, picks)} adds {', '.join(added)}; not run")
                    status, score, first, seconds = run_trial(copy, source, args.function, text, original, args.timeout)
                    if interrupted.is_set():
                        return  # the trial was cut short with the run: not a result
                    if status is None:
                        raise RuntimeError(f'trial.py for variant {index} was {first}')
                    row = {'index': str(index), 'variant': describe(regions, picks), 'status': status, 'score': score,
                           'first_diff': first.replace('\t', ' '), 'seconds': f'{seconds:.1f}'}
                    with lock:
                        rows[index] = row
                        with results.open('a') as handle:
                            handle.write('\t'.join(row[c] for c in COLUMNS) + '\n')
                        finished.add(index)
                        done = len(finished)
                        print(f"[{done}/{len(pending)}] {status} {score} {row['variant']}", flush=True)
                        if args.first and status == 'IDENTICAL':
                            stop.set()
            except Exception as error:  # reported after the other workers finish
                with lock:
                    failures.append(f'worker {number}: {error}')
                stop.set()

        try:
            threads = [threading.Thread(target=worker, args=(n,)) for n in range(jobs)] if pending else []
            for t in threads:
                t.start()
            try:
                for t in threads:
                    t.join()
            except KeyboardInterrupt:
                interrupted.set()
                stop.set()
                with LIVE_LOCK:
                    for process in LIVE:
                        kill_group(process)
                for t in threads:
                    t.join()
                raise
        finally:
            claim.close()
            if not args.keep_work and not args.work:
                shutil.rmtree(work, ignore_errors=True)
        if source_path.read_text() != original:
            raise RuntimeError(f'{source} changed in this checkout while the variants ran')
        elapsed = time.monotonic() - started

        selected = {i: rows[i] for i in indices if i in rows}  # earlier rows outside this selection stay in the TSV
        text = summary(selected, len(indices), elapsed, source, args.function)
        (out / 'summary.txt').write_text(text)
        best = ranked(selected)[0] if selected else None
        if best:
            import difflib
            variant = render(regions, choice(regions, int(best['index'])), original)
            diff = difflib.unified_diff(original.splitlines(True), variant.splitlines(True), f'a/{source}', f'b/{source}')
            (out / 'best.diff').write_text(''.join(diff))
        print(text, end='')
        print(f'results in {out}')
        for failure in failures:
            print(failure, file=sys.stderr)
        return 2 if failures else 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (SpecError, RuntimeError, OSError, KeyError, json.JSONDecodeError) as error:
        sys.exit(f'variants: {error}')
    except KeyboardInterrupt:
        sys.exit('variants: interrupted; rerun the same command to resume')
