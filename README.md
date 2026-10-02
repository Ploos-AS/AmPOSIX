# AmPOSIX

**A modern POSIX portability environment for AmigaOS.**

AmPOSIX is a source-compatibility and porting toolkit for bringing portable C and POSIX-oriented software to AmigaOS while keeping resulting programs as native and Amiga-friendly as practical.

The project is inspired by the strengths of Geek Gadgets, MinGW-w64 and Cygwin, but is not a clone of any of them. AmPOSIX follows a **native-first** design: use existing AmigaOS and C runtime facilities directly when possible, add thin compatibility shims where useful, and provide a runtime compatibility layer only where it is genuinely needed.

## Goals

- Make existing portable C software easier to bring to AmigaOS.
- Prefer native AmigaOS behaviour over emulating a Unix system.
- Provide familiar POSIX headers and APIs where that improves source compatibility.
- Clearly distinguish direct support, compatibility wrappers and unsupported semantics.
- Integrate with modern cross-compilation, CI and emulator-based qualification.
- Make porting measurable through automated source scanning and compatibility reports.
- Build a reusable ports collection rather than accumulating one-off patches.

## Non-goals

- Turning AmigaOS into Unix.
- Claiming complete POSIX conformance where AmigaOS semantics differ.
- Implementing expensive or misleading emulations merely to make a configure test pass.
- Requiring a large runtime dependency for software that can be built natively.

## Compatibility levels

AmPOSIX classifies ports by how much compatibility infrastructure they require:

- **Level 0 — Native:** builds using the normal Amiga C environment and AmigaOS APIs; no AmPOSIX runtime dependency.
- **Level 1 — Portable:** uses compile-time headers, macros or small inline wrappers; no runtime dependency.
- **Level 2 — AmPOSIX:** links against `libamposix` for functionality that needs a compatibility implementation.
- **Level 3 — Unix-like environment:** software that genuinely expects a wider Unix-style userspace and tool environment.

The project should always aim for the lowest practical level.

## Planned architecture

```text
Existing portable/POSIX C software
              |
              v
        AmPOSIX SDK
   +----------+----------+
   | headers / feature   |
   | tests / wrappers    |
   +----------+----------+
              |
      +-------+-------+
      |               |
      v               v
 AmigaOS/libc     libamposix
      |               |
      +-------+-------+
              |
              v
           AmigaOS
```

Networking should use native Amiga networking interfaces where appropriate. Threading, synchronization, timing and process-related compatibility should map to AmigaOS primitives when semantics can be represented honestly.

## Porting Lab

AmPOSIX is validated against real portable-C programs, not only synthetic API tests. The Porting Lab records source-change cost, compatibility level, build result, runtime qualification and semantic limitations for representative programs. Initial targets are hello, cat, grep, wc, date, sleep, netcat and a small IRC client.

## Porting assistant

A central long-term feature is the `amposix` command-line tool. M0 defines the intended interface; implementation follows in later milestones.

```text
amposix scan <source-tree>
amposix configure
amposix build
amposix test
amposix port build <name>
```

`amposix scan` should identify POSIX interfaces used by a project and classify them, for example:

```text
SUPPORTED DIRECTLY
  open read write close stat

SUPPORTED BY AMPOSIX
  getline getopt_long clock_gettime

PORTING REQUIRED
  fork execvp mmap

UNSUPPORTED / PLATFORM-SPECIFIC
  epoll inotify
```

The report must prefer truthful semantic classification over optimistic compile-only compatibility.

## Process model

Some Unix APIs do not map naturally to AmigaOS. `fork()` is the most important example. AmPOSIX must not pretend that AmigaOS has Unix process semantics when it does not.

Where appropriate, AmPOSIX should provide explicit portable abstractions such as spawn-style APIs and document source changes needed by ports.

## Ports collection

The planned ports tree will keep reproducible metadata and patches separate from upstream source code:

```text
ports/
  <name>/
    port.toml
    patches/
```

A future port definition should describe upstream source, checksums, build system, Amiga-specific requirements, runtime requirements and qualification tests.

## Toolchain integration

AmPOSIX is intended to work with the Ploos Amiga development and runtime infrastructure, including cross-compilation and emulator-based qualification. The SDK should remain usable independently and should not require proprietary Amiga ROM or OS files in this repository.

## M0 scope

M0 establishes the project contract and repository structure:

- native-first design principles;
- compatibility levels;
- initial API/support classification;
- SDK and ports directory layout;
- CLI contract for the future porting assistant;
- initial milestones and contribution rules;
- CI skeleton suitable for host-side validation.

No claim of POSIX conformance is made at M0.

## License

Software in this repository is licensed under the MIT License unless a file or imported component states otherwise. Upstream code and patches must retain and document their applicable licenses.
