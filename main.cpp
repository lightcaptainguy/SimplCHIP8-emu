#include "chip8.h"
#include <iostream>

int main(int argc, char* argv[]) {
chip8 chip8;

    std::cout << "CHIP-8 Emulator Starting..." << std::endl;
    std::cout << "Running test program..." << std::endl;
     chip8.initialize()
     chip8.loadTestProgram()
    for (int i = 0; i < 5; i++) {
        chip8.emulateCycle();
    }
    std::cout << "Test Complete" << std::endl;
    return 0;
}