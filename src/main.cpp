#include <iostream>
#include "chip8.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [game location]" << std::endl;
        exit(1);
    }
    const char* file = argv[1];
    Chip8 emulator;
    emulator.LoadROM(file);

    // testing random numbers;
    srand((unsigned) time(0));

    std::cout << "---" << std::endl;
    for (int i = 0; i < 20; i++) {
        emulator.RunNext();
    }
    return 0;
}