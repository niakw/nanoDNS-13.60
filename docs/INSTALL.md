# Safe installation — console firmware 13.60

**Language:** English (default) | [Français](INSTALL.fr.md)

## Upgrade from Drakmor's original nanoDNS 0.4

**This is a manual migration, not an update of the original repository.** The two GitHub projects are independent. The **Update** action of the original nanoDNS catalog entry may reinstall Drakmor's payload, not this release.

1. **Download and back up:** from the [13.60 pre-release](https://github.com/niakw/nanoDNS-13.60/releases/tag/v0.4-13.60.1-beta.1), download both `nanodns.elf` and `nanodns.ini`. Save your original 0.4 ELF, your current `/data/nanodns/nanodns.ini`, and `/data/nanodns/nanodns.log` to your computer. Keep the console WAN-blocked at the router/firewall (IPv4 and IPv6), while preserving local FTP/loader connectivity.
2. **Disable the original autoload:** in **Payload Manager**, turn off the autoload entry for the original nanoDNS. If a separate loader directly autostarts nanoDNS, disable that entry as well. Leave the other payloads unchanged.
3. **Power off cleanly and boot again:** start the local loader and Payload Manager. Do not replace a running ELF, send `SIGKILL` to the old process, or load two nanoDNS versions concurrently.
4. **Import the new ELF as a local payload:** use Payload Manager's local import mechanism with this release's `nanodns.elf`. Select the **imported local entry** rather than the original cloud/catalog entry. Do not guess or overwrite files inside Payload Manager's own storage.
5. **Replace the INI separately via FTP:** copy the release's `nanodns.ini` to **`/data/nanodns/nanodns.ini`**. nanoDNS does **not** overwrite an existing INI on startup, so upgrading just the ELF will not replace the old upstreams or exceptions in the file.
6. **Check DNS settings:** set **both console DNS fields** to `127.0.0.1`. Only the INI's `[upstream]` should contain `server=9.9.9.9` and `server=149.112.112.112`. Expect **zero active exceptions**. Do not enter the external Quad9 addresses directly into console DNS settings.
7. **Enable one entry:** run the imported ELF, verify it, and enable autoload **for that local entry only**. Keep the original/catalog entry disabled. A duplicate may fail to bind UDP port 53 by design.
8. **Verify and test:** inspect the new-session `/data/nanodns/nanodns.log` for `124 rule(s)`, `0 exception(s)`, the local DNS listener and blocked responses. When deliberately allowing selected network access, confirm a permitted name like `github.com` resolves. Then complete the [firmware 13.60 shutdown, controller wake and rest/resume checks](TEST_PLAN.md).

**Rollback:** disable new autoload, shut down normally, restore your backed-up official `nanodns.elf` through Payload Manager and old `nanodns.ini` through FTP, and re-enable **only the original entry**. Do not erase logs needed for diagnosis.

**Protection boundary:** nanoDNS is not a firewall. Direct IPs, cached IPs, non-local/encrypted DNS, TCP DNS, traffic before payload startup and unknown domains require independent router/firewall rules. A green build does not prove the original shutdown issue is fixed.

## First-time installation checklist

1. **Deny WAN access for the console at your router/firewall** (both IPv4 and IPv6), but retain the local network required for FTP and a local/offline jailbreak loader. A saved `nanodns.ini` does not protect traffic before nanoDNS starts.
2. **Back up** your original `nanodns.elf`, `/data/nanodns/nanodns.ini`, `/data/nanodns/nanodns.log` and any important saves.
3. Copy this repository's [124-rule profile](../nanodns.ini) to `/data/nanodns/nanodns.ini`. The ELF **does not overwrite** an existing configuration. Look for `124 rule(s), 0 exception(s)` in the freshly generated log.
4. Set **both primary and secondary console DNS fields** to `127.0.0.1`. Never use a public secondary DNS for this setup. Retain the default local listener settings `bind=127.0.0.1` and `bind6=::1`.
5. Start your local WebKit Autoloader and **Payload Manager**, ensuring only **one autoload mechanism and one instance of each payload**. Do not add a second direct nanoDNS autoload entry.
6. Deploy a new ELF **only after green console SDK and policy checks**. Confirm the current-session log contains `listening on 127.0.0.1:53`, blocked platform services A/AAAA lookups, and authorized lookup resolution such as `github.com`.
7. Follow the [hardware validation matrix](TEST_PLAN.md): shutdown, physical power-on, controller wake, rest mode/resume, reload, and duplicate launch. Restore the original ELF and INI if a failure occurs.

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
