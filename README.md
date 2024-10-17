# Chip8_Emulator
A Chip-8 Emulator made in C++

This project has been an experiment in creating an emulator from the Chip8 assembly-like language into a working GUI application, while also being a test of multiple build systems, due to my desire to have a build that can be easily replicated across multiple different systems, though it has been a challenge.

Note that the built file, usually called 'chip8' or 'chip8.exe', will currently need a 'games/' folder in order to run, or call `chip [game]`

Currently, I have these build systems working in a Arch-based Linux environment:

### G++
1) Modify `include/window.h` and `src/window.cpp` to swap the commented `#include` with the `#include` below it
2) Run `make`

### CMake
1) Create a folder, call it 'build'
2) Either go inside the folder, and run the command: `cmake -S ..` or outside the folder, run `cmake -B build`
3) Inside the 'build' folder, run the `make` command to create the application
4) (Move 'chip8' outside of directory where 'games/' is to run)

### Meson
1) Start by running `meson setup builddir`
2) Inside 'builddir', either run `ninja` OR `meson compile` OR outside of 'builddir', run `meson compile -C builddir`
4) (Move 'chip8' outside of directory where 'games/' is to run)

### Zig
1) Run `zig build run` to build and run, or just `zig build` to build, where the file will be in 'zig-out/bin/' (doing will will need the file in the same folder as 'games/')

## Windows

Currently, I haven't had much success in windows. In the past I had some complicated solutions with CMake, and possibly a complicated clang command, but never liked the solutions and have since tried meson, which I will note a command that differs between windows and linux, which is creating a 'subprojects' folder, and running: `meson wrap install sdl2` and other commands needed, but I haven't had SDL2_ttf working as of yet.

However, I did get Zig to work!\
You will need to make sure Zig is installed, which will be downloading the Zig .zip file from their [website](), extracting the contents where you would like (my suggestions: `C:\zig`), then type in the Windows search bar 'environment' to edit system environment variables. Click Environment Variables on the bottom, click Path then Edit, press New then Browse, and choose where you put Zig (for me, `C:\zig`). You can confirm it works via restarting all terminals/powershells, and typing `zig version`.\
Simply run `zig build run` to run, or do `zig build` and move the .exe AND the .dll files to where a 'games/' folder is play on linux and windows!

## Mac
yeah im not rich enough for this