TARGET_WINDOWS_DIR := target/windows
TARGET_LINUX_DIR := target/linux
RESOURCES := resources
SDL_DLL := /usr/i686-w64-mingw32/bin/.
COMPILE_HASKELL := ghc -c -O src/haskell/** -outputdir tmp
# TODO: fix test
COMPILE_TEST := ghc --make `sdl2-config --libs --cflags` -O2  -lSDL2_image -optc-O test/c/*.c -no-hs-main -outputdir tmp -o target/test -Wall
COMPILE_C := ghc --make `sdl2-config --libs --cflags` -O2  -lSDL2_image -optc-O src/c/*.c src/haskell/*.hs -no-hs-main -outputdir tmp -o target/linux/PrehistoricWorld -Wall
COMPILE_C_WINDOWS := ghc --make `x86_64-w64-mingw32-gcc -lmingw32` -O2 -lSDL2main -lSDL2 -lSDL2_image -optc-O src/c/*.c src/haskell/*.hs -no-hs-main -outputdir tmp -o target/windows/PrehistoricWorld.exe -Wall
FLAGS_WINDOWS := -lmingw32 -lSDL2main -lSDL2 -ggdb3 -O0 --std=c99 -lSDL2_image -lm  -Wall
#---------------------------------------------------------- Targets
.PHONY: all
all: linux windows

linux: CREATE_LINUX_TARGET COPY_RESOURCES_LINUX COMPILE_HASKELL COMPILE_C
windows: CREATE_WINDOWS_TARGET COPY_RESOURCES_WINDWOS COPY_SDL_DLL COMPILE_HASKELL COMPILE_C_WINDOWS

CREATE_LINUX_TARGET:
	mkdir -p $(TARGET_LINUX_DIR)
CREATE_WINDOWS_TARGET:
	mkdir -p $(TARGET_WINDOWS_DIR)
COPY_RESOURCES_LINUX:
	cp -r $(RESOURCES) $(TARGET_LINUX_DIR)
COPY_RESOURCES_WINDWOS:
	cp -r $(RESOURCES) $(TARGET_WINDOWS_DIR)	
COPY_SDL_DLL:
	cp -r $(SDL_DLL) $(TARGET_WINDOWS_DIR)

COMPILE_HASKELL: 
	$(COMPILE_HASKELL) && echo "[OK]  $@"

COMPILE_C: 
	$(COMPILE_C) && echo "[OK]  $@"

COMPILE_C_WINDOWS: 
	$(COMPILE_C_WINDOWS) && echo "[OK]  $@"	

# --------------------------------------------------------------

.PHONY: test

test: COMPILE_HASKELL REMOVE_MAIN BUILD_TEST

REMOVE_MAIN: 
	rm tmp/src/c/main.o && echo "[OK]  $@"

BUILD_TEST:
	$(COMPILE_TEST) && echo "[OK]  $@"

.PHONY: clean, clear

clean clear:
	@cabal clean
	@rm -r -f target && echo "[CL]  target"
	@rm -r -f tmp && echo "[CL]  tmp"
