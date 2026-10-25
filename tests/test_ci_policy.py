import argparse
import ast
import re
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools'))
import ci_policy


class ValidationLanes(unittest.TestCase):
    def test_successful_proof_with_warm_cache_requires_neither_rebuild(self):
        self.assertEqual(ci_policy.lanes(True, True), {'full':False, 'inventory':False, 'receipts':False})

    def test_successful_proof_with_cold_cache_requires_only_inventory(self):
        self.assertEqual(ci_policy.lanes(True, False), {'full':False, 'inventory':True, 'receipts':False})

    def test_cache_can_never_substitute_for_missing_execution_proof(self):
        for hit in (True, False):
            with self.subTest(hit=hit):
                self.assertEqual(ci_policy.lanes(False, hit), {'full':True, 'inventory':True, 'receipts':True})

    def test_pull_requests_skip_only_the_repeated_host_receipt_export(self):
        for hit in (True, False):
            with self.subTest(hit=hit):
                self.assertEqual(ci_policy.lanes(False, hit, True), {'full':True, 'inventory':True, 'receipts':False})

    def test_invalid_decisions_fail_closed(self):
        for value in ('', 'TRUE', '1', 'yes'):
            with self.subTest(value=value), self.assertRaises(argparse.ArgumentTypeError):
                ci_policy.boolean(value)
        for value in ('false', 0, None):
            with self.subTest(value=value), self.assertRaises(ValueError):
                ci_policy.lanes(value, True)
            with self.subTest(value=value), self.assertRaises(ValueError):
                ci_policy.lanes(False, True, value)
        self.assertTrue(ci_policy.boolean('true'))
        self.assertFalse(ci_policy.boolean('false'))


class HostedCacheBootstrap(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.workflow = (Path(__file__).resolve().parents[1] / '.github/workflows/baseline.yml').read_text()

    def condition(self, step, event, ref, requested, full):
        block = self.workflow.split('      - name: ' + step + '\n', 1)[1].split('      - ', 1)[0]
        expression = re.search(r'^        if: (.+)$', block, re.M).group(1)
        for name, value in {'github.event_name': event, 'github.ref': ref,
                            'inputs.audit_build_cache': requested,
                            'steps.validation.outputs.full': str(full).lower()}.items():
            expression = expression.replace(name, repr(value))
        expression = expression.replace('&&', ' and ').replace('||', ' or ').replace('!', 'not ')
        expression = re.sub(r"(?<![\w'])true(?![\w'])", 'True', expression)
        tree = ast.parse(expression, mode='eval')
        self.assertTrue(all(isinstance(node, (ast.Expression, ast.BoolOp, ast.And, ast.Or,
                            ast.UnaryOp, ast.Not, ast.Compare, ast.Eq, ast.Constant))
                            for node in ast.walk(tree)))
        return eval(compile(tree, '<workflow condition>', 'eval'), {'__builtins__': {}})

    def test_seed_input_is_typed_and_opt_in(self):
        block = self.workflow.split('      audit_build_cache:\n', 1)[1].split('\npermissions:', 1)[0]
        self.assertRegex(block, r'(?m)^        type: boolean$')
        self.assertRegex(block, r'(?m)^        default: false$')

    def test_only_explicit_main_audit_bypasses_proof_and_can_seed_after_full_validation(self):
        main = 'refs/heads/main'
        cases = [('push', main, False, True, True, True),
                 ('workflow_dispatch', main, True, True, False, True),
                 ('workflow_dispatch', main, False, True, True, False),
                 ('workflow_dispatch', 'refs/heads/work', True, True, False, False),
                 ('pull_request', 'refs/pull/1129/merge', True, True, False, False),
                 ('workflow_dispatch', main, True, False, False, False),
                 ('push', main, False, False, True, False)]
        for event, ref, requested, full, selects, saves in cases:
            with self.subTest(event=event, ref=ref, requested=requested, full=full):
                self.assertEqual(self.condition('Select verified final-integration reports',
                                                event, ref, requested, full), selects)
                self.assertEqual(self.condition('Save audited build caches',
                                                event, ref, requested, full), saves)
        self.assertEqual(ci_policy.lanes(False, True),
                         {'full': True, 'inventory': True, 'receipts': True})


if __name__ == '__main__': unittest.main()
