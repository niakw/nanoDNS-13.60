<div align="center">

# nanoDNS 13.60 — Hardened Runtime

### Stronger DNS enforcement. Cleaner shutdown. One auditable payload.

**124 mandatory protected patterns · Quad9 Secure DNS · Native checks · Safer process lifecycle**

[![Protected masks](https://img.shields.io/badge/Mandatory_rules-124-394965)](nanodns.ini)
[![Resolver](https://img.shields.io/badge/DNS-Quad9_secure-456b90)](docs/DNS_POLICY.md)
[![License](https://img.shields.io/badge/License-GPL--3.0-555)](LICENSE)

**English (default)** · [Français](README.fr.md)

[**English installation**](docs/INSTALL.md) · [**Policy architecture**](docs/DNS_POLICY.md) · [**Runtime audit**](docs/PS5_13_60_LIFECYCLE.md) · [**Validation**](docs/TEST_PLAN.md)

</div>

---

## Go beyond a blocklist file

A DNS denylist can be edited, replaced or bypassed through local exceptions. A runtime can also fail during duplicate launch or system shutdown.

**nanoDNS 13.60 builds on [Drakmor's original nanoDNS](https://github.com/drakmor/nanoDNS)** and integrates the independent [124-rule Console Blocklist](https://github.com/niakw/nanodns-console-blocklist) **directly into the binary**. Known protected names are evaluated **before** user-defined exceptions, while permitted DNS lookups still use **Quad9 secure upstream resolvers**.

The goal is stronger **DNS-layer policy enforcement and process reliability** without unnecessarily breaking unrelated Internet access.

## Before and after: clear, testable improvements

| Capability | Original nanoDNS v0.4 | Standalone blocklist | **Independent hardened runtime** |
| --- | --- | --- | --- |
| Shipped default deny rules | **8** | **124** in INI | **124 mandatory** masks in binary |
| Shipped default exceptions | **6** | **0** | No exception can override a mandatory protected name |
| Upstream DNS | Three mixed resolvers | Quad9 secure pair | **Quad9 secure pair** |
| Special DNS questions | Original forwarding behavior | Original behavior | Reject unsupported or multiple questions |
| Upstream reply checks | Basic transaction checking | Original behavior | Validate question identity and protected aliases |
| Wildcard matching | Recursive | Depends on payload | **Iterative, native regression-tested** |
| Duplicate payload start | Can force-kill old instance | Original behavior | **No SIGKILL; exclusive UDP bind** |
| Logs and shutdown | Current log overwritten | Original behavior | Previous log retained, size bounded, shutdown milestones |
| Entire Internet / direct-IP blocking | **No** | **No** | **No — external firewall needed** |
| Firmware 13.60 shutdown/wake proven | Not established | Not applicable | **Hardware verification still required** |

The original software supports custom rules; the 8/6 values refer to its **unchanged defaults**. An INI alone cannot enforce mandatory precedence or modify the payload's process lifecycle.

## How mandatory protection works

```text
DNS query received by nanoDNS
              |
              v
  Compiled mandatory 124 masks
         /          \
    Protected     Not protected
        |              |
   Local deny      Additional INI rules /
 A: 0.0.0.0        user exceptions
 AAAA: no answer        |
                         v
                 Quad9 Secure DNS
                   9.9.9.9
                149.112.112.112
```

No external resolver operator is configured as fallback. Both Quad9 IPs use the **same threat-blocking service**; the payload's upstream transport remains **unencrypted UDP**. [Official Quad9 service details](https://docs.quad9.net/services/).

## Built for stability, not risky system patches

- Removed process enumeration using fixed internal-structure offsets and forced termination of existing instances.
- Preserved the existing process label to maintain compatibility with payload managers.
- Requires exclusive ownership of the IPv4 DNS listener; a second launch fails rather than stealing queries.
- Responds to supported termination signals and closes sockets and networking resources in documented stages.
- Uses bounded upstream operations and monotonic timekeeping when available.
- Retains the previous DNS log and limits log size.
- Adds static policy parity checks, native wildcard differential tests and SDK build workflows.

**No verified system shutdown callback has been established.** These defensive changes are not proof of a hardware shutdown or controller-wake fix.

## Already using Drakmor's original nanoDNS 0.4?

**Use our single ready-to-copy ZIP:** [**nanoDNS 13.60 installation bundle**](https://github.com/niakw/nanoDNS-13.60/releases/download/v0.4-13.60.1-beta.1/nanodns-13.60-v0.4-13.60.1-beta.1-install.zip).

After backing up the existing ELF/INI, **uninstall the original nanoDNS in Payload Manager or disable it and remove its autoload entry**, stop it through the manager when supported or shut down/restart the console cleanly. Then extract the ZIP on your computer, copy its `data/` tree to the **console filesystem root**, refresh Payload Manager, and enable **only `local/nanodns`** in autoload. **Do not** update the original repository/catalog entry or overwrite its existing `repo/nanodns@e8cce5d1` slot.

[**Step-by-step migration guide (English)**](docs/INSTALL.md#upgrade-from-drakmors-original-nanodns-04) · [Guide français](docs/INSTALL.fr.md#migration-depuis-le-nanodns-04-officiel-de-drakmor) · [Release and standalone files](https://github.com/niakw/nanoDNS-13.60/releases/tag/v0.4-13.60.1-beta.1)

## Installation: ZIP first, English first

The recommended download is a **two-file installation ZIP**. Copy the extracted files to these exact destinations (not `/data/data/`):

```text
/data/pldmgr/payloads/local/nanodns/nanodns.elf
/data/nanodns/nanodns.ini
```

Then refresh Payload Manager, enable only the `local/nanodns` autoload entry, keep **both console DNS fields at `127.0.0.1`**, and verify the new-session logs. The archive **does not** update Payload Manager's autoload on its own. An independent external firewall is still required for strict WAN isolation.

**[Download installation ZIP](https://github.com/niakw/nanoDNS-13.60/releases/download/v0.4-13.60.1-beta.1/nanodns-13.60-v0.4-13.60.1-beta.1-install.zip)** · [Complete English instructions](docs/INSTALL.md) · [Guide français](docs/INSTALL.fr.md) · [Validation plan](docs/TEST_PLAN.md)

## When can this independent project be considered stable?

A green build and static tests are **necessary but insufficient**. Real firmware 13.60 hardware must pass repeatable DNS, shutdown, rest/resume and controller-wake checks without crashes or storage repair. Even then, deleting this repository and returning to stock nanoDNS would **remove the compiled mandatory rule enforcement and lifecycle fixes**. Keep the independent repository and its audit history rather than returning to the original payload.

## Security limits

This is **not a firewall**. Direct IP connections, alternative/encrypted DNS, cached addresses, TCP DNS, pre-payload traffic and unknown hostnames remain possible. Use an independent WAN-deny policy for strict network isolation. Wide wildcard patterns and shared delivery infrastructure can also create false positives. See [security](SECURITY.md) and [test plan](docs/TEST_PLAN.md).

## Credits and license

**Original nanoDNS source:** [Drakmor](https://github.com/drakmor/nanoDNS). **Rules and research:** [niakw / Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). **Firmware-specific integration:** [niakw](https://github.com/niakw/nanoDNS-13.60). Community sources are credited in the [provenance document](docs/CREDITS.md). GPL-3.0 preserved. Independent project, not an official device-manufacturer release.

---

**Secure what DNS can protect. Document what it cannot.**
