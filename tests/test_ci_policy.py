import argparse
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools'))
import ci_policy


class ValidationLanes(unittest.TestCase):
    def test_successful_proof_with_warm_cache_requires_neither_rebuild(self):
        self.assertEqual(ci_policy.lanes(True, True), {'full':False, 'inventory':False})

    def test_successful_proof_with_cold_cache_requires_only_inventory(self):
        self.assertEqual(ci_policy.lanes(True, False), {'full':False, 'inventory':True})

    def test_cache_can_never_substitute_for_missing_execution_proof(self):
        for hit in (True, False):
            with self.subTest(hit=hit):
                self.assertEqual(ci_policy.lanes(False, hit), {'full':True, 'inventory':True})

    def test_invalid_decisions_fail_closed(self):
        for value in ('', 'TRUE', '1', 'yes'):
            with self.subTest(value=value), self.assertRaises(argparse.ArgumentTypeError):
                ci_policy.boolean(value)
        for value in ('false', 0, None):
            with self.subTest(value=value), self.assertRaises(ValueError):
                ci_policy.lanes(value, True)
        self.assertTrue(ci_policy.boolean('true'))
        self.assertFalse(ci_policy.boolean('false'))


if __name__ == '__main__': unittest.main()
