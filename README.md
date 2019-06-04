# PrehistoricWorld
An attempt to implement a simple 2d game template written in C as a back-end layer over SDL 2 library to interface with Haskell with "Foreign Function Interface", while Haskell is used to implement the game logic and AI.
The project host OS is Linux and the build targets are Windows & Linux.

#### Prerequisites:

OS: Ubuntu 18.0.4 (other linux distributions may require a different method to setup SDL2)

Setup SDL2: 
```bash
sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev
```

#### To build for Linux:
```bash
make linux
```
#### To build for Windows:
```bash
make windows
```
#### To build for all:
```bash
make all
```
#### To clean for all:
```bash
make clean
```

#### To run in windows:
```bash
cd ${Project_Folder}
cd target/windows
PrehistoricWorld.exe
```
#### To run in Linux:
```bash
cd ${Project_Folder}
cd target/linux
./PrehistoricWorld
```
#### To test:
```bash
cd ${Project_Folder}
cd out
./test
```

