#include <chrono>
#include "chip8.h"
#include "window.h"

bool is_released{};
uint8_t released_key{};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [ROM location] [optional:scale] [optional:delay]" << std::endl;
        exit(1);
    }
    const char* file = argv[1];
    int scale = argc > 2? std::stoi(argv[2]) : 10;
    int delay = argc > 3? std::stoi(argv[3]) : 2;

    Window window("CHIP-8 Emulator", WIDTH * scale, HEIGHT * scale);

    Chip8 emulator;
    emulator.LoadROM(file);

    // int pitch = sizeof(emulator.display[0]) * WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit) {

        auto currentTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::milliseconds::period> (currentTime - lastCycleTime).count();

        if (dt > delay) {
            quit = window.ProcessInput(emulator.keypad);
            lastCycleTime = currentTime;
            emulator.RunNext();
            window.Update(emulator.display);
            is_released = false;
        }
    }
    return 0;
}