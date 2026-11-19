# nanoDNS 13.60 — security & lifecycle fork

A carefully scoped PS5 firmware **13.60** fork of [Drakmor's nanoDNS](https://github.com/drakmor/nanoDNS), with a **mandatory 124-rule DNS denylist** sourced from [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist).

**Status:** source changes and automated verification are in progress. A green SDK build does **not** establish that console shutdown, rest-mode resume or controller wake are fixed. Do not replace your known-working payload until you have checked the build and followed the console validation plan.

## What changed

- No more process scanning with hardcoded FreeBSD kernel-info offsets or forcibly killing old nanoDNS instances with `SIGKILL`.
- Preserves the original `nanodns.elf` process label expected by external payload managers.
- Stops work promptly when `SIGINT` or `SIGTERM` is received and releases sockets / SceNet resources with shutdown milestones.
- Exclusive UDP port-53 ownership; if IPv4 bind fails, the new instance exits instead of silently running IPv6-only beside another resolver.
- Monotonic deadlines when available and bounded draining of stale upstream packets.
- Ships `nanodns.ini`, `nanodns.ini.example` and an embedded initial configuration derived from the multi-console policy.
- Compiles **all 124 protected masks into the payload**: a user-supplied exception or custom override cannot exempt those masks. Blocked A queries receive `0.0.0.0`; blocked AAAA/non-A queries receive NODATA.
- Refuses unsupported/multiple DNS questions rather than forwarding them uninspected.
- Checks upstream DNS replies (transaction ID, name, type, class and response flags) and refuses answers with protected domain aliases.
- Includes offline policy tests and PS4/PS5 SDK build workflows.

The policy is intentionally **selective**. Names not covered by its masks can still resolve through upstream DNS. Broad matches such as `*sony*`, `*nintendo*` and the shared CDN alias `a192.d.akamai.net` can block otherwise legitimate requests.

## Install on PS5 firmware 13.60

1. Read [safe installation (French)](docs/INSTALL.fr.md), [DNS rules](docs/DNS_POLICY.md) and [threat model](SECURITY.md).
2. Keep a router-level WAN block for the console during initial setup; this payload cannot filter pre-jailbreak traffic.
3. Back up `/data/nanodns/nanodns.ini` and existing logs before modifying anything.
4. Copy this repo's [`nanodns.ini`](nanodns.ini) to `/data/nanodns/nanodns.ini`. Existing on-console configs are deliberately **never overwritten** by payload startup.
5. Set **both** PS5 DNS slots to `127.0.0.1`; do not assign an external secondary DNS. Run the offline WebKit loader and Payload Manager, then launch only one `nanodns.elf`.
6. Verify `124 rule(s), 0 exception(s)` in the fresh log, `listening on 127.0.0.1:53`, blocked A/AAAA behavior, and normal permitted DNS resolutions.
7. Test clean shutdown, cold boot from the DualSense, rest/resume, relaunch and duplicate-load handling as described in [console test plan](docs/TEST_PLAN.md).

**Important:** Installing a new ELF does not replace the on-console `nanodns.ini`. Back up and explicitly deploy the policy file. For an existing conflicting user INI, the compiled mandatory 124 rules still apply; the startup rule count may differ from 124.

## Build and checks

```sh
python3 -m unittest discover -s tests -v
export PS5_PAYLOAD_SDK=/path/to/ps5-payload-sdk
make clean all
```

GitHub Actions uploads `nanodns.elf` on the PS5 build workflow. It also retains the upstream PS4 build for regression checks. Never interpret a CI artifact as proven safe on a physical console.

## Documentation

- [DNS policy, precedence, configuration](docs/DNS_POLICY.md)
- [PS5 13.60 lifecycle and shutdown audit](docs/PS5_13_60_LIFECYCLE.md)
- [Test matrix and release gate](docs/TEST_PLAN.md)
- [Installation sécurisée](docs/INSTALL.fr.md)
- [Security boundaries and responsible disclosure](SECURITY.md)
- [Credits and provenance](docs/CREDITS.md)
- [Changelog](CHANGELOG.md)

## Scope and limits

This payload **is not a firewall**. It cannot block cached IPs, direct-IP connections, alternate DNS or DoH/DoT clients, DNS over TCP, or outbound traffic before the payload starts. Its protection is limited to requests received by its UDP DNS sockets and the domains it recognizes. If *no forbidden network traffic may leave the console*, enforce that policy **at the router/firewall**, including IPv6.

The controller PS-button wake function occurs while the PS5 is powered off and cannot be implemented by a payload running only after boot. Fixing a faulty shutdown may help indirectly but cannot be asserted without console reproduction.

## Credits, licensing, affiliation

- **Original nanoDNS payload and code:** [Drakmor](https://github.com/drakmor/nanoDNS).
- **124-rule policy and independent security research:** [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist).
- Additional public domain research cited by that policy: [source bibliography](https://github.com/niakw/nanodns-console-blocklist/blob/main/docs/SOURCES.md).
- Maintainer of this 13.60 integration: [niakw](https://github.com/niakw).

Derived from Drakmor's GPL-3.0 code; the original [LICENSE](LICENSE) is retained. Independent community fork, not an official Sony, Microsoft, Nintendo or Drakmor release.
