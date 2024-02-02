#include <chrono>
#include "chip8.h"
#include "window.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [ROM location] [option:scale] [option:delay]" << std::endl;
        exit(1);
    }
    const char* file = argv[1];
    int scale = argc > 2? std::stoi(argv[2]) : 10;
    int delay = argc > 3? std::stoi(argv[3]) : 1;

    Window window("CHIP-8 Emulator", WIDTH * scale, HEIGHT * scale, WIDTH, HEIGHT);

    Chip8 emulator;
    emulator.LoadROM(file);

    int pitch = sizeof(emulator.display[0]) * WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit) {
        quit = window.ProcessInput(emulator.keypad);

        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period> (currentTime - lastCycleTime).count();

        if (dt > delay) {
            lastCycleTime = currentTime;
            emulator.RunNext();
            window.Update(emulator.display, pitch);
        }
    }
    return 0;
}