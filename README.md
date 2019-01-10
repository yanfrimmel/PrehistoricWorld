# PrehistoricWorld
An Attempt to implement a simple 2d survival game written in C as a back-end layer over SDL 2 library to interface with Haskell, while using Haskell to implement the game logic.
The project host OS is Linux and the build targets are Windows & Linux.

* To build for Linux:
```bash
make all
```
* To build for Windows:
```bash
make -f Makefile.win all
```
* To run:
```bash
cd $Project_folder
cd out
./PrehistoricWorld
```
* To test:
```bash
cd $Project_folder
cd out
./test
```

