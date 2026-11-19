# DNS policy and exact security semantics


**Language:** English (default) | [Français](DNS_POLICY.fr.md)
## Provenance

The installable [`nanodns.ini`](../nanodns.ini) is sourced from [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist), its selective 124-rule v3 profile (updated 10 October 2026). The original resolver is [Drakmor/nanoDNS](https://github.com/drakmor/nanoDNS); its code remains GPL-3.0.

The fork contains three synchronized snapshots: `nanodns.ini`, `nanodns.ini.example` and the compiled list of `k_protected_masks`. The generated initial config in `main.c` includes the same rules. Tests fail if those masks or sections drift. **The policy is not downloaded automatically at boot.** Changes to the source policy require a reviewed code change and new CI run.

## Enforcement order

1. Decode a single standard-class IN DNS question, checking query opcode and packet structure. Nonstandard requests do **not** pass through upstream unfiltered.
2. Match against the **built-in mandatory masks**. If matched, answer A with `0.0.0.0`, AAAA and other types without resource records, without contacting upstream.
3. Only for names **not matching** the mandatory masks, consult the user's optional `[exceptions]` and `[overrides]`.
4. Forward remaining questions to configured IPv4 upstream DNS, and verify returned transaction ID, name, class, type and response flags.
5. Reject upstream answers that name a protected host in an answer record or supported alias target (CNAME/DNAME/NS/PTR/MX/SRV/SVCB/HTTPS).

**Malformed data never needs to be forwarded** to maintain compatibility. This improves DNS-layer enforcement without being a firewall. An unknown hostname or direct IP can still reach an unwanted service.

## Original source profile

- **124 rules** / **0 exceptions**, with broad platform services / platform vendor / additional console networks patterns, additional console networks, publisher services, publisher services, publisher services, publisher services, publisher services, publisher services, publisher services and other publishers.
- **Quad9-only secure upstreams** for otherwise permitted names: `9.9.9.9` (primary) and `149.112.112.112` (backup), with malware/phishing blocking and DNSSEC validation performed by Quad9. Both IPs belong to **the same provider**, and nanoDNS forwards using ordinary (unencrypted) UDP DNS.
- Local listeners: `127.0.0.1:53` and `[::1]:53`.
- The list deliberately leaves e.g. GitHub and YouTube resolvable if the console actually uses this resolver.

## Existing installations and compatibility

nanoDNS **does not overwrite** an existing file at `/data/nanodns/nanodns.ini`. You must back it up and deploy this repo's `nanodns.ini` to get the same 124-rule display and zero user exceptions. The mandatory compiled rules still prevent a legacy platform vendor `[exceptions]` entry from permitting a covered domain.

A hand-edited INI might add extra rules, which remain honored for otherwise unprotected names. An invalid line or missing file falls back to the built-in rules where applicable. There is **no remote hot update** of the policy and no dependence on live GitHub access.

## Limits and false positives

Full service coverage is not provable from 124 known masks. This is UDP DNS only; TCP DNS, encrypted DNS, other resolvers, cached addresses, direct IPs, network traffic preceding exploit startup and in-firmware update installation are not intercepted. For zero leaks, add an external network deny policy. Broad patterns and the shared CDN operator alias can break legitimate traffic; investigate with redacted logs.
