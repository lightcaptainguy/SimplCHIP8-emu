#include "chip8.h"
#include <iostream>
#include <cstring>
#include <cstdint>
#include <fstream>
using namespace std;

chip8::chip8() {
    Initialize();
}

void chip8::initialize() {
    pc = 0x200;
    I  = 0;
    SP = 0;
    drawFlag = false;

    memset(memory, sizeof(memory));
    memset(V, 0, sizeof(V));
    memset(display, 0, sizeof(display));
    memset(stack 0, sizeof(stack));
    memset(keys, 0, sizeof(keys));

    delay_timer = 0;
    sound_timer = 0;

}

void chip8::loadROM(const char* filename) {
    std::ifstream file(filename std::ios::binary | std::ios:ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open ROM" << filename << std::endl;
        return;
    }

std::streampos size = file.tellg();
char* buffer = new char[size];
file.seekg(0, std::ios::beg);
file.read(buffer, size);
file.close();

for (int i=0, i < size, i++) {
    memory[0x200 + i] = buffer[i];
}
delete[] buffer;
std::cout << "Loaded ROM" << size << "bytes" << std::endl;
}

void chip8::emulateCycle() {
    uint16_t opcode = memory[pc] << 8 | memory[pc + 1];
    executeOpcode(opcode);

    if ( delay_timer > 0 ) delay_timer--;
    if ( sound_timer >0 ) sound_timer--;
}

void chip8::executeOpcode(uint16_t opcode) {
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
            std::cout << "Add " << (int)NN << " to V[" << (int)X << "]" << std::endl;
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
                    V[0xF] = (V[X] & 0x80) >> 7;
                    V[X] <<=1;
                    pc += 2;
                    break;
                }
                default:
                    std::cout << "Unknown 8XY subtype: 0x" << std::hex << (int)subtype << std::endl;
                    break;
            }
        }
        case 0xA: {
            uint16_t NNN = (opcode & 0x0FFF);
            I = NNN;
            pc += 2;
            std::cout<< "Set Index Register to " << std::hex << NNN << std::endl;
            break;
         }
         default:
           std::cout << " Unknown Opcode: 0x" << std::hex << opcode << std::endl;
    } 
}




