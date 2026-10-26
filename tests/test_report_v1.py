import copy
import json
from pathlib import Path
import re
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT/'tools'))
import report_v1


def leaf(name, address, size, matched, source=None, **extra):
    item = dict(name=name, kind='code', size=size, linked=0, matched=matched, fuzzy=float(matched),
                address=address, type='function', function_address=address, original_size=size, **extra)
    if source:
        item['source'] = source
    return item


class Fixture(unittest.TestCase):
    def setUp(self):
        functions = [leaf('fn_80000000', '0x80000000', 8, 8, 'src/a.c', complete=True),
                     leaf('fn_80000008', '0x80000008', 8, 4, 'src/a.c'),
                     leaf('fn_80000010', '0x80000010', 16, 16, comparison_source='src/b.c')]
        group = dict(name='src/a.c', kind='code', size=32, linked=0, matched=28, fuzzy=28.0,
                     boundary='likely', scope='game', children=functions)
        self.site = dict(schema=1, revision='a'*40, built_at='2026-10-25T00:00:00+00:00', target='GN7E69',
                         target_sha1='3561e946e9ff785b68692f87d2ba85d81fd2dcf4', baseline='verified',
                         measures=dict(code=dict(total=32, linked=0, matched=28, fuzzy=28.0),
                                       data=dict(total=4, linked=0, matched=0, fuzzy=0.0)),
                         functions=dict(total=3, exact=2, named=0, basis='provisional-analysis'),
                         file_counts=dict(total=1, exact=0, named=1, basis='mapped-file-inventory'),
                         sections=[dict(name='.text', kind='code', size=32, linked=0, matched=28, fuzzy=28.0,
                                        address='0x80000000'),
                                   dict(name='.data', kind='data', size=4, linked=0, matched=0, fuzzy=0.0,
                                        address='0x80100000')],
                         files=[group, dict(name='.data', kind='data', size=4, linked=0, matched=0, fuzzy=0.0,
                                           address='0x80100000', auto_generated=True)])
        self.ledger = dict(schema=1, target='GN7E69',
                           contributors={'alice': dict(id=7), 'bob': dict(id=9)},
                           entries=[dict(source='src/a.c', functions=['0x80000000', '0x80000008'],
                                         contributors=['alice', 'bob']),
                                    dict(source='src/b.c', functions=['0x80000010'], contributors=['bob'])])
        self.feed = dict(revision='a'*40, credited_functions=2,
                         contributors=[dict(login='bob', id=9, functions=2, pull_requests=[1, 2]),
                                       dict(login='alice', id=7, functions=1, pull_requests=[1])],
                         snapshots=[dict(revision='b'*40, built_at='2026-10-01T00:00:00Z',
                                         code=dict(linked=0, total=32), data=dict(linked=0, total=4),
                                         provenance=dict(kind='workflow-artifact', run=5, artifact=6,
                                                         report_sha256='c'*64)),
                                    dict(revision='a'*40, built_at='2026-10-25T00:00:00+00:00',
                                         code=dict(linked=0, total=32), data=dict(linked=0, total=4),
                                         provenance=dict(kind='verified-source-build', report_sha256='d'*64))])


class MapAndSummary(Fixture):
    def test_map_keeps_geometry_and_metrics_but_not_project_evidence_fields(self):
        document = report_v1.map_document(self.site)
        def fields(items):
            for item in items:
                yield set(item)
                yield from fields(item.get('children', []))
        self.assertEqual(document['schemaVersion'], 1)
        self.assertTrue(all(keys <= set(report_v1.NODE_FIELDS) for keys in fields(document['files'])))
        self.assertEqual(document['files'][0]['children'][1]['matched'], 4)
        self.assertNotIn('source', document['files'][0]['children'][0])
        self.assertIn('source', self.site['files'][0]['children'][0])  # input untouched

    def test_summary_carries_raw_bytes_and_inventories(self):
        summary = report_v1.summary(self.site)
        self.assertEqual(summary['code'], dict(totalBytes=32, linkedBytes=0, matchedBytes=28,
                                               fuzzyEquivalentBytes=28.0))
        self.assertEqual(summary['functions'], self.site['functions'])
        self.assertEqual(summary['files'], self.site['file_counts'])


class Contributors(Fixture):
    def test_function_ledger_uses_map_identities_and_matches_the_verified_feed(self):
        document = report_v1.contributors_document(self.site, self.feed, self.ledger)
        self.assertEqual(document['functions'], [dict(id='GN7E69:0x80000000:8', authors=[7, 9]),
                                                 dict(id='GN7E69:0x80000010:16', authors=[9])])
        self.assertEqual(document['contributors'], [dict(login='bob', id=9, functions=2),
                                                    dict(login='alice', id=7, functions=1)])
        self.assertEqual(document['credited_functions'], 2)

    def test_disagreement_with_the_feed_or_missing_credit_fails(self):
        feed = copy.deepcopy(self.feed); feed['contributors'][1]['functions'] = 2
        with self.assertRaisesRegex(ValueError, 'differs from the verified contributor feed'):
            report_v1.contributors_document(self.site, feed, self.ledger)
        ledger = copy.deepcopy(self.ledger); ledger['entries'].pop()
        with self.assertRaisesRegex(ValueError, 'lacks ledger attribution'):
            report_v1.contributors_document(self.site, self.feed, ledger)
        site = copy.deepcopy(self.site); site['functions']['exact'] = 3
        with self.assertRaisesRegex(ValueError, 'differ from the public inventory'):
            report_v1.contributors_document(site, self.feed, self.ledger)


class Timeline(Fixture):
    cut = dict(revision='b'*40, built_at='2026-10-01T00:00:00Z')

    def test_rows_through_the_cutover_are_inherited_and_later_rows_are_measured(self):
        rows = report_v1.timeline_document(self.site, self.feed, 1, 1, self.cut)['snapshots']
        self.assertEqual([r['provenance'] for r in rows], [
            dict(kind='inherited', record=self.feed['snapshots'][0],
                 source='nflstreet2 workflow-artifact run 5 artifact 6 report sha256:'+'c'*64),
            dict(kind='measured', source='nflstreet2 verified-source-build report sha256:'+'d'*64)])
        # The site's legacy-replacement rule: the record is the accepted row.
        record = rows[0]['provenance']['record']
        self.assertEqual({k: record[k] for k in ('revision', 'built_at', 'code', 'data')},
                         {k: rows[0][k] for k in ('revision', 'built_at', 'code', 'data')})

    def test_without_a_cutover_every_row_is_measured(self):
        rows = report_v1.timeline_document(self.site, self.feed, 1, 1)['snapshots']
        self.assertEqual([r['provenance']['kind'] for r in rows], ['measured', 'measured'])

    def test_a_row_never_changes_between_runs_or_when_history_grows(self):
        first = report_v1.timeline_document(self.site, self.feed, 1, 1, self.cut)['snapshots']
        self.assertEqual(first, report_v1.timeline_document(self.site, self.feed, 2, 3, self.cut)['snapshots'])
        feed = copy.deepcopy(self.feed)
        feed['snapshots'].append(dict(feed['snapshots'][1], revision='e'*40))
        site = dict(self.site, revision='e'*40)
        self.assertEqual(report_v1.timeline_document(site, feed, 3, 1, self.cut)['snapshots'][:2], first)

    def test_cutover_outside_the_history_fails(self):
        with self.assertRaisesRegex(ValueError, 'cutover is not in the verified history'):
            report_v1.timeline_document(self.site, self.feed, 1, 1,
                                        dict(revision='f'*40, built_at='2026-10-02T00:00:00Z'))
        with self.assertRaisesRegex(ValueError, 'cutover differs from the verified history'):
            report_v1.timeline_document(self.site, self.feed, 1, 1,
                                        dict(revision='b'*40, built_at='2026-10-02T00:00:00Z'))

    def test_a_seed_history_ending_before_the_cutover_is_all_inherited(self):
        # PR runs see only the committed seed, which ends before the pinned legacy cutover.
        cut = dict(revision='f'*40, built_at='2026-10-26T00:00:00Z')
        rows = report_v1.timeline_document(self.site, self.feed, 1, 1, cut)['snapshots']
        self.assertEqual([r['provenance']['kind'] for r in rows], ['inherited', 'inherited'])
        feed = copy.deepcopy(self.feed); feed['snapshots'].pop()
        rows = report_v1.timeline_document(self.site, feed, 1, 1, cut)['snapshots']
        self.assertEqual([r['provenance']['kind'] for r in rows], ['inherited', 'measured'])

    def test_committed_history_config_has_no_cutover_until_the_site_switches(self):
        history = json.loads((ROOT/report_v1.HISTORY).read_text())
        self.assertEqual(history, dict(schemaVersion=1, inheritedThrough=None))

    def test_pull_request_merge_is_appended_as_candidate_evidence(self):
        feed = copy.deepcopy(self.feed); feed['snapshots'].pop()
        rows = report_v1.timeline_document(self.site, feed, 40, 2, self.cut)['snapshots']
        self.assertEqual(rows[-1]['revision'], 'a'*40)
        self.assertEqual(rows[-1]['provenance']['kind'], 'measured')
        self.assertEqual(rows[-1]['code'], dict(total=32, linked=0))
        self.assertEqual(rows[-1]['provenance']['source'], 'nflstreet2 pull-request candidate run 40 attempt 2')

    def test_unknown_history_provenance_fails(self):
        feed = copy.deepcopy(self.feed); feed['snapshots'][0]['provenance'] = dict(kind='guess')
        with self.assertRaisesRegex(ValueError, 'Unknown history provenance'):
            report_v1.timeline_document(self.site, feed, 1, 1)


class ProducerPolicy(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.workflow = (ROOT/report_v1.WORKFLOW).read_text()
        cls.template = json.loads((ROOT/'config/GN7E69/report-v1-producer.json').read_text())

    def test_policy_names_real_single_workflow_steps_and_artifact(self):
        names = re.findall(r'(?m)^      - name: (.+)$', self.workflow)
        for name in self.template['requiredSteps'] + sum(self.template['lanes'].values(), []):
            with self.subTest(name=name):
                self.assertEqual(names.count(name), 1)
        self.assertEqual(self.template['artifact'], report_v1.ARTIFACT)
        self.assertIn(f'          name: {report_v1.ARTIFACT}\n', self.workflow)
        self.assertEqual(re.findall(r'(?m)^  (\w+):\n    name: Toolchain baseline$', self.workflow), ['baseline'])

    def condition(self, name):
        block = self.workflow.split('      - name: '+name+'\n', 1)[1].split('      - ', 1)[0]
        return re.search(r'^        if: (.+)$', block, re.M).group(1)

    def test_every_pull_request_validates_but_only_a_publishable_proof_uploads(self):
        for name in ('Prepare report-v1 inputs', 'Check out pinned site report packager',
                     'Set up site packager runtime', 'Package and validate report-v1'):
            with self.subTest(name=name):
                self.assertEqual(self.condition(name),
                                 "github.ref == 'refs/heads/main' || github.event_name == 'pull_request'")
        self.assertEqual(self.condition('Upload report-v1 package'),
                         "github.ref == 'refs/heads/main' || "
                         "(github.event_name == 'pull_request' && steps.measure.outputs.reused == '0')")
        self.assertEqual(self.condition('Upload report-v1 package'),
                         self.condition('Upload verified publication handoff').replace(
                             "github.event_name == 'pull_request' && steps.measure.outputs.reused == '0'",
                             "github.ref == 'refs/heads/main' || "
                             "(github.event_name == 'pull_request' && steps.measure.outputs.reused == '0')"))

    def test_environment_is_pinned_and_template_never_approves_workflows(self):
        environment = re.search(r'(?m)^      BUILD_ENVIRONMENT: (\S+)$', self.workflow).group(1)
        policy = report_v1.policy(ROOT, environment, 'e'*40)
        self.assertEqual(policy['workflowBlobs'], ['e'*40])
        self.assertNotIn('workflowBlobs', self.template)
        with self.assertRaisesRegex(ValueError, 'another build environment'):
            report_v1.policy(ROOT, 'ghcr.io/other@sha256:'+'0'*64, 'e'*40)


if __name__ == '__main__':
    unittest.main()
