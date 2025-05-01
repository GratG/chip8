#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "chip8.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

void createWindow(){

    SDL_CreateWindowAndRenderer("Chip8", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        64, 32);
}

int main(int argc, char *argv[]){
    std::cout << "Hello!" << std::endl;
    //create SDL window
    createWindow();

    Chip8 *chip8;
    chip8->init();

    //load the game
    chip8->loadRom("../roms/Pong.ch8");

    //setup gui/inputs



    //emulation loop
    while(true){
        //cycle cpu

        //render graphics
    }

    return 0;

}