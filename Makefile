all:
	g++ -I include/ src/*.cpp -o chip8
	./chip8 Brix.ch8