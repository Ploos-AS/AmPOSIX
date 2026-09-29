# AmigaOS time capability probes

These files are compile probes, not runtime implementations. They answer narrow SDK questions before AmPOSIX commits to an AmigaOS backend mapping.

- `read-eclock.c`: availability and declarations for `ReadEClock` / `EClockVal`.
- `timer-device.c`: timer.device request types and Exec declarations.
- `datestamp.c`: DOS `DateStamp()` wall-clock interface.

A successful compile proves only API/toolchain availability. Runtime semantics, resolution, epochs, wraparound and supported OS versions remain qualification questions.
