# AmPOSIX ports

This directory will contain reproducible port metadata and Amiga-specific patches.

Planned layout:

```text
ports/
  <name>/
    port.toml
    patches/
```

A port should eventually record:

- upstream source URL and version;
- cryptographic checksum;
- upstream and patch licenses;
- build system;
- dependencies;
- required AmPOSIX compatibility level;
- Amiga-specific patches;
- stack/runtime requirements;
- qualification commands.

Upstream source archives and proprietary AmigaOS components do not belong here.
