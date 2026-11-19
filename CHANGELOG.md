# Changelog

## 0.4-13.60.1 — development candidate (2026-11-19)

### Process safety
- Remove hardcoded process-info structure offsets and SIGKILL-based replacement.
- Retain the original process label for Payload Manager interoperability.
- Require exclusive IPv4 UDP listener and cleanly release resources on bind failure.
- Improve SIGTERM/SIGINT shutdown sequencing and logging milestones.
- Use monotonic deadline where supported; bound stale upstream packet draining.

### DNS policy and security
- Integrate and credit the 124-rule, zero-exception selective configuration from [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist).
- Compile mandatory masks into the ELF and apply **before** any local exception.
- Reject unsupported DNS question sets rather than forwarding unchecked.
- Verify upstream response ID / question and reject protected aliases in DNS answers.
- Synchronize default generated config, shipped INI and example profile with static parity tests.

### Documentation and CI
- Add security boundary, shutdown lifecycle audit, French installation, test plan, policy provenance and credits.
- Retain PS5 and PS4 SDK builds and add offline security/policy validation.

**Validation note:** CI build status and physical PS5 13.60 shutdown/standby/PS-button behavior must be verified separately. This changelog does not claim a hardware fix.
