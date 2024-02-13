:: cmd | include  | files      | exe   |     SDL files                  | sdl.dll |    SDL_TTF files                     | sdl_ttf.dll
clang++ -Iinclude .\src\*.cpp -o chip8 -Ilibs/SDL/include -Llibs/SDL/lib -lSDL2 -Ilibs/SDL_TTF/include -Llibs/SDL_TTF/lib -lSDL2_ttf -lSDL2main

:: C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\bin