#include <chrono>
#include <string>
#include "chip8.h"
#include "window.h"

bool is_released{};
uint8_t released_key{};

int main(int argc, char** argv) {
    const char* file = argc > 1? argv[1] : NULL;
    int scale = argc > 2? std::stoi(argv[2]) : 10;
    int delay = argc > 3? std::stoi(argv[3]) : 2;

    Window window("CHIP-8 Emulator", WIDTH * scale, HEIGHT * scale);
    std::cout << "test" << std::endl;

    Chip8 emulator;

    // int pitch = sizeof(emulator.display[0]) * WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;
    bool on_menu = file == NULL;
    if (!on_menu)
        emulator.LoadROM(file);

    while (!quit) {

        if (on_menu) {
            menuInput keypress = window.MenuInput();
            if (keypress == 4)
                quit = true;
            on_menu = window.UpdateMenu(emulator.display, keypress);
            if (!on_menu) {
                std::string rom = "games/";
                rom.append(window.games[window.selected]);
                rom.append(".ch8");
                emulator.LoadROM(rom.c_str());
            }
        } else {
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

    }
    return 0;
}