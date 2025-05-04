
#include <iostream>
#include <cstdint>

class Chip8{
    public:
        Chip8();
        ~Chip8();
        void init();
        bool loadRom(const char *filePath); //loads the rom file to memory
        void cycle(); //performs a single cpu step

        void setDrawFlag(bool b);
        bool getDrawFlag();
        int getDisplay(int i);

        //keypad to store current state of key from 0x0-0xF
        uint8_t key[16];

    private:
        //CPU
        uint16_t opcode; //16 bit opcode
        uint8_t V[16]; //15 8bit registers, 16th is carry flag
        uint16_t index;
        uint16_t pc; //program counter
        uint16_t stack[16];
        uint16_t sp; //stack pointer
        int execute(uint16_t op);
        //RAM
        uint8_t memory[4096]; //4kb of mem

        //display of 64 height by 32 width pixels
        int display[64*32];
        bool drawFlag;
        //timers
        int delayTimer;
        int soundTimer;
        //clear display
        void clearScreen();
};
