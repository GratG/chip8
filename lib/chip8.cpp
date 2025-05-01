
#include <iostream>
#include <fstream>
#include <cstring>
#include "chip8.h"

uint8_t fontset[80]{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0   |   each value is used to represent a hex value
    0x20, 0x60, 0x20, 0x20, 0x70, // 1  |   eg: for 0, only look at upper nibble
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2  |   0xF0 = 0b1111 = ****
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3  |   0x90 = 0b1001 = *  *
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4  |   0x90 = 0b1001 = *  *
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5  |   0x90 = 0b1001 = *  *
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6  |   0xF0 = 0b1111 = ****
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7  |
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8  |
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9  |
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A  |
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B  |
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80 // F
};

Chip8::Chip8(){

}

Chip8::~Chip8(){
    
}

void Chip8::init(){
    std::cout << "initializing system..." << std::endl;
    //set all initial values
    pc = 0x200;
    opcode = 0;
    index = 0;
    sp = 0;
    //set first 0-80bits in mem for fontset values
    for(int i=0; i<80; i++){
        memory[i] = fontset[i];
    }
}

bool Chip8::loadRom(std::string s){

    std::cout << "loading rom..." << std::endl;
    std::ifstream ifs;
    ifs.open(s, std::ios::binary);
    char c;
    //start at position 0x200 onwards
    int j = 0x200;
    for(int i = 0x200; ifs.get(c); i++){
        if(j >= 4096){
            return false;
        }
        memory[i] = (uint8_t)c;
        j++;
    }
    std::cout << "loading completed..." << std::endl;
    return true;
}

void Chip8::cycle(){
    /*
        opcode is a 16bit code in the form 0xABCD
        opcode is loaded from 2 nibbles AB and CD
        from location at pc(eg 0xA2F0)
    */

    opcode = memory[pc] << 8 | memory[pc+1];//fetch
    pc +=2;
    execute(opcode); 
}

void Chip8::execute(uint16_t op){

    switch(op & 0xF000){ //evaluate the first nibble of opcode
        case 0x0000:
            switch(op){
                //clear screen
                case 0x00E0:
                    break;
                //set pc to stack addr, and decrease sp
                case 0x00EE:
                    sp--;
                    pc = stack[sp];
                    pc +=2;
                    break;
                default:
                    break;
            }
        break;
        case 0x1000:
            //JP - set pc to location 0x0FFF
            pc= opcode & 0x0FFF;
            break;
    }

}