#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

extern bool is_released;
extern uint8_t released_key;

class Window {
public:
    Window(char const* title, int width, int height);
    ~Window();
    void Update(uint32_t* buffer);
    bool ProcessInput(uint8_t* keys);
    uint8_t GetKeyReleased();

private:
    SDL_Window* win;
    SDL_Renderer* renderer;
};