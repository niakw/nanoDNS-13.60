# nanoDNS 13.60 — v0.4-13.60.2

**Standard GitHub Release · firmware 13.60 targeted · 19 November 2026**

## Why this update?

This patch release rebuilds the actual ELF binaries after security and CI updates on `main`, instead of silently overwriting the earlier user-tested 0.4-13.60.1 Release.

- **CodeQL #2 (high / TOCTOU):** replace separate file-existence check + `fopen("w")` with atomic `open(O_CREAT | O_EXCL | O_NOFOLLOW, 0600)`, followed by descriptor-based writing. Existing `nanodns.ini` is never truncated during default creation.
- **Configuration reading:** open the INI using `O_NOFOLLOW`, validate it is a regular file with `fstat()`, and apply compiled mandatory fallback rules if it cannot be safely loaded.
- **CodeQL #1 (medium / workflow permissions):** specify read-only contents permissions for the normal build workflows, and avoid competing tag publication from these jobs.
- **Build pipeline:** Dependabot updates merged for `actions/checkout@v7`, `actions/upload-artifact@v7`, and `actions/download-artifact@v8`. Valid weekly GitHub Actions dependency monitoring.
- Updated bilingual community documentation, contribution/accessibility/conduct policies, and regression tests for atomic config creation.

## Verified hardware status (version-specific)

**0.4-13.60.1 (prior release):** **USER-TESTED** on console firmware 13.60. The tester reported normal startup and shutdown/power-on without recurrence of the previous issue. Two runtime logs documented **23 blocked A queries**, 124 loaded rules, 0 exceptions, and IPv4/IPv6 DNS listeners. A `shutdown: complete` line was not observed; the power-off result is based on the tester's report.

**0.4-13.60.2 (this release): NOT YET USER-TESTED.** SDK builds and host tests are required but do not transfer that earlier user validation to this newly built ELF. Firmware 13.60 needs a separate installation/startup/DNS and shutdown/power-on trial. Rest/resume, permitted Quad9 resolution, AAAA handling and repeated power cycles remain unverified by hardware logs.

**Other current-generation firmware: NOT USER-VALIDATED. Secondary/older-generation build: NOT USER-VALIDATED on any firmware.** Successful compilation does not establish compatibility.

## Download and install (recommended)

Download **`nanodns-13.60-v0.4-13.60.2-install.zip`**. It contains exactly two paths:

```text
data/pldmgr/payloads/local/nanodns/nanodns.elf
data/nanodns/nanodns.ini
```

Extract the ZIP on your computer, then FTP-copy its `data/` tree to the console filesystem root `/`, so the final paths are `/data/pldmgr/payloads/local/nanodns/nanodns.elf` and `/data/nanodns/nanodns.ini`. Never create `/data/data/`.

**Upgrade:** back up the old ELF and INI first. In Payload Manager, remove the old catalog nanoDNS 0.4 **or disable its entry**, stop it normally (or power off fully and reboot with its autoload disabled), and **remove the original entry from automatic startup**. Refresh the manager after copying files and activate only the new local `local/nanodns` entry in autoload. Do not launch two instances. Console primary **and** secondary DNS settings remain `127.0.0.1`; Quad9 `9.9.9.9` and `149.112.112.112` are INI upstreams only.

**Migrating from 0.4-13.60.1:** the destination `local/nanodns` is unchanged. Back up its current ELF and INI and ensure it is no longer running before overwriting them with this new build. Perform a full restart with only one nanoDNS autoload entry. Keep the old ZIP for rollback.

**Separate assets:** `nanodns.elf`, `nanodns-ps4.elf`, `nanodns.ini`, `SHA256SUMS`, and `nanodns-13.60-v0.4-13.60.2-install.zip.sha256` are also published. The SHA-256 files cover their respective distributions.

[English installation guide](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.md) · [Guide français](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.fr.md) · [Detailed test status](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/TEST_PLAN.md).

## Security boundary

nanoDNS only filters DNS queries received while its UDP listeners are running. It is **not a firewall** and cannot prevent direct-IP traffic, alternate or encrypted DNS, cached addresses, or pre-payload communication. Keep independent router/firewall WAN restrictions (IPv4 and IPv6) for strict network isolation. A green build is not proof of safe shutdown on an untested firmware.

Original work and GPL-3.0: [Drakmor/nanoDNS](https://github.com/drakmor/nanoDNS). 124-mask policy: [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist).

---

## Français — notes de version

**Release standard 0.4-13.60.2, pour firmware 13.60. Nouveau binaire à tester sur console.**

Ce correctif reconstruit le véritable ELF après le traitement des deux alertes CodeQL (création atomique de l'INI sans écrasement et droits minimaux des workflows) et la fusion des trois PR Dependabot (checkout v7, upload-artifact v7, download-artifact v8). Les documents d'accessibilité, contribution, conduite et issues ont été adaptés en français et en anglais.

**Version 0.4-13.60.1 précédente : test utilisateur positif sur firmware 13.60** pour le démarrage, le filtrage DNS de type A, l'extinction et le rallumage, sans répétition du problème initial. Les deux logs comptent 23 requêtes A bloquées, 124 règles et 0 exception.

**Version 0.4-13.60.2 (cette Release) : PAS ENCORE RETESTÉE SUR CONSOLE.** La version PS4 et les autres firmwares PS5 restent également non validés par des essais utilisateurs. La compilation seule n'est pas une preuve de compatibilité.

Le ZIP `nanodns-13.60-v0.4-13.60.2-install.zip` contient exactement `data/pldmgr/payloads/local/nanodns/nanodns.elf` et `data/nanodns/nanodns.ini`. Après sauvegarde, décompresser sur Mac puis copier `data/` à la racine `/` de la console. Dans Payload Manager, enlever ou désactiver l'ancien nanoDNS et **retirer son ancien autoload** ; fermer l'ancienne instance ou redémarrer complètement, puis activer **seulement `local/nanodns`** en démarrage automatique. Conserver le dernier ELF en sauvegarde pour retour arrière.

Les deux DNS console restent `127.0.0.1`. Quad9 se configure dans l'INI uniquement. nanoDNS ne remplace pas un pare-feu : garder le blocage WAN indépendant si nécessaire.

[Installation en français](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/INSTALL.fr.md) · [Protocole de tests](https://github.com/niakw/nanoDNS-13.60/blob/main/docs/TEST_PLAN.fr.md).
