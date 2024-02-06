#include "window.h"

Window::Window(char const* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    win = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Window::Update(uint32_t* buffer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw pixels based on the buffer
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 64; ++x) {
            if (buffer[y * 64 + x] == 1) {
                SDL_Rect pixelRect = {x * 10, y * 10, 10, 10};
                SDL_RenderFillRect(renderer, &pixelRect);
            }
        }
    }

    // Update the screen
    SDL_RenderPresent(renderer);
}

bool Window::ProcessInput(uint8_t* keys) {
    bool quit = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_1:
                        keys[0x1] = 1;
                        break;
                    case SDLK_2:
                        keys[0x2] = 1;
                        break;
                    case SDLK_3:
                        keys[0x3] = 1;
                        break;
                    case SDLK_4:
                        keys[0xC] = 1;
                        break;
                    case SDLK_q:
                        keys[0x4] = 1;
                        break;
                    case SDLK_w:
                        keys[0x5] = 1;
                        break;
                    case SDLK_e:
                        keys[0x6] = 1;
                        break;
                    case SDLK_r:
                        keys[0xD] = 1;
                        break;
                    case SDLK_a:
                        keys[0x7] = 1;
                        break;
                    case SDLK_s:
                        keys[0x8] = 1;
                        break;
                    case SDLK_d:
                        keys[0x9] = 1;
                        break;
                    case SDLK_f:
                        keys[0xE] = 1;
                        break;
                    case SDLK_z:
                        keys[0xA] = 1;
                        break;
                    case SDLK_x:
                        keys[0x0] = 1;
                        break;
                    case SDLK_c:
                        keys[0xB] = 1;
                        break;
                    case SDLK_v:
                        keys[0xF] = 1;
                        break;
                }
                break;
            case SDL_KEYUP:
                is_released = true;
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        keys[0x1] = 0;
                        released_key = 0x1;
                        break;
                    case SDLK_2:
                        keys[0x2] = 0;
                        released_key = 0x2;
                        break;
                    case SDLK_3:
                        keys[0x3] = 0;
                        released_key = 0x3;
                        break;
                    case SDLK_4:
                        keys[0xC] = 0;
                        released_key = 0xC;
                        break;
                    case SDLK_q:
                        keys[0x4] = 0;
                        released_key = 0x4;
                        break;
                    case SDLK_w:
                        keys[0x5] = 0;
                        released_key = 0x5;
                        break;
                    case SDLK_e:
                        keys[0x6] = 0;
                        released_key = 0x6;
                        break;
                    case SDLK_r:
                        keys[0xD] = 0;
                        released_key = 0xD;
                        break;
                    case SDLK_a:
                        keys[0x7] = 0;
                        released_key = 0x7;
                        break;
                    case SDLK_s:
                        keys[0x8] = 0;
                        released_key = 0x8;
                        break;
                    case SDLK_d:
                        keys[0x9] = 0;
                        released_key = 0x9;
                        break;
                    case SDLK_f:
                        keys[0xE] = 0;
                        released_key = 0xE;
                        break;
                    case SDLK_z:
                        keys[0xA] = 0;
                        released_key = 0xA;
                        break;
                    case SDLK_x:
                        keys[0x0] = 0;
                        released_key = 0x0;
                        break;
                    case SDLK_c:
                        keys[0xB] = 0;
                        released_key = 0xB;
                        break;
                    case SDLK_v:
                        keys[0xF] = 0;
                        released_key = 0xF;
                        break;
                }
                break;
        }
    }
    return quit;
}