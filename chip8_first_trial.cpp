#include <iostream>
#include <cstring>
#include <cstdint>
#include <fstream>
using namespace std;

uint8_t V[16] = {0};
uint16_t I = {0};
void executeOpcode(uint16_t opcode, uint16_t &pc) {
    uint16_t firstNibble = (opcode & 0xF000) >> 12;
    switch(firstNibble) {
        case 0x1: {
            uint16_t address = opcode & 0x0FFF;
            pc = address;
            std::cout<< "Jump to 0x" << std::hex << address << std::endl;
            break;
        }
        case 0x6: {
            uint16_t X  = (opcode & 0x0F00) >> 8;
            uint16_t NN = opcode & 0x00FF;
            V[X]= NN;
            pc += 2;
            std::cout<< "Set V["<<X<<"] to "  << std::hex << NN << std::endl;
            break;
        }
        case 0x7: {
            uint16_t X = (opcode & 0x0F00) >> 8;
            uint16_t NN = opcode & 0x00FF;
            V[X] += NN;
            pc += 2;
        }
        case 0x8: {
            uint16_t X = (opcode & 0x0F00) >> 8;
            uint16_t Y = (opcode & 0x00F0) >> 4;
            uint16_t Subtype = (opcode & 0x000F);
            switch (Subtype) {
                case 0x0: {
                   V[X]=V[Y];
                   pc +=2;
            std::cout<< "Set V["<<X<<"] to V["<<Y<<"] " << std::endl;
            break; 
                }
                case 0x1: {
                    V[X] |= V[Y];
                    V[0xF] = 0;
                    pc += 2;
                    break;
                }
                case 0x2: {
                    V[X] &= V[Y];
                    pc += 2;
                    break;
                }
                case 0x3: {
                    V[X] ^= V[Y];
                    pc += 2;
                    break;
                }
                case 0x4: {
                    uint16_t sum = V[X] + V[Y];
                    if (sum >255)
                    V[0xF] = 1;
                    else
                    V[0xF] = 0;
                V[X] = sum & 0xFF;
                pc +=2;
                break;
                }
                case 0x5: {
                    if (V[X]>=V[Y])
                    V[0xF] = 1;
                    else
                     V[0xF] = 0;
                     V[X] -= V[Y];
                     pc += 2;
                     break;
                }
                case 0x6: {
                    V[0xF] = V[X] & 0x1;
                    V[X] >>= 1;
                    pc +=2;
                    break;
                }
                case 0x7: {
                    if (V[Y] >= V[X])
                    V[0xF] = 1;
                    else
                    V[0xF] = 0;
                    V[X] = V[Y] - V[X];
                    pc += 2;
                    break;
                }
                case 0xE: {
                    
                }
            }
        }
        case 0xA: {
            uint16_t NNN = (opcode & 0x0FFF);
            I = NNN;
            pc += 2;
            std::cout<< "Set Index Register to " << std::hex << NNN << std::endl;
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
    
    memory[0x200] = 0x82;
    memory[0x201] = 0x30;
    uint16_t opcode = memory[pc] << 8 | memory[pc+1];
    
    std::cout<<"CHIP-8 Initialized\n";
    std::cout<<"PC: 0x" <<std::hex << pc << std::endl;
    std::cout<<"Opcode at PC: 0x" <<std::hex << opcode << std::endl;

    executeOpcode(opcode, pc);
    std::cout<<"PC after execute: 0x" << std::hex << pc << std::endl;
    
}



