import importlib.util
import pathlib
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("amposix_cli", ROOT / "tools" / "amposix")
MOD = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MOD)

class ScanTests(unittest.TestCase):
    def test_fixture_classification(self):
        db = MOD.load_db(ROOT / "data" / "features.json")
        found = MOD.scan(ROOT / "tests" / "fixtures", db)
        self.assertIn("read", found)
        self.assertIn("write", found)
        self.assertIn("fork", found)
        self.assertIn("mmap", found)
        self.assertEqual(db["read"]["class"], "native")
        self.assertEqual(db["fork"]["class"], "adapt")

    def test_identifier_boundary(self):
        db = {"read": {"class": "native"}}
        import tempfile
        with tempfile.TemporaryDirectory() as d:
            p = pathlib.Path(d) / "x.c"
            p.write_text("void bread(void); int x(){ bread(); return 0; }")
            self.assertNotIn("read", MOD.scan(p, db))

if __name__ == "__main__":
    unittest.main()
