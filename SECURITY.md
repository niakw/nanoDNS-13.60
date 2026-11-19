# Security model and disclosure


**Language:** English (default) | [Français](SECURITY.fr.md)
## What this fork protects

The built-in denylist contains 124 masks from [nanoDNS Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). Matching queries handled by this **running** UDP DNS payload are answered locally, before configured exceptions are considered. AAAA and other types are answered without the matching IPv4 address; unsupported multi-question / non-IN requests are not relayed.

The payload additionally validates upstream reply identity, blocks protected alias names in answer sections, avoids forcible termination of old payload processes and refuses to start when the required IPv4 listener cannot bind.

## DNS upstream trust

The bundled policy uses only Quad9's **secure service** at `9.9.9.9` and `149.112.112.112`, two addresses belonging to the same operator. These are **unencrypted UDP DNS** upstreams, and any existing user INI needs explicit replacement to adopt them. Quad9 malware filtering and DNSSEC validation do not turn nanoDNS into a network firewall.

## What it does not protect

**DNS filtering is not a firewall or an absolute firmware-update prevention mechanism.** The following remain outside its scope:

- Cold boot or shutdown intervals before the payload starts, and failed jailbreak starts.
- Direct IPv4/IPv6 connections, cached addresses, direct package installation from local storage.
- Alternate resolvers, DNS-over-HTTPS / DNS-over-TLS, DNS-over-TCP and app-specific network stacks.
- New or hidden service domains not matching the 124 known rules; service traffic on unrelated CDN names.
- Hardware controller wake, suspend/resume of the OS, full kernel-lifecycle or network stack correctness.

If you need *no unfiltered outbound traffic*, enforce WAN-deny rules on your **router/firewall**, including IPv6, even when the PS5 is off or being jailbroken. Keep the locally hosted jailbreak path available.

## Risks and trust boundary

- Rules such as `*sony*`, `*playstation*`, `*nintendo*` are intentionally broad and can block innocent names. `a192.d.akamai.net` is a shared-CDN alias and may affect unrelated services.
- `bind=0.0.0.0` / `bind6=::` makes the resolver available on LAN; default loopback listeners are safer.
- A manually edited `nanodns.ini` may contain extra forwarders, exceptions or overrides. The embedded 124 mandatory masks cannot be overridden by exceptions but extra rules can still cause false positives.
- UDP upstream DNS is not encrypted or DNSSEC-validated. Response question/ID validation is useful defense-in-depth, not authentication.
- DNS logs can contain domain names, network addresses and timestamps. Review and redact before sharing.
- A successful SDK build is not proof of safe shutdown on PS5 13.60. Observe [test plan](docs/TEST_PLAN.md).

## Reports

Report reproducible vulnerabilities with firmware, payload SHA, config (without identifying network information), last relevant log lines, expected versus actual DNS output, and whether you can reproduce without nanoDNS. Do not publicly upload unredacted console or DNS logs.

## Provenance

Original payload: [Drakmor/nanoDNS](https://github.com/drakmor/nanoDNS).
Denylist: [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist), including [original source credits](https://github.com/niakw/nanodns-console-blocklist/blob/main/docs/SOURCES.md).
License: [GPL-3.0](LICENSE).
