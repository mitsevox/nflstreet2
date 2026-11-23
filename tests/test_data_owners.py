"""Tests for tools/data_owners.py: which data addresses a function's instructions form."""
import contextlib
import io
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import data_owners


def d_form(op, rd, ra, immediate):
    return (op << 26) | (rd << 21) | (ra << 16) | (immediate & 0xFFFF)


SDA = {13: 0x803F22A0, 2: 0x804022A0}


class FunctionReferences(unittest.TestCase):
    def references(self, words):
        return [target for _, target in data_owners.function_references(words, 0x80010000, SDA)]

    def test_lis_then_addi_load_and_store_form_addresses(self):
        words = [d_form(15, 3, 0, 0x8030), d_form(14, 4, 3, 0x1234),    # lis r3; addi r4,r3,0x1234
                 d_form(15, 5, 0, 0x8031), d_form(32, 6, 5, -8),         # lis r5; lwz r6,-8(r5)
                 d_form(36, 6, 5, 0x10)]                                 # stw r6,0x10(r5)
        self.assertEqual(self.references(words), [0x80301234, 0x8030FFF8, 0x80310010])

    def test_small_data_bases_and_ori(self):
        words = [d_form(32, 3, 13, -0x7F00), d_form(48, 1, 2, 0x10),     # lwz r3,-0x7f00(r13); lfs f1,0x10(r2)
                 d_form(15, 4, 0, 0x802C), d_form(24, 4, 4, 0x8000)]     # lis r4; ori r4,r4,0x8000
        self.assertEqual(self.references(words), [0x803F22A0 - 0x7F00, 0x804022B0, 0x802C8000])

    def test_overwritten_register_no_longer_names_its_lis(self):
        words = [d_form(15, 3, 0, 0x8030), d_form(14, 3, 3, 0x100),      # lis r3; addi r3,r3,0x100
                 d_form(32, 4, 3, 8),                                    # lwz r4,8(r3): a member, not tracked
                 d_form(15, 5, 0, 0x8030), d_form(32, 5, 5, 0),          # lis r5; lwz r5,0(r5)
                 d_form(32, 6, 5, 4),                                    # lwz r6,4(r5): r5 is a loaded value
                 d_form(15, 7, 0, 0x8030), (21 << 26) | (7 << 21) | (7 << 16),  # lis r7; rlwinm r7,r7,...
                 d_form(32, 8, 7, 0)]
        self.assertEqual(self.references(words), [0x80300100, 0x80300000])

    def test_unreadable_word_forgets_every_lis(self):
        words = [d_form(15, 3, 0, 0x8030), None, d_form(32, 4, 3, 0)]
        self.assertEqual(self.references(words), [])

    def test_ra_zero_is_the_literal_zero(self):
        words = [d_form(15, 0, 0, 0x8030), d_form(14, 3, 0, 0x10),       # lis r0; li r3,0x10
                 d_form(32, 4, 0, 0x20)]                                 # lwz r4,0x20(0)
        self.assertEqual(self.references(words), [])

    def test_addis_lmw_calls_and_paired_single_updates_forget_registers(self):
        cases = [
            [d_form(15, 3, 0, 0x8030), d_form(15, 3, 4, 1), d_form(32, 5, 3, 0)],     # addis r3,r4,1
            [d_form(15, 30, 0, 0x8030), d_form(46, 29, 1, 8), d_form(32, 5, 30, 0)],  # lmw r29: r30 too
            [d_form(15, 3, 0, 0x8030), (18 << 26) | 0x100 | 1, d_form(32, 5, 3, 0)],  # bl clobbers r3
            [d_form(15, 3, 0, 0x8030), (57 << 26) | (1 << 21) | (3 << 16) | 8, d_form(32, 5, 3, 0)],  # psq_lu
        ]
        for words in cases:
            self.assertEqual(self.references(words), [], words)
        # A callee-saved register survives a call.
        words = [d_form(15, 31, 0, 0x8030), (18 << 26) | 0x100 | 1, d_form(32, 5, 31, 4)]
        self.assertEqual(self.references(words), [0x80300004])


class Output(unittest.TestCase):
    def test_output_outside_the_repository(self):
        with tempfile.TemporaryDirectory() as folder, patch.object(data_owners, 'analyse', return_value=[]):
            path = Path(folder) / 'owners.tsv'
            printed = io.StringIO()
            with patch.object(sys, 'argv', ['data_owners.py', '--output', str(path)]), \
                    contextlib.redirect_stdout(printed):
                data_owners.main()
            self.assertTrue(path.is_file())
            self.assertIn(f'Per-range detail: {path.resolve()}', printed.getvalue())


if __name__ == '__main__':
    unittest.main()
