#include "chip8.h"
#include <string.h>
#include <iomanip> // for rand()
//temp
#include <bitset>

void Chip8::Execute(const uint16_t instr) {
    const uint16_t nnn = instr & 0xFFF;
    const uint8_t nn = instr & 0xFF;
    const uint8_t n = instr & 0xF;
    const uint8_t x = (instr & 0xF00) >> 8;
    const uint8_t y = (instr & 0xF0) >> 4;

    switch (instr & 0xF000) {
        case 0x0000:
            switch (nnn) {
                case 0xE0:
                    // disp_clear(). Sets all the bits in display to 0
                    memset(display, 0, sizeof(display));
                    break;
                case 0xEE:
                    // RET. Returns from a subroutine. Note: pc is overriden here
                    pc = stack[--sp];
                    break;
            }
            break;
        case 0x1000:
            // pc = nnn
            pc = nnn;
            break;
        case 0x2000:
            // Call subroutine. A function call. 
            // NOTE: pc already is + 2, so when it returns, it is already at the next, which is good
            stack[sp++] = pc;
            pc = nnn;
            break;
        case 0x3000:
            // if vx == nn, skip next instr.
            // Since its already +2 prior to execute(), to skip next, I add 2 more
            if (registers[x] == nn)
                pc += 2;
            break;
        case 0x4000:
            // if xv != nn, skip next instr.
            if (registers[x] != nn)
                pc += 2;
            break;
        case 0x5000:
            // if vx == vy, skip next instr.
            // NOTE: make sure to check the final '0', ensure its 0 (n?)
            if (registers[x] == registers[y])
                pc += 2;
            break;
        case 0x6000:
            // vx == nn
            registers[x] = nn;
            break;
        case 0x7000:
            // vx += nn
            registers[x] += nn;
            break;
        case 0x8000:
            Case0x8000(x, y, n);
            break;
        case 0x9000:
            // if vx != vy, skip next instr.
            // NOTE: make sure to check the final '0', ensure its 0 (n?)
            if (registers[x] != registers[y]) 
                pc += 2;
            break;
        case 0xA000:
            // I = nnn
            I = nnn;
            break;
        case 0xB000:
            // pc = nnn + v0
            pc = registers[0] + nnn;
            break;
        case 0xC000: {
            // vx = rand() & nn
            // casts rand to u8
            uint8_t rng = rand();
            registers[x] = rng & nn;
            break;
        }
        case 0xD000:
            // draw(vx, vy, n)
            Draw(x, y, n);
            break;
        case 0xE000: {
            uint8_t key = registers[x];
            switch (nn) {
                case 0x9E:
                    // if key() == vx, skip next instr
                    if (keypad[key])
                        pc += 2;
                    break;
                case 0xA1:
                    // if key() != vx, skip next instr.
                    if (!keypad[key])
                        pc += 2;
                    break;
            }
            break;
        }
        case 0xF000:
            Case0xF000(x, nn);
            break;
        default:
            std::cout << "Error: unknown instr: " << hex(instr) << std::endl;
    }
}

void Chip8::Case0x8000(uint8_t x, uint8_t y, uint8_t n) {
    switch (n) {
        case 0x0:
            // vx = vy
            registers[x] = registers[y];
            break;
        case 0x1:
            // vx != vy
            registers[x] |= registers[y];
            registers[0xF] = 0;
            break;
        case 0x2:
            // vx &= vy
            registers[x] &= registers[y];
            registers[0xF] = 0;
            break;
        case 0x3:
            // vx ^= vy
            registers[x] ^= registers[y];
            registers[0xF] = 0;
            break;
        case 0x4: {
            // vx += vy, set vf if overflow
            uint16_t sum = registers[x]+registers[y];
            registers[x] += registers[y];
            registers[0xF] = (sum > 0xFF)? 1 : 0;
            // registers[0xF] = sum >> 8;
            break;
        }
        case 0x5: {
            // vx -= vy, set vf if NOT underflow
            uint8_t orig = registers[x];
            registers[x] -= registers[y];
            registers[0xF] = (registers[x] > orig)? 0 : 1;
            // registers[0xF] = diff <= 255;
            break;
        }
        case 0x6: {
            // vx >>= 1. VF set to the value of the least sig. bit of vx before shift
            // if (!quirks.contains("ShiftVx")) // TODO
                registers[x] = registers[y];
            uint8_t f = registers[x] & 0x1;
            registers[x] >>= 1;
            registers[0xF] = f;
            break;
        }
        case 0x7:
            // vx = vy - vx, set vf if NOT underflow
            registers[x] = registers[y] - registers[x];
            registers[0xF] = (registers[x] > registers[y])? 0 : 1;
            break;
        case 0xE: {
            // vx = vy <<= 1. VF set to the value of the most sig. bit of vx before shift
            // if (!quirks.contains("ShiftVx")) // TODO
                registers[x] = registers[y];
            uint8_t f = registers[x] >> 7;
            registers[x] <<= 1;
            registers[0xF] = f;
            break;
        }
        default:
            std::cout << "Error: unknown instr: 0x8" << std::hex << (int) x << std::hex << (int) y << std::hex << (int) n << std::endl;
    }
}

void Chip8::Case0xF000(uint8_t x, uint8_t nn) {
    switch (nn) {
        case 0x07:
            // vx = get_delay(). sets vx to the value of delay timer
            registers[x] = delayTimer;
            break;
        case 0x0A:
            // vx = get_key(). A key press is awaited, and stored in vx
            GetKey(x);
            break;
        case 0x15:
            // delay_timer(vx). sets the delay timer to vx
            delayTimer = registers[x];
            break;
        case 0x18:
            // sound_timer(vx). sets the sound timer to vx
            soundTimer = registers[x];
            break;
        case 0x1E:
            // I += vx
            I += registers[x];
            break;
        case 0x29:
            // I = location of sprite for digit vx
            // `5 *` because each font character is 5 bytes each
            I = 5 * registers[x];
            break;
        case 0x33:
            // set_BCD(Vx). Stores the binary-coded decimal representation of VX,
            // *(I+0) = BCD(3); // with the hundreds digit in memory at location in I,
            // *(I+1) = BCD(2); // the tens digit at location I+1,
            // *(I+2) = BCD(1); // and the ones digit at location I+2.
            memory[I] = registers[x] /100; // hundreth place
            memory[I+1] = (registers[x]/10) %10; // tens-place
            memory[I+2] = (registers[x]%10); //ones-place
            break;
        case 0x55:
            // reg_dump(vx, &I)
            for (uint8_t offset = 0; offset <= x; offset++) {
                memory[I+offset] = registers[offset];
            }
            break;
        case 0x65:
            // reg_load(vx, &I)
            for (uint8_t offset = 0; offset <= x; offset++) {
                registers[offset] = memory[I+offset];
            }
            break;
        default:
            std::cout << "Error: unknown instr: 0xF" << std::hex << (int) x << std::hex << (int) nn << std::endl;
    }
}

/*
void Chip8::Draw(uint8_t x, uint8_t y, uint8_t height) {
    // pre-sets vf. If any bit is flipped, vf will be set 1.
    registers[0xF] = 0;
    uint8_t xOrigin = registers[x] & WIDTH  - 1;
    uint8_t yOrigin = registers[y] & HEIGHT - 1;
    uint8_t xPos = 0, yPos = 0;
    for (int h = 0; h < height; h++) {
        // Drawing starts at I, goes down row
        uint8_t spriteByte = memory[I + h];
        yPos = yOrigin + h;
        // width of 8 bytes
        for (int b = 0; b < 8; b++) {
            xPos = xOrigin + b;
            // Receives the most sig. bit, then shifts it right later, to make this easier
            uint8_t bit = spriteByte >> 7;
            int index = yPos*WIDTH + xPos;

            // Checks if a screen bit was flipped, for vf
            if (bit == 1 && display[index] == 0)
                registers[0xF] = 1;
            
            // Does XOR on the screen bit, the bits are either different OR the opposite of what they both were
            display[index] ^= bit;

            // aforementioned shift for the next bit
            spriteByte <<= 1;
        }
    }
}*/

void Chip8::Draw(uint8_t x, uint8_t y, uint8_t height) {
    // pre-sets vf. If any bit is flipped, vf will be set 1.
    registers[0xF] = 0;
    auto xOrigin = registers[x] & WIDTH  - 1;
    auto yOrigin = registers[y] & HEIGHT - 1;
    auto xPos = 0, yPos = 0;

    for (auto h = 0; h < height; ++h) {
        yPos = yOrigin + h;
        if (yPos >= HEIGHT) break;

        auto spriteByte = memory[I + h];
        
        for (auto b = 0; b < 8; ++b) {
            xPos = xOrigin + b;
            if (xPos >= WIDTH) break;

            if (!((spriteByte >> (7 - b)) & 0x1)) continue;
            
            auto index = yPos * WIDTH + xPos;

            if (display[index]) registers[0xF] = 1;
            display[index] ^= 1;
        }
    }
}

// Either sets vx or repeats the instruction
void Chip8::GetKey(uint8_t x) {
    if (is_released) {
        if (released_key == 0x0)
            registers[x] = 0x0;
        else if (released_key == 0x1)
            registers[x] = 0x1;
        else if (released_key == 0x2)
            registers[x] = 0x2;
        else if (released_key == 0x3)
            registers[x] = 0x3;
        else if (released_key == 0x4)
            registers[x] = 0x4;
        else if (released_key == 0x5)
            registers[x] = 0x5;
        else if (released_key == 0x6)
            registers[x] = 0x6;
        else if (released_key == 0x7)
            registers[x] = 0x7;
        else if (released_key == 0x8)
            registers[x] = 0x8;
        else if (released_key == 0x9)
            registers[x] = 0x9;
        else if (released_key == 0xA)
            registers[x] = 0xA;
        else if (released_key == 0xB)
            registers[x] = 0xB;
        else if (released_key == 0xC)
            registers[x] = 0xC;
        else if (released_key == 0xD)
            registers[x] = 0xD;
        else if (released_key == 0xE)
            registers[x] = 0xE;
        else if (released_key == 0xF)
            registers[x] = 0xF;
    } else
        pc -= 2;
}