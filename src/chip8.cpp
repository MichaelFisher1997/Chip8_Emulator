#include <fstream>
#include <iomanip>
#include "chip8.h"
#include "nlohmann/json.hpp"

uint8_t fontset[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {
    pc = START_ADRESS;
    sp = 0;

    // In order to make `rand()` make new numbers
    srand((unsigned) time(0));
    uint8_t rng = rand();

    for (unsigned int i = 0; i < 80; i++) {
        memory[0x50 + i] = fontset[i];
    }
}
void Chip8::LoadROM(char const* filename) {
    //Opens the file as a stream of binary, and moves the file pointer to the end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open()) {
        // Get size of file and allocate a buffer to hold contents
        std::streampos size = file.tellg();
        char* buffer = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        for (long i = 0; i < size; i++) {
            // std::cout << hex(buffer[i]) << std::endl;
            memory[START_ADRESS + i] = buffer[i];

        }
    }
}

bool Chip8::RunNext() {
    // Creates the opcode
    const uint16_t opcode = (memory[pc] << 8) | memory[pc+1];
    std::cout << "Instr: " << hex(opcode) << std::endl;

    // Increment the pc prior to execution
    pc += 2;

    // Execute opcode. Note: Regarding pc, it will either be override, modifed more, or be fine.
    Execute(opcode);

    // Decrement timers
    if (delayTimer > 0)
        delayTimer--;
    if (soundTimer > 0)
        soundTimer--;

    return false;
}