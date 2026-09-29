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
| Environment | `getenv` | investigate | Map to available C/AmigaOS facilities |
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
