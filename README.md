# Chip8_Emulator
A Chip-8 Emulator made in C++

This project has been an experiment in creating an emulator from the Chip8 assembly-like language into a working GUI application, while also being a test of multiple build systems, due to my desire to have a build that can be easily replicated across multiple different systems, though it has been a challenge.

Note that the built file, usually called 'chip8' or 'chip8.exe', will currently need a 'games/' folder in order to run. 

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