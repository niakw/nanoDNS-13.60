# QA and release gate — nanoDNS 13.60

**Current status: developer candidate until an SDK build and real console runs both pass.** These are test specifications, not assertions that console behavior has already been validated.

## 1. Offline tests (no console)

Run `python3 -m unittest discover -s tests -v`.
The tests compare the **124** source-policy masks, generated default policy, shipped `nanodns.ini.example` and compiled `k_protected_masks`. They validate absence of exceptions in the baseline, authorized name negative controls and representative PlayStation/Nintendo/Xbox/publisher domains.

Build the **PS5 ELF** with the official `ps5-payload-dev/sdk` and check the artifact exists and is nonempty. Check the PS4 workflow for compile regressions. Do not tag a release unless both builds and policy tests pass.

## 2. Safe console preparation

Back up `/data/nanodns/nanodns.ini`, the old ELF and `/data/nanodns/nanodns.log`; also back up important game saves. Keep WAN blocked externally (including IPv6) during initial tests while maintaining local FTP/loader access.

Use the same firmware 13.60, Payload Manager, WebKit Autoloader 0.7.1, kstuff-lite 1.11, ShadowMountPlus 1.7beta12, BFPilot 0.4.4 and ftpsrv 0.22. Confirm that autoload runs only once per payload.

## 3. DNS acceptance matrix

| Test | Expected behavior |
| --- | --- |
| `ps5.np.playstation.net` A | Blocked locally; 0.0.0.0, no upstream |
| `fus01.ps5.update.playstation.net` AAAA | Blocked locally; zero answers, no upstream |
| `feature.api.playstation.com` A | Blocked even if the old INI contains an exception |
| `gst.prod.dl.playstation.net` A | Blocked even if the old INI contains an exception |
| `nintendo.net`, `xboxlive.com`, `ea.com` A | Blocked by policy |
| Multi-question or unsupported DNS opcode | Rejected, never forwarded |
| Permitted query (e.g. `github.com`) | Resolved upstream normally |
| Upstream answer with a protected CNAME | Rejected and answered as SERVFAIL |
| Duplicate nanoDNS launch | Previous instance remains alive; new launch refuses to bind |
| Invalid/truncated or missing INI | No loss of embedded baseline protection |

These behaviors must be tested with controlled UDP DNS packets and console logs, not by accessing a firmware-update endpoint.

## 4. Power/lifecycle acceptance

1. No nanoDNS: establish a clean shutdown and controller wake baseline.
2. One nanoDNS instance: verify listener, permitted/blocked DNS, 10+ minutes of ordinary use, clean shutdown.
3. Cold power-on with DualSense PS button: note whether the console powers on **without requiring the hardware button**.
4. Rest mode and resume: verify controllers, DNS behavior and sockets; repeat clean shutdown.
5. After application/game switches, close all games and shut down. Note missing `shutdown: complete` milestones and kernel warnings.
6. Reload nanoDNS via Payload Manager: confirm no `SIGKILL` of an old instance, and no shared UDP listener.
7. No filesystem-repair popup, shutdown hang, or crash throughout validation.

If a failure occurs, preserve **last pre-shutdown logs** and any klog, redact personal data, and revert to the known-working ELF/config.

## 5. Release decision

- **Required**: green PS5 SDK CI, policy tests, no forbidden DNS lookup forwarded in matrix, allowed domains still work, successful one-instance startup, and successful physical PS5 shutdown/rest/resume/wake.
- **Blocked**: any unexplained shutdown hang, controller wake regression, disk repair, DNS policy bypass or red build.
- Do not infer a solved DualSense firmware bug merely from an ELF build: the PS button wake signal is handled while the payload is not running.
