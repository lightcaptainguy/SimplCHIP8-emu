#ifndef CHIP8_H
#define CHIP8_H
#include <cstdint>

class chip8 {
    public:
    chip8();
    void emulateCycle();
    void loadROM(const char* filename);
    void loadTestProgram();
    uint8_t display[64 * 32];
    uint8_t keys[16];
    bool drawFlag;
    
    private:
    uint8_t memory[4096]; // RAM 
    uint8_t V[16]; // 16 8 bit V registers
    uint16_t I; // 16 bit register I
    uint16_t pc; //16 bit program counter
    uint8_t SP; //8 bit stack counter
    uint8_t stack[16]; //16 16bit values can be stored in the stack
    uint8_t delay_timer, sound_timer; // delay and sound 8 bit registers

    void Initialize();
    void executeOpcode(uint16_t opcode);



};
#endif