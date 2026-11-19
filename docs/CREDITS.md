# Credits and provenance


**Language:** English (default) | [Français](CREDITS.fr.md)
## Original nanoDNS source

The C payload was authored by [Drakmor](https://github.com/drakmor/nanoDNS) and distributed under the GNU GPL-3.0 license. This fork preserves the upstream copyright notices and [license](../LICENSE). Original upstream repository and release notes: https://github.com/drakmor/nanoDNS .

## DNS policy

The mandatory 124-rule configuration and categorized console/publisher hostname research are from [niakw/nanodns-console-blocklist](https://github.com/niakw/nanodns-console-blocklist), version 3 profile. Its [source bibliography](https://github.com/niakw/nanodns-console-blocklist/blob/main/docs/SOURCES.md) credits other independent community work, including Al-Azif, MagicStuffCL, cjrb007, Misl3d and ZixX3r.

The rule snapshot is used in both `nanodns.ini` and the native protected-mask array; their exact parity is enforced by automated tests. Changes should be reviewed alongside the source policy, never silently updated over the network.

## Integration

This firmware-13.60-focused integration is maintained in [niakw/nanoDNS-13.60](https://github.com/niakw/nanoDNS-13.60). It is not an official Drakmor release and has no Sony, Nintendo or Microsoft affiliation.

The fork does not add third-party proprietary assets. Source and modifications remain subject to [GPL-3.0](../LICENSE).
