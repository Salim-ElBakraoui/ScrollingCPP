# Scrolling C++ Project (SDL2)

Well it's my first project that doesnt have a static camera, you can move using the arrow keys and attack using the spacebar.
For now, the hitbox is represented by an ugly transparent square, and deals 25 damage every 6th of a second.
Enemies have 100hp.

# Compiling instructions

## Prerequisites
To compile that project you need to have MinGW installed on Windows along with all the SDL2 libraries.
On Linux you need to have `gcc gdb g++ make` and all the SDL2 dev/devel libraries.

## How to compile

### Windows
You just input this command if you're on Windows and already in the cloned repo
```bash
make

```
And you should get an executable ready to be launched (if you have dll issues do not forget to add them afterwards)

### Linux
You really just type 
```bash
make linux
```
and you get a ready to execute game.

