# Compatibility Model

AmPOSIX tracks APIs by semantics, not only by whether a symbol can be made to compile.

## Status classes

- `native` — available through the normal Amiga C environment or straightforward AmigaOS facilities.
- `header` — source compatibility can be provided entirely at compile time.
- `library` — implemented by `libamposix`.
- `adapt` — software usually requires a source-level portability change.
- `unsupported` — no credible compatibility implementation is currently planned.
- `investigate` — not yet classified.

## Initial API map

This table is a design target for investigation, not a statement of completed support.

| Area | API/example | Initial class | Direction |
| --- | --- | --- | --- |
| File I/O | `open`, `read`, `write`, `close` | investigate | Prefer existing libc/DOS mapping |
| Metadata | `stat` | investigate | Prefer libc/DOS mapping |
| Directories | `opendir`, `readdir`, `closedir` | investigate | Prefer existing libc or thin wrapper |
| Environment | `getenv` | native | Use the C environment where available |
| Environment mutation | `setenv`, `unsetenv` | library | Host backend implemented; AmigaDOS mapping remains platform-specific |
| Options | `getopt`, `getopt_long` | investigate | Header/library compatibility if needed |
| Line input | `getline`, `getdelim` | library | Implemented as `amposix_getline` / `amposix_getdelim`; optional POSIX-name macros |
| Strings | `strdup`, `strndup` | library | Implemented with optional POSIX-name macros |
| BSD strings | `strlcpy`, `strlcat` | library | Explicit BSD extensions; optional BSD-name macros |
| Time | `clock_gettime` | investigate | Map honestly to Amiga timing facilities |
| Sleep | `sleep`, `usleep`, `nanosleep` | investigate | Map to appropriate timing primitives |
| Networking | `socket`, `connect`, `send`, `recv` | investigate | Native socket stack integration |
| Resolver | `getaddrinfo`, `freeaddrinfo` | investigate | Compatibility wrapper if required |
| Multiplexing | `select` | investigate | Prefer native socket support where semantics fit |
| Threads | pthread subset | investigate | Map selected semantics to Exec primitives or explicit wrapper API |
| Mutexes | pthread mutex subset | investigate | Consider SignalSemaphore-backed compatibility |
| Dynamic loading | `dlopen` family | adapt | Prefer explicit Amiga library/module model; investigate compatibility |
| Processes | `posix_spawn` | adapt | Candidate portable process abstraction |
| Processes | `fork` | adapt | Do not emulate Unix copy-on-write process semantics deceptively |
| Memory mapping | `mmap` | adapt | Case-by-case; avoid fake semantics |
| Linux-only | `epoll` | unsupported | Port to portable event abstraction/select-style API |
| Linux-only | `inotify` | unsupported | Port to explicit polling/platform abstraction |

## Rules

1. A successful compile is not sufficient to mark an API supported.
2. Behaviour important to real applications must be tested.
3. Semantic differences must be documented next to the compatibility implementation.
4. Prefer a small source adaptation over a large misleading emulation.
5. Ports should record the lowest AmPOSIX compatibility level they require.

## Implemented compatibility slice

The first concrete `libamposix` compatibility functions are `amposix_getline()` and `amposix_getdelim()`. They use ordinary C `FILE *`, dynamically grow caller-owned buffers, preserve the delimiter, NUL-terminate the result, return `-1` at EOF before any bytes are read, and report invalid arguments through `errno`.

By default AmPOSIX does not replace host libc symbols. A port may define `AMPOSIX_ENABLE_POSIX_NAMES` before including `<amposix/stdio.h>` to map `getline` and `getdelim` to the compatibility implementation.

### String compatibility

`<amposix/string.h>` provides `amposix_strdup()`, `amposix_strndup()`, `amposix_strlcpy()` and `amposix_strlcat()`. POSIX names are opt-in through `AMPOSIX_ENABLE_POSIX_NAMES`; BSD extension names are separately opt-in through `AMPOSIX_ENABLE_BSD_NAMES`. This distinction is intentional: AmPOSIX does not describe `strlcpy` or `strlcat` as POSIX interfaces.

### Environment compatibility

`<amposix/env.h>` provides `amposix_setenv()` and `amposix_unsetenv()`. The current host backend implements POSIX-style process-environment behaviour and validates variable names. POSIX names remain opt-in through `AMPOSIX_ENABLE_POSIX_NAMES`.

AmigaOS qualification must not assume that the C process environment, AmigaDOS local variables and AmigaDOS global variables are interchangeable. The future Amiga backend will document which namespace is used for POSIX compatibility, while native local/global-variable access should remain available through an explicit Amiga-oriented API where useful.


### Time compatibility

`<amposix/time.h>` provides AmPOSIX clock and sleep interfaces. The host backend implements realtime, monotonic time and nanosleep. The classic AmigaOS backend uses the E-Clock for monotonic time, `timer.device` for sleeping, and `TR_GETSYSTIME` for the system wall clock.

Classic AmigaOS system time counts seconds and microseconds from 1978-01-01. AmPOSIX adds 252460800 seconds when exposing `AMPOSIX_CLOCK_REALTIME`, so the numeric epoch matches Unix/POSIX 1970-01-01. This is an epoch conversion only: AmPOSIX does not silently apply a timezone correction to the Amiga system clock.

On classic m68k builds `struct amposix_timespec.tv_sec` is currently a signed `long`. Consequently the Unix-epoch representation has a signed 32-bit 2038 limit even though the underlying classic AmigaOS timer value is unsigned. This limitation is explicit and must be resolved before AmPOSIX claims post-2038 realtime support.

Cross-compilation proves API and link compatibility only. Classic AmigaOS runtime support remains unqualified until the Q4 emulator contract records the required guest PASS evidence.
