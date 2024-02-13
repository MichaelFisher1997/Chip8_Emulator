#include "window.h"
#include <SDL2/SDL_ttf.h>
#include <filesystem>

namespace fs = std::filesystem;
TTF_Font* font = NULL;

Window::Window(char const* title, int width, int height) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    win = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowPosition(win, 50, 50);

    // Initialize SDL2_TTF
    if (TTF_Init() == -1) {
        exit(1);
    }
    font = TTF_OpenFont("Sans.ttf", 24);

    // Get files from 'games'
    const fs::path dir = "games/";
    const std::string extention = ".ch8";
    std::vector fileList (fs::directory_iterator(dir), {}); //change to C convention
    for (const fs::directory_entry &file : fileList) {
        std::string item = file.path().string();

        if (item.substr(item.size() - extention.size(), extention.size()) == extention)
            games.push_back(item.substr(6, item.size()-6-extention.size()));
    }
}

Window::~Window() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

bool Window::UpdateMenu(uint32_t* buffer, int keypress) {
    // Clean display
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Calculate selected from keypress
    switch (keypress) {
        case up:
            selected = selected == 0? games.size()-1 : selected-1;
            break;
        case down:
            selected = selected == games.size()-1? 0 : selected+1;
            break;
    }

    // modifying for scrolling
    int height{};
    if (selected < 6) {
        // normal
        height = -10;
    } else if (selected > games.size()-10) {
        // bottom
        height = (games.size()-10)*-25;
    } else {
        // mid
        height = (selected-4)*-25;
    }

    // Create text for each game
    int i = 0;
    for (auto game : games) {
        SDL_Color White = {255, 255, 255};
        std::string msg = i == selected? "> " + game : game;
        
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, msg.c_str(), White);
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        
        SDL_Rect message_rect = {0, height, (int) msg.length() * 10, 40}; //x,y,w,h
        height += 30;
        SDL_RenderCopy(renderer, message, NULL, &message_rect);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
        i++;
    }

    // Update the screen
    SDL_RenderPresent(renderer);
    return keypress == enter? false : true;
}

menuInput Window::MenuInput() {
    menuInput keypress = none;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                keypress = quit;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        keypress = quit;
                        break;
                    case SDLK_w:
                    case SDLK_UP:
                        keypress = up;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        keypress = down;
                        break;
                    case SDLK_RETURN:
                        keypress = enter;
                        break;
                }
                break;
        }
    }
    return keypress;
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