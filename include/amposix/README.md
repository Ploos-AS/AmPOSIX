# AmPOSIX public headers

This directory is reserved for AmPOSIX-specific public headers.

General POSIX compatibility headers should only be added when needed for real source compatibility and when their semantics are understood. AmPOSIX-specific extension APIs belong under the `amposix/` namespace to avoid collisions with standard headers.

Planned examples:

- `amposix/compat.h`
- `amposix/features.h`
- `amposix/spawn.h`

M0 intentionally does not publish unstable C APIs yet.
