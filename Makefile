all:
	g++ -I include/ src/*.cpp -o chip8 -lSDL2