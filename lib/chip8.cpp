
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

    //set timers
    delayTimer = 0;
    soundTimer = 0;
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
    
    pc += execute(opcode); 
}

void Chip8::clearScreen(){
    for(int i=0;i <64*32; i++){
        display[i] = 0;
    }
    drawFlag = true;
}

int Chip8::execute(uint16_t op){

    switch(op & 0xF000){ //evaluate the first nibble of opcode
        case 0x0000:
            switch(op){
                //clear screen
                case 0x00E0:
                    clearScreen();
                    return 2;
                //set pc to stack addr, and decrease sp
                case 0x00EE:
                    pc = stack[sp];
                    sp--;
                    return 2;
                default:
                    break;
            }
        break;
        case 0x1000:
            //JP 0x1nnn - set pc to location nnn
            pc = op & 0x0FFF;
            return 0;
        case 0x2000:
            //0x2NNN push pc to stack, then set pc to nnn
            sp++;
            stack[sp] = pc;
            pc = op & 0x0FFF;
            return 0;
        case 0x3000:
            //0x3XNN reg V[x] is equal to value kk
            //skip next opcode
            if(V[(op & 0x0F00) >> 8] == op & 0x00FF)
                return 4;
            else
                return 2;
            break;
        case 0x4000:
            //0x4XKK reg V[x] is equal to value kk
            //skip next opcode
            if(V[(op & 0x0F00) >> 8] != op & 0x00FF)
                return 4;
            else
                return 2;
        case 0x5000:
            //0x5XY0 if reg V[x] == V[y]
            //skip next instr
                        //0x3XNN reg V[X] is equal to value NN
            //skip next opcode
            if(V[(op & 0x0F00) >> 8] == V[(op & 0x00F0) >> 4])
                return 4;
            else
                return 2;
            break;
        case 0x6000:
            //0x6XKK set V[x] to value KK
            V[(op & 0xF00) >> 8] = op & 0x00FF;
            return 2;
        case 0x7000:    
            //0x7XKK ADD value KK to V[X]
            V[(op & 0x0F00) >> 8] += 0x00FF;
            return 2;
        case 0x8000:
            switch(op & 0x000F){
                case 0x0000:
                    //0x8XY0 LD V[X] = V[Y]
                    V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4];
                    return 2;
                case 0x0001:
                    //0x8XY1 OR V[X] = V[X] OR V[Y]
                    V[(op & 0x0F00) >> 8] |= V[(op & 0x00F0) >> 4];
                    return 2;
                case 0x0002:
                    //0x8XY2 OR V[X] = V[X] AND V[Y]
                    V[(op & 0x0F00) >> 8] &= V[(op & 0x00F0) >> 4];
                    return 2;
                case 0x0003:
                    //0x8XY3 OR V[X] = V[X] XOR V[Y]
                    V[(op & 0x0F00) >> 8] ^= V[(op & 0x00F0) >> 4];
                    return 2;
                case 0x004:
                    //0x8XY4 ADD V[X] + V[Y], if greather than 8bits, set V[F] to 1
                    if((V[(op & 0x0F00) >> 8] + V[(op & 0x00F0) >> 4]) > 0xFF){
                        V[0xF] = 1;
                    } else{
                        V[0xF] = 0;
                    }
                    V[(op & 0x0F00) >> 8] += V[(op & 0x00F0) >> 4];
                    return 2;
                case 0x005:
                    //0x8XY5 SUB V[X] - V[Y], then set V[F] if borrow (if V[X] < V[Y])
                    if((V[(op & 0x0F00) >> 8] < V[(op & 0x00F0) >> 4]) ){
                        V[0xF] = 0;
                    } else {
                        V[0xF] = 1;
                    }
                    V[(op & 0x0F00) >> 8] -= V[(op & 0x00F0) >> 4];
                    return 2;
                case 0x006:
                    //0x8XY6 V[X] is shifted 1 right, V[F]? is set to 0x1 of reg before shift
                    V[0xF] = V[(op & 0x0F00) >> 8] & 0x1;
                    V[(op & 0x0F00) >> 8] >>= 1;
                    return 2;    
                case 0x007:
                    //0x8XY7 SUBN V[Y] - V[X]
                    if((V[(op & 0x0F00) >> 8] > V[(op & 0x00F0) >> 4])){
                        V[0xF] = 0;
                    } else{
                        V[0xF] = 1;
                    }             
                    V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4] - V[(op & 0x0F00) >> 8];
                    return 2;
                case 0x000E:
                    //0x8XYE V[X] is shifted 1 left, V[F] is set to bit 8 of reg before shift 
                    V[0xF] = V[(op & 0x0F00) >> 8] >> 7;
                    V[(op & 0x0F00) >> 8] <<= 1;
                    return 2;                               
                default:
                    break;
            }
            break;
        case 0x9000:
            
        
    }   

}