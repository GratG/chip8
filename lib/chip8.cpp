#include "chip8.h"

Chip8::Chip8(){

}

Chip8::~Chip8(){
    
}

bool Chip8::loadRom(std::string s){

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