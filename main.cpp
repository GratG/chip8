#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_main.h>
#include "chip8.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

uint8_t keymap[16] = {
    SDLK_X,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_Q,
    SDLK_W,
    SDLK_E,
    SDLK_A,
    SDLK_S,
    SDLK_D,
    SDLK_Z,
    SDLK_C,
    SDLK_4,
    SDLK_R,
    SDLK_F,
    SDLK_V,
};

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;


void createWindow(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Chip8", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    
    //SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING,
        64, 32);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_PIXELART);

}

void handleEvents(){

}

void drawDisplay(Chip8 c){
    uint32_t pixels[64*32];
    //store pixels in temp buffer
    for(int i=0; i < 64*32; i++){
        if(c.getDisplay(i) == 0){
            pixels[i] = 0xFF000000;
        } else{
            pixels[i] = 0x00FFFFFF;
        }
        
    }

    SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(Uint32));

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv){
    std::cout << "Hello!" << std::endl;
    //create SDL window
    createWindow();

    Chip8 chip8;
    
    //chip8->init();

    //load the game
    std::string file = "../roms/test_opcode.ch8";
    std::cout << "loading rom" <<std::endl;
    if(chip8.loadRom(argv[1])){

    }

    //setup gui/inputs



    //emulation loop
    while(true){
        //cycle cpu
        chip8.cycle();

        SDL_Event e;

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT)
                exit(0);
        
            if(e.type == SDL_EVENT_KEY_DOWN){
                for(int i =0; i <16; i++){
                    if(e.key.scancode == keymap[i]){
                        chip8.key[i] = 1;
                    }
                }
            }
            if(e.type == SDL_EVENT_KEY_UP){
                for(int i =0; i <16; i++){
                    if(e.key.scancode == keymap[i]){
                        chip8.key[i] = 0;
                    }
                }
            }
        }

        //render graphics
        if(chip8.getDrawFlag()){
            chip8.setDrawFlag(false);
            drawDisplay(chip8);
        }
        
        SDL_Delay(10);
    }

    return 0;

}