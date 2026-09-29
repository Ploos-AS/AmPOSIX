# Contributing to AmPOSIX

AmPOSIX is a native-first portability project. Contributions should make software easier to port to AmigaOS without hiding important platform differences.

## Design rules

- Prefer existing AmigaOS/libc functionality over adding a runtime wrapper.
- Prefer compile-time compatibility over runtime compatibility when semantics remain correct.
- Do not claim POSIX behaviour unless the relevant semantics are actually provided.
- Document deviations and limitations explicitly.
- Avoid large emulations for APIs whose process or memory model fundamentally differs from AmigaOS.
- Keep proprietary ROMs, AmigaOS files and other redistributability-sensitive material out of the repository.
- Preserve upstream licenses when importing code or patches.

## Compatibility changes

When adding or changing support for an API:

1. update the compatibility database/documentation;
2. state the intended compatibility level;
3. add tests for observable behaviour where practical;
4. document semantic differences;
5. include a real-world port/example when the implementation exists mainly to support one.

## Ports

Ports should eventually include reproducible metadata, source verification, patches, dependency information, licensing information and qualification tests. Upstream source should not be vendored merely for convenience unless there is a documented reason and its license permits it.

## Commit style

Keep commits focused and describe the compatibility behaviour being introduced or changed.
