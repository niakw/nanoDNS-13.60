"""Host regression test for actual atomic config-creation helper from main.c."""
from pathlib import Path
import re
import shutil
import stat
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class AtomicIniTests(unittest.TestCase):
    def test_create_once_never_truncates_or_follows_symlinks(self):
        compiler = shutil.which("cc")
        if compiler is None:
            self.skipTest("host C compiler not available")

        source = (ROOT / "main.c").read_text(encoding="utf-8")
        match = re.search(
            r"static int\\nensure_default_config_exists\\(const char \\*path\\) \\{"
            r"[\\s\\S]*?\\n\\}\\n\\nstatic int\\nload_config",
            source,
        )
        self.assertIsNotNone(match, "could not extract production config helper")
        helper = match.group(0).rsplit("\\n\\nstatic int\\nload_config", 1)[0]
        self.assertIn("O_EXCL", helper)
        self.assertIn("O_NOFOLLOW", helper)
        self.assertNotIn('fopen(path, "w")', helper)
        read_section = source[source.index("static int\\nload_config("):]
        self.assertIn("O_RDONLY | O_NOFOLLOW", read_section)
        self.assertIn("fstat(fd, &config_stat)", read_section)

        program = (
            "#define _POSIX_C_SOURCE 200809L\\n"
            "#include <errno.h>\\n#include <fcntl.h>\\n#include <stdio.h>\\n"
            "#include <stdlib.h>\\n#include <sys/stat.h>\\n#include <unistd.h>\\n"
            "static const char k_default_config[] = \"# default only\\\\n\";\\n"
            + helper
            + "\\nint main(int argc, char **argv) {\\n"
            "  if(argc != 2) return 2;\\n"
            "  int r = ensure_default_config_exists(argv[1]);\\n"
            "  if(r < 0) { perror(\"create\"); return 3; }\\n"
            "  printf(\"%d\\\\n\", r); return 0;\\n"
            "}\\n"
        )
        with tempfile.TemporaryDirectory() as td:
            directory = Path(td)
            cfile = directory / "atomic.c"
            binary = directory / "atomic"
            cfile.write_text(program, encoding="utf-8")
            build = subprocess.run(
                [compiler, "-std=c11", "-Wall", "-Wextra", "-Werror",
                 "-pedantic", str(cfile), "-o", str(binary)],
                text=True, capture_output=True,
            )
            self.assertEqual(build.returncode, 0, build.stdout + build.stderr)

            target = directory / "new.ini"
            run = lambda path: subprocess.run(
                [str(binary), str(path)], text=True, capture_output=True
            )
            first = run(target)
            self.assertEqual(first.returncode, 0, first.stderr)
            self.assertEqual(first.stdout.strip(), "1")
            self.assertEqual(target.read_text(), "# default only\\n")
            self.assertEqual(stat.S_IMODE(target.stat().st_mode), 0o600)

            target.write_text("user custom config\\n")
            second = run(target)
            self.assertEqual(second.returncode, 0, second.stderr)
            self.assertEqual(second.stdout.strip(), "0")
            self.assertEqual(target.read_text(), "user custom config\\n")

            link = directory / "config-link.ini"
            link.symlink_to(target)
            linked = run(link)
            self.assertEqual(linked.returncode, 0, linked.stderr)
            self.assertEqual(linked.stdout.strip(), "0")
            self.assertEqual(target.read_text(), "user custom config\\n")

            missing_parent = run(directory / "missing" / "nanodns.ini")
            self.assertNotEqual(missing_parent.returncode, 0)


if __name__ == "__main__":
    unittest.main()
