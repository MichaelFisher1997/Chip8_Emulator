all:
	g++ -I include/ src/*.cpp -o chip8 -lSDL2 -lSDL2_ttf