# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Ksnip is a cross-platform Qt-based screenshot tool with annotation features, written in C++17. It supports Linux (X11, Wayland), Windows, and macOS.

## Build Commands

```bash
# Standard build
mkdir build && cd build
cmake ..
cmake --build .

# Build with Qt6
cmake .. -DBUILD_WITH_QT6=ON

# Build with tests enabled
cmake .. -DBUILD_TESTS=ON
cmake --build .

# Run tests (Linux requires virtual framebuffer)
xvfb-run --auto-servernum ctest --extra-verbose    # Linux
ctest --extra-verbose                               # Windows/macOS
```

**Key CMake options:**
- `BUILD_TESTS` — enable unit tests (default: OFF)
- `BUILD_WITH_QT6` — build against Qt6 (default: OFF)
- `USE_SUBMODULE_KCOLORPICKER` / `USE_SUBMODULE_KIMAGEANNOTATOR` — build dependencies from git submodules in `libraries/`

## Architecture

**Dependency injection** drives the app: `DependencyInjector` wires all components. The startup flow is:
`main()` → `DependencyInjector` → `BootstrapperFactory` → `MainWindow`

**Key layers:**
- `src/backend/` — non-GUI logic: screenshot capture (`imageGrabber/`), uploading (`uploader/` — Imgur, FTP, scripts), config persistence (`config/`), CLI handling (`commandLine/`), IPC (`ipc/`)
- `src/gui/` — Qt UI: `MainWindow`, settings dialog, capture handlers, operations (save/upload workflows), global hotkeys, snipping area overlay, pin windows
- `src/common/` — shared utilities, platform detection, helpers, DTOs, enums
- `src/bootstrapper/` — app startup, single-instance enforcement via IPC
- `src/plugins/` — plugin system (OCR)

**Platform abstraction:** Many components (imageGrabber, snippingArea, globalHotKeys, config) have per-platform implementations selected at build time.

**Interface-heavy design:** Most components use I-prefixed interfaces (e.g., `IImageGrabber`, `IConfig`) for loose coupling and testability.

**External libraries:**
- **kImageAnnotator** — annotation UI framework
- **kColorPicker** — color picker widget
- Both available as git submodules under `libraries/`

## Testing

Tests use **Google Test/GMock**. Test sources are in `tests/` mirroring the `src/` structure. Mocks live in `tests/mocks/`.

**Test naming convention:** `<MethodUnderTest>_Should_<ExpectedBehavior>_When_<OptionalCondition>`

## Coding Style

Based on KDELibs style with these project-specific rules:
- **Indentation:** TABs, not spaces
- **Member variables:** `mCamelCase` prefix (not `m_camelCase`)
- **File naming:** PascalCase matching class name (`SomeClass.cpp`)
- **Headers:** cumulative — all includes go in `.h` files; `.cpp` includes only its own `.h`
- **Parameters:** const references for class types, pass-by-value for primitives/enums
- **Getters:** must be `const`
- **Access modifier order:** public, public slots, signals, protected, protected slots, private, private slots (member variables before member functions)
