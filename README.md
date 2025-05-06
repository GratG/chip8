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
## Controls: 
The controls of the chip8 interpreter are setup in a 4x4 grid from 0-F, to adapt this to keyboard controls I am using the left 4 rows of the keyboard.

|---|---|---|---|
| 1 | 2 | 3 | C |
| 4 | 5 | 6 | D |
| 7 | 8 | 9 | E |
| A | 0 | B | F |

## Screenshots:
### Space Invaders:
Controls:<br />
    W - START/SHOOT<br />
    Q - LEFT<br />
    E - RIGHT<br />
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Space-Invaders.png)
### Pong:
Controls:<br />  
    Left player: 2 - UP Q - DOWN<br />
    Right player: Z - UP X - DOWN<br /> 
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Pong.png)
### [Timendus test suite:](https://github.com/Timendus/chip8-test-suite) chip8 Logo
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Timendus.png)
### [Timendus test suite:](https://github.com/Timendus/chip8-test-suite) corax+
![alt text](https://github.com/GratG/chip8/blob/main/screenshots/Corax.png)