# nanoDNS 13.60 — 0.4-13.60.1

**Standard GitHub Release — user-tested on console firmware 13.60.**

The original tag `v0.4-13.60.1-beta.1` and existing asset names are intentionally retained to preserve published download links. This Release is **not flagged as a prerelease**; the original tag name does not broaden the tested firmware scope.

This independent release builds on [nanoDNS by Drakmor](https://github.com/drakmor/nanoDNS) and the [niakw Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). The original GPL-3.0 license and attribution are preserved.

## Real-hardware test status (19 November 2026)

**Firmware 13.60 — USER-TESTED, basic operation successful.** The tester installed this release and confirmed that the previous shutdown/power-on issue did **not recur during the trial**. Two console log generations show **23 blocked A queries**, 124 rules, 0 exceptions, Quad9 configured and active IPv4/IPv6 loopback listeners.

**Other current-generation firmware: NOT USER-VALIDATED.** **Secondary/older-generation console build: NOT USER-VALIDATED on any firmware.** Green SDK compilation is not a real-user hardware test.

The 13.60 logs contain no `shutdown: complete` marker, so successful shutdown/power-on is **user-reported**, not a logged cleanup guarantee. Permitted Quad9 lookup, AAAA, rest/resume, repeatability and long-running stability remain unverified. This is a **standard GitHub Release**, with the remaining hardware test matrix clearly documented as incomplete. [Full English test record](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/TEST_PLAN.md) · [Bilan des tests en français](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/TEST_PLAN.fr.md).

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

## Ready-to-place installation bundle (recommended)

**[`nanodns-13.60-v0.4-13.60.1-beta.1-install.zip`](https://github.com/niakw/nanoDNS-13.60/releases/download/v0.4-13.60.1-beta.1/nanodns-13.60-v0.4-13.60.1-beta.1-install.zip)** contains exactly two files:

```text
data/pldmgr/payloads/local/nanodns/nanodns.elf
data/nanodns/nanodns.ini
```

The **actual console destinations** are `/data/pldmgr/payloads/local/nanodns/nanodns.elf` and `/data/nanodns/nanodns.ini`.

Extract on your computer and FTP-copy the ZIP's `data/` tree to the console filesystem root `/` (not to `/data/data/`). **First** back up the old configuration and binary; uninstall the original catalog nanoDNS using Payload Manager **or disable its autoload**, stop the running instance normally or cold-restart, and **remove the old nanoDNS from automatic startup**. After copying, refresh Payload Manager and add **only the new local slot `local/nanodns`** to autoload. The ZIP itself cannot edit the manager's autoload. The new profile uses Quad9; the console DNS fields remain `127.0.0.1`. [Detailed English guide](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.md) · [Guide français](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.fr.md).

**`nanoDNS_0.4.elf`** in the original `repo/nanodns@e8cce5d1` slot must **not** be overwritten with our release; treat it as a backup or remove it **through Payload Manager** after backing it up.

## Included files

| File | Purpose |
| --- | --- |
| `nanodns-13.60-v0.4-13.60.1-beta.1-install.zip` | **Recommended two-file installation bundle** (ready for FTP) |
| `nanodns.elf` | Firmware 13.60 console payload (standalone) |
| `nanodns-ps4.elf` | Additional legacy console build |
| `nanodns.ini` | Installable 124-rule, zero-exception Quad9 policy |
| `SHA256SUMS` | SHA-256 checksums for included deliverables |

## Upgrade from nanoDNS 0.4 (Payload Manager)

1. **Back up** the existing ELF, `/data/nanodns/nanodns.ini`, and `/data/nanodns/nanodns.log`.
2. Keep the console on a local network with **WAN isolated externally**, IPv4 and IPv6, during the migration. This payload is inactive before a successful load.
3. In Payload Manager, **uninstall the original nanoDNS after backup OR disable it and remove its autoload entry**. Stop the old running process cleanly if supported; otherwise fully shut down and restart the console with original autoload disabled. Do not repeatedly force-kill the old process.
4. **Preferred:** unpack the installation ZIP, FTP-copy its `data/` tree to console root, and refresh Payload Manager. It discovers `local/nanodns`. **Alternative:** import the standalone `nanodns.elf` via the manager's local payload import interface. Never overwrite the original catalog slot.
5. The ZIP also copies `nanodns.ini` to **`/data/nanodns/nanodns.ini`**. With standalone ELF installation, copy the INI via FTP yourself. The ELF **does not overwrite an existing INI**.
6. Re-enable **exactly one** nanoDNS autoload entry. Both console DNS fields should be `127.0.0.1`, not the external Quad9 addresses.
7. Verify fresh logs show the protected masks loaded, `0 exception(s)`, a live IPv4 listener, blocked queries answered locally, and benign permitted names resolving via Quad9 when WAN access is deliberately allowed.
8. Follow the full [English installation guide](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.md) or [French guide](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.fr.md), then execute the [hardware test matrix](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/TEST_PLAN.md).

**Rollback:** disable new nanoDNS autoload, restart, restore the original ELF and backed-up INI, then re-enable **one** original entry.

## Important release limitations

**A first firmware 13.60 user shutdown/power-on test has passed, without recurrence of the reported issue.** Longer/repeated testing, rest/resume, AAAA and permitted upstream resolution remain unverified; all other firmware and the secondary hardware target remain **not user-validated**. Verify release checksums and retain backups. This is a **standard Release** for the tested 13.60 firmware, not a blanket stability certification across all firmwares.

**DNS is not a firewall** and does not guarantee that forbidden IP traffic cannot leave a device. Direct IPs, cached addresses, alternate/encrypted DNS, TCP DNS, DNS before payload initialization and unknown hostnames remain out of scope. If absolutely no unauthorized WAN traffic is acceptable, enforce restrictions at an independent router/firewall.

Some broad deny patterns and shared CDN names can create false positives. Do not attempt firmware-update requests as a test.

---

## Français — notes de version

## Validation sur console (19 novembre 2026)

**Firmware 13.60 : TEST UTILISATEUR RÉUSSI pour les fonctions de base.** Le testeur confirme que le problème précédent d'extinction/rallumage ne s'est **pas reproduit pendant l'essai**. Deux générations de journaux montrent **23 requêtes A bloquées**, 124 règles, 0 exception, la configuration Quad9 et les deux écoutes IPv4/IPv6.

**Autres firmwares de la génération actuelle : NON VALIDÉS PAR TEST UTILISATEUR.** **Binaire pour la génération précédente : NON VALIDÉ SUR CONSOLE.** Une compilation SDK verte n'est pas un test utilisateur.

Aucune ligne `shutdown: complete` ne figure dans les deux logs : la réussite de l'arrêt/rallumage est **rapportée par le testeur**. Les requêtes AAAA, résolutions autorisées vers Quad9, veille/reprise, répétabilité et endurance restent à valider. La version est publiée comme **Release GitHub standard**, sans validation automatique des autres firmwares.

**Release standard :** extinction/rallumage sans anomalie signalée lors d'un premier essai matériel 13.60 ; veille, cycles répétés et stabilité prolongée restent à valider. Le tag historique conserve le suffixe `beta.1` pour préserver les liens des fichiers existants.

Cette version intègre **124 règles DNS obligatoires** dans le binaire, sans exception pouvant les neutraliser. Les domaines autorisés passent uniquement par **Quad9 sécurisé** (`9.9.9.9`, `149.112.112.112`). Le fonctionnement est renforcé contre les chargements en double, les interruptions et certaines réponses DNS inattendues.

**ZIP conseillé : [`nanodns-13.60-v0.4-13.60.1-beta.1-install.zip`](https://github.com/niakw/nanoDNS-13.60/releases/download/v0.4-13.60.1-beta.1/nanodns-13.60-v0.4-13.60.1-beta.1-install.zip).** Il contient exactement `data/pldmgr/payloads/local/nanodns/nanodns.elf` et `data/nanodns/nanodns.ini`, à décompresser sur Mac puis à copier vers la **racine** de la console (sans créer `/data/data/`). Il faut retirer l'ancien nanoDNS de l'autoload, puis mettre `local/nanodns` à la place ; le ZIP ne change pas automatiquement cette configuration.

**Pour remplacer nanoDNS 0.4 :** sauvegarder l'ancien ELF, le fichier `/data/nanodns/nanodns.ini` et les logs ; supprimer l'ancien nanoDNS via Payload Manager après sauvegarde, ou le désactiver et retirer son boot auto ; redémarrer proprement avant de charger la nouvelle instance ; copier les deux fichiers du ZIP aux chemins prévus, puis choisir le nouveau payload local ; réactiver **une seule** entrée de chargement automatique. Les DNS primaire et secondaire de la console restent `127.0.0.1`.

**Important :** le filtrage DNS n'est pas un pare-feu. Pour interdire strictement le WAN, bloquer les accès réseau en amont sur le routeur, IPv4 et IPv6. Vérifier les journaux puis l'arrêt et la veille ; en cas de problème, rétablir l'ELF et l'INI sauvegardés.

**Crédits :** [Drakmor / nanoDNS](https://github.com/drakmor/nanoDNS), [niakw Console Blocklist](https://github.com/niakw/nanodns-console-blocklist). Licence GPL-3.0 conservée.
