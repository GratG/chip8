
#include <iostream>
#include <cstdint>

class Chip8{
    public:
        Chip8();
        ~Chip8();

        bool loadRom(std::string s); //loads the rom file to memory
        void cycle(); //performs a single cpu step


    private:
        //CPU
        uint16_t opcode; //16 bit opcode
        uint8_t V[16]; //15 8bit registers, 16th is carry flag
        uint16_t index;
        uint16_t pc; //program counter
        uint16_t stack[16];
        uint16_t sp; //stack pointer
        void execute(uint16_t op);
        //RAM
        uint8_t memory[4096]; //4kb of mem

        //display of 64 height by 32 width pixels
        int display[64*32]; 
};
