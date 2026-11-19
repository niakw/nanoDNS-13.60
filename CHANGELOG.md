# Changelog


**Language:** English (default) | [Français](CHANGELOG.fr.md)
## Unreleased on hardware — security and community follow-up (2026-11-19)

- Avoid a time-of-check/time-of-use race when generating the default `nanodns.ini`: create with `O_CREAT | O_EXCL | O_NOFOLLOW` and restrictive initial file permissions, without overwriting an existing configuration.
- Open an existing INI using a no-symlink file descriptor and require a regular file; retain fallback mandatory rules if the INI cannot safely be loaded.
- Add least-privilege `contents: read` for the ordinary console build workflows; eliminate duplicate auto-release jobs from those workflows. The release publisher remains separate.
- Replace the invalid Dependabot placeholder with weekly GitHub Actions dependency checks.
- Add complete English and French contribution, accessibility, code-of-conduct and issue-reporting guides, with real project paths and privacy reminders.

**Publication boundary:** The current standard GitHub Release and ZIP still contain the previously published binaries; these subsequent source changes are **not** claimed to have passed a new user console test. The 13.60 hardware success refers to the **previously installed release**. Other firmware and the secondary console build are not user-validated.

## 0.4-13.60.1 — standard GitHub Release; 13.60 basic user test passed (2026-11-19)

### Process safety
- Remove hardcoded process-info structure offsets and SIGKILL-based replacement.
- Retain the original process label for Payload Manager interoperability.
- Require exclusive IPv4 UDP listener and cleanly release resources on bind failure.
- Improve SIGTERM/SIGINT shutdown sequencing and logging milestones.
- Use monotonic deadline where supported; bound stale upstream packet draining.

### DNS policy and security

- Upstreams changed to Quad9 secure-only primary `9.9.9.9` and backup `149.112.112.112`; no other DNS providers fallback in distributed defaults. The original 124 deny rules / 0 exceptions stay intact.
- Integrate and credit the 124-rule, zero-exception selective configuration from [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist).
- Compile mandatory masks into the ELF and apply **before** any local exception.
- Reject unsupported DNS question sets rather than forwarding unchecked.
- Verify upstream response ID / question and reject protected aliases in DNS answers.
- Synchronize default generated config, shipped INI and example profile with static parity tests.

### Documentation and CI
- Add security boundary, shutdown lifecycle audit, French installation, test plan, policy provenance and credits.
- Retain console and console SDK builds and add offline security/policy validation.

**Validation note:** firmware 13.60 passed one user trial for basic startup, protected A-query DNS filtering and normal shutdown/power-on without a recurrence of the previously reported issue. Permitted upstream DNS, AAAA, rest/resume, repeated power cycles and long-term stability are not yet user-verified; other firmware and the secondary build remain untested on real hardware.
