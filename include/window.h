#pragma once
#include <cstdint>
#include <SDL2/SDL.h>

class Window {
public:
    Window(char const* title, int width, int height, int textureWidth, int textureHeight);
    ~Window();
    void Update(uint32_t* buffer, int pitch);
    bool ProcessInput(uint8_t* keys);
    uint8_t GetKeyReleased();

private:
    SDL_Window* win;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};