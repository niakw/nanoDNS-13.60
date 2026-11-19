# Safe installation — console firmware 13.60

**Language:** English (default) | [Français](INSTALL.fr.md)

1. **Deny WAN access for the console at your router/firewall** (both IPv4 and IPv6), but retain the local network required for FTP and a local/offline jailbreak loader. A saved `nanodns.ini` does not protect traffic before nanoDNS starts.
2. **Back up** your original `nanodns.elf`, `/data/nanodns/nanodns.ini`, `/data/nanodns/nanodns.log` and any important saves.
3. Copy this repository's [124-rule profile](../nanodns.ini) to `/data/nanodns/nanodns.ini`. The ELF **does not overwrite** an existing configuration. Look for `124 rule(s), 0 exception(s)` in the freshly generated log.
4. Set **both primary and secondary console DNS fields** to `127.0.0.1`. Never use a public secondary DNS for this setup. Retain the default local listener settings `bind=127.0.0.1` and `bind6=::1`.
5. Start your local WebKit Autoloader and **Payload Manager**, ensuring only **one autoload mechanism and one instance of each payload**. Do not add a second direct nanoDNS autoload entry.
6. Deploy a new ELF **only after green console SDK and policy checks**. Confirm the current-session log contains `listening on 127.0.0.1:53`, blocked platform services A/AAAA lookups, and authorized lookup resolution such as `github.com`.
7. Follow the [hardware validation matrix](TEST_PLAN.md): shutdown, physical power-on, DualSense wake, rest mode/resume, reload, and duplicate launch. Restore the original ELF and INI if a failure occurs.

## Upstream DNS configuration

The bundled `nanodns.ini` and embedded defaults use Quad9's **secure resolver pair** for *permitted* names only:

```ini
[upstream]
server=9.9.9.9
server=149.112.112.112
timeout_ms=1500
```

These are **not** the console's DNS settings. Keep both console DNS fields at `127.0.0.1`. Existing on-console configs must be manually replaced to use the new pair.

## Precautions

- An ELF alone cannot guarantee blocking while the console is fully off or before the exploit and payload load.
- This payload only filters UDP DNS requests actually received by nanoDNS, not direct IPs, cached addresses, alternate DNS/DoH/DoT, TCP DNS, or unrecognized hosts. Keep external WAN restrictions for a strict deny-all requirement.
- The embedded mandatory list protects its known masks even if an older INI contains exceptions, but the on-disk configuration controls additional rules and the visible user rule count.
- Review false positives: `<blocked-hostname-from-INI>`, `<blocked-hostname-from-INI>`, and the exact shared-CDN alias `<blocked-hostname-from-INI>`.
- Avoid testing by opening platform services or manually requesting a firmware update.

## Credits

Source payload: [Drakmor](https://github.com/drakmor/nanoDNS). Policy: [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist). Independent GPL-3.0 integration for firmware 13.60.

See also [security model](../SECURITY.md), [DNS policy](DNS_POLICY.md), and [release gate](TEST_PLAN.md).
