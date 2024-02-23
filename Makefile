all:
	g++ -I include/ src/*.cpp -o chip8 -lSDL2 -lSDL2_ttf
	./chip8 games/2048game.ch8