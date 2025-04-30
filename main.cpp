#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "chip8.h"


int main(int argc, char *argv[]){
    std::cout << "Hello!" << std::endl;
    //create SDL window
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    SDL_CreateWindowAndRenderer("Chip8", 640, 320, 0, &window, &renderer);



    Chip8 chip8;
    chip8.loadRom("test");

    //setup gui/inputs

    //load the game

    //emulation loop
    while(true){
        //cycle cpu

        //render graphics
    }

    return 0;

}