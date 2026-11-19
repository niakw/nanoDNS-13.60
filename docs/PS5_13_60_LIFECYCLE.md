# nanoDNS lifecycle audit — PS5 firmware 13.60


**Language:** English (default) | [Français](PS5_13_60_LIFECYCLE.fr.md)
## Evidence, not yet a confirmed fix

[Upstream issue #16](https://github.com/drakmor/nanoDNS/issues/16) reports PS5 13.60 shutdown hangs in a setup containing WebKit Autoloader, Payload Manager, kstuff-lite and ShadowMountPlus, with the symptom disappearing when nanoDNS was disabled. This is **correlation**, not proof of the root cause, and it does not establish why a DualSense might fail to power on the console.

The original v0.4 source scanned OS process structures using hard-coded offsets and killed existing nanoDNS instances with `SIGKILL`. This bypassed exit handlers and cleanup. The fork removes the dangerous scan/kill path rather than guessing new firmware-specific offsets.

## Startup sequence

1. The autoloader starts Payload Manager (avoid running both distinct autoload mechanisms at once).
2. Payload Manager starts one nanoDNS process and displays its original `nanodns.elf` label.
3. The process loads `/data/nanodns/nanodns.ini`. If missing, it generates a copy of the bundled 124-rule default policy. Existing configs are not overwritten.
4. The process creates the SceNet pool, then tries IPv4 UDP `127.0.0.1:53`, plus optional IPv6 `::1:53`.
5. If IPv4 cannot bind, startup aborts and releases SceNet; a second launch must **not** steal a running listener.

Only after successful listener initialization do startup notifications occur.

## Runtime

- Matching the mandatory 124 masks occurs before user exceptions.
- Blocked A answers: `0.0.0.0`. Other blocked question types: NODATA.
- A non-IN, non-standard or multi-question packet is refused, never blindly forwarded.
- Permitted queries use upstream UDP with bounded timeouts. Returned response question/name/type/class/ID must match, and protected aliases in the answer section are rejected.
- DNS queries are logged to `/data/nanodns/nanodns.log`; sanitize logs when sharing.
- Listener sockets can be retried on errors; upstream drain loops are bounded.

## Stop, shutdown and rest mode

The process handles `SIGINT` and `SIGTERM` by setting a stop flag. It then finishes no new DNS work, closes local and upstream sockets, releases the SceNet pool, writes terminal milestones and exits. The code **does not yet have a proven PS5 system shutdown callback**. If the OS kills the process without delivering a supported signal, that path cannot be guaranteed.

Rest mode may suspend and later resume existing sockets. PS5 13.60 behavior and interactions with ShadowMountPlus, kstuff-lite and Payload Manager require actual hardware validation.

**Do not apply kernel memory offsets, register kernel patches, or force-kill system processes as a substitute for this validation.**

## Required evidence before release

A green PS5 SDK build; 124-rule parity tests; no leakage in known blocked A, AAAA, ANY and unsupported multi-question requests; at least one authorized name resolving; stable single-instance/duplicate behavior; clean 13.60 power off, physical-button power on, DualSense power on and rest/resume; no filesystem repair warning; consistent logs through shutdown. See [test plan](TEST_PLAN.md).
