#pragma once
#include <cstdint>
#include <iostream>
#define SDL_MAIN_HANDLED
// #include <SDL2/SDL.h>
#include "SDL.h"
#include <vector>

extern bool is_released;
extern uint8_t released_key;

enum menuInput {
    none = 0,
    up = 1,
    down = 2,
    enter = 3,
    quit = 4,
};

class Window {
public:
    Window(char const* title, int width, int height);
    ~Window();
    bool UpdateMenu(uint32_t* buffer, int keypress);
    menuInput MenuInput();
    void Update(uint32_t* buffer);
    bool ProcessInput(uint8_t* keys);
    uint8_t GetKeyReleased();
    std::vector<std::string> games{};
    int selected{};

private:
    SDL_Window* win;
    SDL_Renderer* renderer;
};