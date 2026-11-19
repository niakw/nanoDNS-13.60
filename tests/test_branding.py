"""Documentation contracts for the hardened DNS runtime."""
from pathlib import Path
import re
import unittest

ROOT=Path(__file__).resolve().parents[1]
BANNED=re.compile(r"\b(?:sony|nintendo|playstation|xbox|microsoft|epic|rockstar|ubisoft|sega|cloudflare|google|capcom|bandai|namco|steam|valve|gog|psn|ps4|ps5|ps3|akamai|electronic arts|take.two|square enix|cd projekt)\b",re.I)
PAIRS=(
 ("README.md","README.fr.md"),
 ("SECURITY.md","SECURITY.fr.md"),
 ("CHANGELOG.md","CHANGELOG.fr.md"),
 ("docs/CREDITS.md","docs/CREDITS.fr.md"),
 ("docs/DNS_POLICY.md","docs/DNS_POLICY.fr.md"),
 ("docs/INSTALL.md","docs/INSTALL.fr.md"),
 ("docs/PS5_13_60_LIFECYCLE.md","docs/PS5_13_60_LIFECYCLE.fr.md"),
 ("docs/TEST_PLAN.md","docs/TEST_PLAN.fr.md"),
)

class DocumentationContracts(unittest.TestCase):
 def test_language_pairs(self):
  for en,fr in PAIRS:
   with self.subTest(en=en):
    a=ROOT/en;b=ROOT/fr
    self.assertTrue(a.is_file());self.assertTrue(b.is_file())
    self.assertIn(b.name,a.read_text(encoding="utf-8"))
    self.assertIn(a.name,b.read_text(encoding="utf-8"))

 def test_english_install_is_default(self):
  en=(ROOT/"README.md").read_text(encoding="utf-8")
  self.assertIn("(docs/INSTALL.md)",en)
  self.assertIn("(docs/INSTALL.fr.md)",en)
  self.assertLess(en.index("(docs/INSTALL.md)"),en.index("(docs/INSTALL.fr.md)"))
  for name in ("README.md","README.fr.md"):
   s=(ROOT/name).read_text(encoding="utf-8")
   for term in ("124","Quad9","Drakmor"):
    self.assertIn(term,s)
  self.assertIn("hardware",en.lower())
  self.assertIn("not",en.lower())

 def test_no_visible_commercial_platform_names(self):
  for file in ROOT.rglob("*.md"):
   s=file.read_text(encoding="utf-8")
   s=re.sub(r"\]\([^)]*\)","]()",s)
   s=re.sub(r"https?://[^\s)>]+","",s)
   m=BANNED.search(s)
   self.assertIsNone(m, f"{file.relative_to(ROOT)}: {m.group(0) if m else ''}")

 def test_all_local_markdown_links(self):
  for file in ROOT.rglob("*.md"):
   s=file.read_text(encoding="utf-8")
   for href in re.findall(r"\]\(([^)]+)\)",s):
    if href.startswith(("https:","http:","#","mailto:")):continue
    path=href.split("#",1)[0].split("?",1)[0]
    if not path:continue
    with self.subTest(file=str(file.relative_to(ROOT)),link=href):
     self.assertTrue((file.parent/path).is_file())

if __name__=="__main__":
 unittest.main()
