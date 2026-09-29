# AmPOSIX Roadmap

## M0 — Project foundation

Goal: define what AmPOSIX is, what it is not, and how future compatibility work is classified.

Deliverables:

- project contract and native-first principles;
- compatibility levels 0–3;
- initial repository structure;
- API/support classification model;
- CLI contract for `amposix`;
- ports metadata concept;
- host-side CI skeleton;
- contribution and licensing rules.

Exit criterion: the repository clearly defines the architecture and can validate its own metadata/docs without requiring proprietary AmigaOS files.

## M1 — Core SDK and scanner prototype

- create initial `include/amposix/` headers;
- create feature/support database;
- implement first `amposix scan` prototype;
- detect a useful subset of common POSIX calls;
- emit support classifications and actionable warnings;
- add small host-side unit tests.

## M2 — Level 0/1 portability layer

- compile-time compatibility helpers;
- common string, option parsing, directory and filesystem helpers;
- build-system integration examples for Autotools, CMake and Meson where practical;
- first real software ports that require no AmPOSIX runtime.

## M3 — libamposix runtime

- establish stable library ABI policy;
- timing and clock compatibility;
- selected file/process helpers;
- synchronization primitives where semantics map cleanly;
- explicit documentation of semantic differences.

## M4 — Networking

- Amiga-native socket backend;
- compatibility for common BSD/POSIX networking APIs;
- resolver helpers;
- qualification tests against supported Amiga networking environments.

## M5 — Process and execution portability

- spawn-oriented API;
- process execution compatibility where practical;
- shell/environment helpers;
- explicit handling strategy for software that assumes `fork()` semantics.

## M6 — Ports framework

- formal `port.toml` schema;
- source verification and patch application;
- reproducible cross-build workflow;
- package staging;
- dependency metadata;
- license metadata;
- qualification hooks.

## M7 — Emulator qualification

- integrate with Ploos Amiga runtime infrastructure;
- run representative binaries under multiple supported emulator configurations;
- keep ROM and AmigaOS files outside the repository;
- publish compatibility reports.

## M8 — Unix-like environment

Only after lower compatibility levels are mature:

- curated shell/tool environment;
- selected Unix utilities;
- package/ports user workflow;
- compatibility conveniences for software that genuinely expects a Unix-style userspace.

This milestone must not become a requirement for software that can run natively at Levels 0–2.
