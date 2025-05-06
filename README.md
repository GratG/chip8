# chip8 Emulator/Interpreter
A chip8 emulator written in C++ using SDL for graphics and input
 

## Building: 
Clone using `git clone` then cd into directory
```
$ mkdir build
$ cmake ..
$ make
```
## Running: 
After building the progect, you can run a .ch8 ROM but typing ./chip8 ../roms/*.ch8

example: 
```
./chip8 ../roms/Space.ch8
```

## Screenshots:
### Space Invaders:
Controls:
    W - START/SHOOT<br />
    Q - LEFT
    E - RIGHT
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Space-Invaders.png)
### Pong
Controls:  
    Left player: 2 - UP Q - DOWN
    Right player: Z - UP X - DOWN 
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Pong.png)
### [Timendus test suite:](https://github.com/Timendus/chip8-test-suite) chip8 Logo
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Timendus.png)
### [Timendus test suite:](https://github.com/Timendus/chip8-test-suite) corax+
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Corax.png)