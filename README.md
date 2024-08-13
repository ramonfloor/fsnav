# Important
THIS PROJECT IS STILL IN DEVELOPMENT! PROGRAM WILL CRASH WHEN CERTAIN ACTIONS ARE PERFORMED! I am still working on some ideas, 
this is merely the first version. Also this programm is most likely not portable. I run a Debian 12 machine, it works for me, but I
cannot guarantee that it will work on your system.

# File system Navigator
File system navigator for Linux. Allows efficient travelling through your file system with arrow keys in terminal.

[![fsnav_demo.webm](https://github.com/user-attachments/assets/593d754e-603b-4c77-9de6-bec850c643bc)](https://github-production-user-asset-6210df.s3.amazonaws.com/60486705/357579366-593d754e-603b-4c77-9de6-bec850c643bc.webm?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAVCODYLSA53PQK4ZA%2F20240813%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20240813T213714Z&X-Amz-Expires=300&X-Amz-Signature=0782874497de3fe2aa517af113f77ec8f6b49426fd55ed6ac4c3c26fdaeded5a&X-Amz-SignedHeaders=host&actor_id=60486705&key_id=0&repo_id=838759643)


## Set path to keyboard
Keyboard input is read from ```/dev/input/eventX```. This has to be set manually, since the program does not
automatically detect your input device (yet). Use ```sudo evtest``` to find out what event file
corresponds to your keyboard and change
```c
#define DEVICE "/dev/input/eventX" 
```
in ```include/fsnav/io.h```.

## Build
To build the executable you need ```cmake```. Then run the following commands:
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

## Controls
Controls are straightforward.\
<kbd>↑</kbd> 
<kbd>↓</kbd>
Move cursor up and down in the current directory\
<kbd>→</kbd>
Change to the marked directory\
<kbd>←</kbd>
Go back to parent directory
