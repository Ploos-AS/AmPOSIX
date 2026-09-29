# AmPOSIX public headers

Public AmPOSIX extension APIs live under the `amposix/` namespace so they do not collide with standard headers.

## Current M1 API

`<amposix/features.h>` provides:

- compile-time AmPOSIX version constants;
- `amposix_version_string()`;
- `amposix_capability_find()`;
- stable support categories;
- `amposix_support_name()`.

This API describes AmPOSIX's current portability knowledge. It does **not** claim POSIX conformance and does not replace libc functions.

Future compatibility headers are added only when required by real ports and after their semantics are understood. Planned namespaces include `amposix/compat.h` and `amposix/spawn.h`.
