#pragma once
#include <cstdint>
#include <iostream>

#define WIDTH 64
#define HEIGHT 32
#define hex(x) "0x" << std::hex << std::setfill('0') << std::setw(4) << (int) x
const unsigned int START_ADRESS = 0x200;

class Chip8 {
public:
    uint8_t registers[16];
    uint8_t memory[0xFFF];
    uint16_t I;
    uint16_t pc;
    uint16_t stack[16];
    uint8_t sp; // possibly can use a vector instead?
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t keypad[0xF];
    uint8_t display[WIDTH * HEIGHT];
    int debug_num;

    Chip8();
    void LoadROM(char const* filename);
    bool RunNext();

private:
    void Execute(const uint16_t instr);
    void Case0x8(uint8_t x, uint8_t y, uint8_t n);
    void Case0xF(uint8_t x, uint8_t n);
    void Draw(uint8_t x, uint8_t y, uint8_t height);
    void GetKey(uint8_t x);
};