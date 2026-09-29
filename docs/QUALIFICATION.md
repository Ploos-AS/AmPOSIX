# AmigaOS runtime qualification

`qualification/amiga.c` is the minimal executable contract between AmPOSIX, `amiga-dev` and `amiga-runtime`.

Build it with:

```sh
make amiga-qualification
```

The resulting `build/amiga/amposix-qualification` must be copied into the runtime test volume and executed under the supported AmigaOS profiles.

Output is intentionally machine-readable line text:

```text
AmPOSIX qualification 0.1.0
PASS strdup
PASS strlcpy
PASS getline
SKIP environment: platform backend unqualified
SKIP monotonic: platform backend unqualified
SUMMARY pass=3 fail=0 skip=2
```

`PASS` means runtime behaviour was observed. `SKIP` is permitted only for an explicitly unqualified backend returning `ENOSYS`. Any other incorrect result is `FAIL` and the executable exits non-zero.

Initial runtime matrix:

| Profile | CPU | OS family | Purpose |
| --- | --- | --- | --- |
| A500 | 68000 | 1.x | minimum baseline |
| A500+ | 68000 | 2.x | later DOS/library behaviour |
| A1200 | 68020 | 3.x | primary higher-end baseline |

No Kickstart or AmigaOS files belong in this repository.
