# Simple Calculator GUI (SDL)

A small graphical calculator built with C++ and [SDL2](https://www.libsdl.org/),
using SDL2_image to render PNG button textures. The interface presents digit and
operator buttons that build up an equation string on screen.

## Dependencies

- A C++17 compiler (e.g. `g++`)
- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://github.com/libsdl-org/SDL_image)

On Debian/Ubuntu:

```sh
sudo apt install g++ libsdl2-dev libsdl2-image-dev
```

## Building

With the provided `Makefile`:

```sh
make            # builds both simpleCalculator and testingParsing
make clean      # removes built binaries
```

Or compile directly with `g++`:

```sh
# GUI calculator (needs SDL2 + SDL2_image)
g++ -std=c++17 simpleCalculator.cpp -o simpleCalculator $(pkg-config --cflags --libs sdl2 SDL2_image)

# Standalone parser test harness (no SDL dependency)
g++ -std=c++17 testingParsing.cpp -o testingParsing
```

### Windows (one-shot)

On Windows, run the bundled script — it builds `simpleCalculator.exe` and
launches it in one step:

```bat
build-and-run.bat
```

Double-click it in Explorer, or run it from a Command Prompt. It checks for
`g++`, `pkg-config`, and SDL2/SDL2_image and prints the exact install command
if anything is missing, then `cd`s to its own folder so the PNG assets load.

It targets the MinGW-w64 toolchain (the same `g++` + `pkg-config` build as the
Makefile). The easiest way to get that is [MSYS2](https://www.msys2.org/) —
install the prerequisites once in an MSYS2 MinGW64 shell:

```sh
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 \
          mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-pkg-config
```

then add `C:\msys64\mingw64\bin` to your PATH (so both the compiler and the
SDL runtime DLLs are found).

## Running

```sh
./simpleCalculator
```

The button textures are PNG files (`one.png`, `plus.png`, `equals.png`, …) loaded
with relative paths via `IMG_Load`, so **run the program from the repository
directory** where those assets live. Running it from elsewhere will fail to load
the textures.

The parser test harness is interactive — it reads an equation from standard input
and prints the parsed result:

```sh
./testingParsing
```

## Known limitations

These are tracked as open issues:

- The equals button does not yet evaluate the equation (issue #1). Note the
  standalone equation parser in `testingParsing.cpp` is implemented and
  working; it is just not yet wired into the GUI's equals button.

See the [issue tracker](https://github.com/dmccoystephenson/Simple-Calculator-GUI-Using-SDL/issues)
for the full list.
