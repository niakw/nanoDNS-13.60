# Release validation plan — firmware 13.60

**Language:** English (default) | [Français](TEST_PLAN.fr.md)

**Status: development candidate.** Source tests and SDK builds cannot establish that console shutdown, controller power-on or standby are fixed.

## 1. Offline and CI checks

- `python3 -m unittest discover -s tests -v`: verify the 124 mandatory masks, zero-exception default profile, matching INI files, Quad9 addresses and native matching tests.
- Build the console ELF with the supported SDK; verify the artifact exists and is non-empty. Also compile the secondary compatibility target.
- Check the current **main commit**, not only an older successful run. Never present a build as validated hardware behavior.

## 2. Prepare without network leaks

Back up the old ELF, `/data/nanodns/nanodns.ini`, logs and important saves. Keep the console WAN-denied through an independent router/firewall rule (IPv4 and IPv6), while preserving LAN/FTP and a local loader.

Confirm one autoload mechanism and exactly one nanoDNS process. Transfer the 124-rule `nanodns.ini` explicitly; the payload deliberately does not overwrite an existing profile.

## 3. DNS security matrix

| Scenario | Required result |
| --- | --- |
| A query for a hostname from the mandatory INI | Local `0.0.0.0`; **no upstream forwarding** |
| AAAA query for the same protected hostname | Local no-address answer; **no upstream forwarding** |
| A previously excepted service hostname that is protected by the INI | **Still denied**, even with a legacy exception |
| Any additional protected publisher/legacy console hostname from the policy | Denied according to the mandatory masks |
| Multi-question, unsupported class or unsupported query opcode | Rejected rather than forwarded without checks |
| Permitted test hostname (such as `github.com`) | Successful upstream resolution when WAN is intentionally enabled |
| Upstream answer containing a CNAME to a protected hostname | Rejected; no protected target relayed |
| Duplicate payload launch | Existing IPv4 listener retained; new instance does not steal port 53 |
| Missing or invalid on-disk profile | Mandatory compiled masks still applied |
| Restart after receiving a supported termination signal | Network pool and listener released cleanly |

Select blocked names **from the actual INI**. Do not contact or deliberately request operating-system updates. Capture sanitized network traces if possible, not just successful app startup.

## 4. Hardware shutdown and wake

1. Establish clean shutdown and controller power-on behavior **without nanoDNS**, keeping other payloads unchanged.
2. Run a single nanoDNS instance for ordinary use, confirm DNS and then shut down from the system menu.
3. From a genuinely powered-off state, try the controller power button and note its light behavior.
4. Test standby, resume, controller input and restored DNS resolution.
5. Repeat after switching between apps, then close them before shutdown.
6. Check for storage repair prompts, freeze, kernel warnings or missing shutdown milestone logs.
7. If any problem recurs, save redacted logs and restore the known-working ELF and INI.

## 5. Release gate

**Required:** the current commit's SDK builds and policy CI must pass, DNS deny tests must show no upstream lookup for known blocked queries, permitted names must resolve, and physical-console shutdown/rest/resume/controller-wake must be repeatable.

**Fail conditions:** any unaccounted shutdown hang, filesystem repair, improper DNS relay, regression in permitted resolution, unexpected process kill or red CI. The strict no-WAN guarantee remains the responsibility of an external firewall, never this DNS payload alone.
