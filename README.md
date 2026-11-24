# FrameLog

A small C++20 CLI for filtering and summarising recorded frame logs. The product is deliberately narrow; the repository exists to show the **delivery pipeline around it**: cross-platform builds, tests, containers, security gates, packaging and tagged releases.

> **Status: M0 foundation.** The binary currently supports `--version` and `--help`. The product commands (`inspect`, `filter`, `stats`, `gen`) and the delivery pipeline are the next milestones. Nothing here is production-ready.
>
> This is a portfolio project. It contains no client code, customer data or proprietary protocol implementation.

## Why this exists

Recorded frame logs are useful, but extracting a repeatable subset or a quick summary often means opening a GUI or writing a one-off script. FrameLog is intended to give engineers a small, scriptable CLI:

- validate a capture
- filter by bus, frame ID and time window
- summarise counts and rates
- generate deterministic synthetic fixtures for tests

The format will be a documented, versioned binary format called `.flog` v1. It is not a SOME/IP, DoIP, CAN, CAN-FD, FlexRay or PCAP implementation.

## What works today

```bash
framelog --version   # framelog 0.1.0
framelog --help      # usage and current status
```

The commands above are the M0 skeleton. They are covered by CTest and a GoogleTest smoke test.

## Build and test

Requirements:

- CMake 3.25 or newer
- A C++20 compiler (GCC, Clang or MSVC)
- Network access on the first configure, because GoogleTest is fetched by CMake

macOS or Linux:

```bash
cmake --preset macos-release   # or linux-release
cmake --build --preset macos-release
ctest --preset macos-release
```

Windows (Visual Studio 2022 or newer):

```powershell
cmake --preset windows-release
cmake --build --preset windows-release
ctest --preset windows-release
```

The binary is written to `build/<preset>/framelog` (Visual Studio adds a `Release/` directory). The Windows preset uses whichever Visual Studio generator is installed, so it works with both VS 2022 and VS 2026 runners.

## Repository layout

```text
framelog/
├── apps/framelog/main.cpp      # CLI entry point
├── include/framelog/           # public headers
├── src/                        # core library
├── tests/                      # GoogleTest suites
├── cmake/warnings.cmake        # warning policy
├── .github/workflows/ci.yml    # Linux + Windows matrix
├── CMakeLists.txt
├── CMakePresets.json
└── LICENSE
```

The core library is split from the CLI so the parser, filters, statistics and renderers can be tested without spawning a process. That structure is in place from M0; the components arrive in M1.

## Roadmap

| Milestone | Outcome | Status |
|---|---|---|
| M0 — Foundation | CMake skeleton, `--version`/`--help`, one test, Linux + Windows CI | In progress |
| M1 — Core product | `.flog` v1 format, reader/writer, filter, stats, generator, fixtures | Planned |
| M2 — Delivery | Multi-stage Docker, CPack packages, GHCR image, tagged `v0.1.0` release | Planned |
| M3 — Quality and security | CodeQL, dependency review, Trivy, SBOM, coverage gate, ADRs | Planned |
| M4 — Distribution | README polish, measured metrics, demo, portfolio links | Planned |

## Design notes

- **C++20, no runtime dependencies.** The CLI and core library use only the standard library. GoogleTest is a build-time test dependency.
- **Warnings are errors.** New warnings fail the build for the project's own targets.
- **Reproducible dependency.** GoogleTest is pinned by version and SHA-256 in `CMakeLists.txt`.
- **Cross-platform from the start.** The CI matrix builds and tests on Ubuntu and Windows before product features are added.

## Licence

MIT. See [LICENSE](LICENSE).

## Confidentiality

All fixtures will be synthetic. This repository does not contain KPIT client code, customer captures, proprietary protocol implementations or confidential screenshots.
