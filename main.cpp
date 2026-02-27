#include "chip8.h"
#include <iostream>

int main(int argc, char* argv[]) {
chip8 chip8;

    std::cout << "CHIP-8 Emulator Starting..." << std::endl;
    std::cout << "Running test program..." << std::endl;
     chip8.memory[0x200] = 0x60; // 0x60 0A  →  LD V0, 0x0A
     chip8.memory[0x201] = 0x0A;

     chip8.memory[0x202] = 0x70; // 0x70 05  →  ADD V0, 0x05
     chip8.memory[0x203] = 0x05;

     chip8.memory[0x204] = 0x12; // 0x12 00  →  JP 0x200 (loop)
     chip8.memory[0x205] = 0x00;
    for (int i, i < 5, i++) {
        chip8.emulateCycle();
    }
    std::cout << "Test Complete" << std::endl;
    return 0;
}