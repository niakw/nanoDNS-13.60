# nanoDNS 13.60 — v0.4-13.60.1-beta.1

**Pre-release / developer candidate — console firmware 13.60**

This independent release builds on [nanoDNS by Drakmor](https://github.com/drakmor/nanoDNS) and the [niakw Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). The original GPL-3.0 license and attribution are preserved.

## What's improved

- **124 mandatory DNS deny masks** compiled into the ELF; those protected names cannot be re-enabled by legacy INI exceptions.
- **Quad9 Secure DNS only:** `9.9.9.9` and `149.112.112.112` for permitted names.
- Deny unsupported/multiple DNS questions rather than forwarding them unfiltered.
- Validate upstream DNS transaction identity, question fields and selected protected answer aliases.
- Replace recursive DNS mask matching with an iterative implementation covered by native differential tests.
- Remove process scanning based on fixed OS offsets and forced `SIGKILL` of existing instances; use exclusive UDP listener ownership.
- Improve supported-signal shutdown cleanup, resource-release logs, upstream timeout/drain handling.
- Save the previous DNS log and cap active log size.
- Full English-first / French-second documentation, 124-mask parity tests and CI builds.

## Included files

| File | Purpose |
| --- | --- |
| `nanodns.elf` | Firmware 13.60 console payload — **use this** |
| `nanodns-ps4.elf` | Additional legacy console build |
| `nanodns.ini` | Installable 124-rule, zero-exception Quad9 policy |
| `SHA256SUMS` | SHA-256 checksums for included deliverables |

## Upgrade from nanoDNS 0.4 (Payload Manager)

1. **Back up** the existing ELF, `/data/nanodns/nanodns.ini`, and `/data/nanodns/nanodns.log`.
2. Keep the console on a local network with **WAN isolated externally**, IPv4 and IPv6, during the migration. This payload is inactive before a successful load.
3. In Payload Manager, **disable nanoDNS autoload**, stop it cleanly if supported, and do a full restart if necessary to ensure no old instance is running. Do not repeatedly force-kill the old process.
4. Import the new `nanodns.elf` into Payload Manager's **local payload library** using its documented import UI. Verify the autoload entry points to the newly imported ELF rather than the previous cloud/catalog entry. Do not overwrite arbitrary files under the manager's internal managed storage.
5. Copy `nanodns.ini` from this release to **`/data/nanodns/nanodns.ini`** through your normal FTP/file-transfer setup, keeping the backup. The ELF **does not automatically overwrite an existing INI**.
6. Re-enable **exactly one** nanoDNS autoload entry. Both console DNS fields should be `127.0.0.1`, not the external Quad9 addresses.
7. Verify fresh logs show the protected masks loaded, `0 exception(s)`, a live IPv4 listener, blocked queries answered locally, and benign permitted names resolving via Quad9 when WAN access is deliberately allowed.
8. Follow the full [English installation guide](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.md) or [French guide](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.fr.md), then execute the [hardware test matrix](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/TEST_PLAN.md).

**Rollback:** disable new nanoDNS autoload, restart, restore the original ELF and backed-up INI, then re-enable **one** original entry.

## Important release limitations

**Not yet validated on a physical console for shutdown, rest/resume or controller power-on.** Verify the exact release checksums before installation; keep the prior ELF and INI available for rollback. A green SDK build and offline tests do not prove those behaviors fixed. This is deliberately labeled **Pre-release**, not a stable production release.

**DNS is not a firewall** and does not guarantee that forbidden IP traffic cannot leave a device. Direct IPs, cached addresses, alternate/encrypted DNS, TCP DNS, DNS before payload initialization and unknown hostnames remain out of scope. If absolutely no unauthorized WAN traffic is acceptable, enforce restrictions at an independent router/firewall.

Some broad deny patterns and shared CDN names can create false positives. Do not attempt firmware-update requests as a test.

---

## Français — notes de version

**Préversion de test pour firmware 13.60, non validée sur console réelle pour l'extinction, la veille ou le réveil à la manette.**

Cette version intègre **124 règles DNS obligatoires** dans le binaire, sans exception pouvant les neutraliser. Les domaines autorisés passent uniquement par **Quad9 sécurisé** (`9.9.9.9`, `149.112.112.112`). Le fonctionnement est renforcé contre les chargements en double, les interruptions et certaines réponses DNS inattendues.

**Pour remplacer nanoDNS 0.4 :** sauvegarder l'ancien ELF, le fichier `/data/nanodns/nanodns.ini` et les logs ; désactiver le démarrage automatique de l'ancien nanoDNS dans Payload Manager ; redémarrer proprement avant de charger la nouvelle instance ; importer `nanodns.elf` dans la bibliothèque locale ; transférer séparément le nouveau `nanodns.ini` par FTP ; réactiver **une seule** entrée de chargement automatique. Les DNS primaire et secondaire de la console restent `127.0.0.1`.

**Important :** le filtrage DNS n'est pas un pare-feu. Pour interdire strictement le WAN, bloquer les accès réseau en amont sur le routeur, IPv4 et IPv6. Vérifier les journaux puis l'arrêt et la veille ; en cas de problème, rétablir l'ELF et l'INI sauvegardés.

**Crédits :** [Drakmor / nanoDNS](https://github.com/drakmor/nanoDNS), [niakw Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). Licence GPL-3.0 conservée.
