# Changelog


**Language:** English (default) | [Français](CHANGELOG.fr.md)
## 0.4-13.60.1 — development candidate (2026-11-19)

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

**Validation note:** CI build status and physical console 13.60 shutdown/standby/PS-button behavior must be verified separately. This changelog does not claim a hardware fix.
