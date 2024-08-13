# File system Navigator
File system navigator for Linux. Allows travelling through your file system with arrow keys in terminal.

## Set path to keyboard
Keyboard input is read from ```/dev/input/eventX```. This has to be set manually, since the program does not
automatically detect your input device (yet). Use ```sudo evtest``` to find out what event file
corresponds to your keyboard and change
```c
#define DEVICE "/dev/input/eventX" 
```
in ```include/fsnav/io.h```.

## Build
To build the executable you need cmake. Then run the following commands:
```console
$ mkdir build
$ cd build
$ cmake -S ..
$ make
```
## Run
From build directory run:
```console
$ sudo ./fsnav
```
Since keyboard input is read directly from ```/dev/input/eventX``` you have to sudo.

# Important
THIS PROJECT IS STILL IN DEVELOPMENT! PROGRAM WILL CRASH WHEN CERTAIN ACTIONS ARE PERFORMED!
