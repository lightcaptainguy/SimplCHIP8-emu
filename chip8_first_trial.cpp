#include <iostream>
#include <cstring>
#include <cstdint>
#include <fstream>
using namespace std;

void executeOpcode(uint16_t opcode, uint16_t &pc) {
    uint16_t firstNibble = (opcode & 0xF000) >> 12;
    switch(firstNibble) {
        case 0x1: {
            uint16_t address = opcode & 0x0FFF;
            pc = address;
            std::cout<< "Jump to 0x" << std::hex << address << std::endl;
            break;
        }
    
    } 
}

int main ()
{ 
    uint8_t memory[4096] = {0}; // RAM
    uint8_t V[16] = {0}; // 16 8 bit memory registers Vx, where x varies from 0 to F, unused for now
    uint16_t I = {0}; // Index register I, used to point locations in memory, unused for now
    uint16_t pc = 0x200;
    
    memory[0x200] = 0x12;
    memory[0x201] = 0x34;
    uint16_t opcode = memory[pc] << 8 | memory[pc+1];
    
    std::cout<<"CHIP-8 Initialized\n";
    std::cout<<"PC: 0x" <<std::hex << pc << std::endl;
    std::cout<<"Opcode at PC: 0x" <<std::hex << opcode << std::endl;

    executeOpcode(opcode, pc);
    std::cout<<"PC after execute: 0x" << std::hex << pc << std::endl;



}



