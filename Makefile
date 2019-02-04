CC := gcc
CC_WIN := x86_64-w64-mingw32-gcc
GHC := ghc
GHC_WIN := wine ghc
OUT_DIR := out
OUT_DIR_WINDOWS := $(OUT_DIR)/windows
OUT_DIR_LINUX := $(OUT_DIR)/linux
RESOURCES := resources
TEMP_DIR := tmp
SDL_DLL := /usr/i686-w64-mingw32/bin/SDL2*.dll
GO_TO_TMP := cd $(TEMP_DIR)
HASKELL_LIB_NAME_LINUX := libAI.so
HASKELL_LIB_PATH_LINUX := $(TEMP_DIR)/$(HASKELL_LIB_NAME_LINUX)
HASKELL_LIB_NAME_WINDOWS := libAI.dll
HASKELL_LIB_PATH_WINDOWS := $(TEMP_DIR)/$(HASKELL_LIB_NAME_WINDOWS)
HASKELL_EXEC_PATH := $(TEMP_DIR)/PrehistoricWorld
HASKELL_LIB := $(GHC) -O2 -dynamic -shared -fPIC -o $(HASKELL_LIB_NAME_LINUX) ../src/haskell/*.hs ../src/hsbracket.c -lHSrts_thr-ghc8.0.2
HASKELL_LIB_WINDOWS := $(GHC_WIN) -shared -o $(HASKELL_LIB_NAME_WINDOWS) ../src/haskell/*.hs ../src/hsbracket.c -lHSrts_thr
COMPILE_OBJ_LINUX := $(CC) -O2 -c `sdl2-config --libs --cflags` -lSDL2_image ../src/c/*.c
COMPILE_OBJ_WINDOWS := $(CC_WIN) -O2 -c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image ../src/c/*.c
EXEC_LINUX := $(CC) -o PrehistoricWorld ./*.o `sdl2-config --libs --cflags` -lSDL2_image -lm -L. -lAI -Wl,-rpath,'$$ORIGIN'
EXEC_WINDWOS := $(CC_WIN) -o PrehistoricWorld.exe ./*.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm -L. -lAI -Wl,-rpath,'$$ORIGIN'

.PHONY: all
all: linux windows

linux: create_dirs_linux copy_resources_linux build_linux move_exec_linux
windows: create_dirs_windows copy_resources_windows copy_sdl build_windows move_exec_windows

create_dirs_linux:
	mkdir -p $(OUT_DIR_LINUX);
	mkdir -p $(TEMP_DIR);

create_dirs_windows:
	mkdir -p $(OUT_DIR_WINDOWS);
	mkdir -p $(TEMP_DIR);

copy_resources_linux:
	cp -r $(RESOURCES) $(OUT_DIR_LINUX)

copy_resources_windows:
	cp -r $(RESOURCES) $(OUT_DIR_WINDOWS)	

copy_sdl:
	cp -r $(SDL_DLL) $(OUT_DIR_WINDOWS)

build_linux: 
	$(GO_TO_TMP) && $(HASKELL_LIB) && echo "[OK] HASKELL_LIB";
	$(GO_TO_TMP) && $(COMPILE_OBJ_LINUX) && echo "[OK] COMPILE_OBJ_LINUX"; 
	$(GO_TO_TMP) && $(EXEC_LINUX) && echo "[OK] EXEC_LINUX"; 

build_windows: 
	$(GO_TO_TMP) && $(HASKELL_LIB_WINDOWS) && echo "[OK] HASKELL_LIB_WINDOWS"; 
	$(GO_TO_TMP) && $(COMPILE_OBJ_WINDOWS) && echo "[OK] COMPILE_OBJ_WINDOWS"; 
	$(GO_TO_TMP) && $(EXEC_WINDWOS) && echo "[OK] EXEC_WINDWOS"; 

move_exec_linux: 
	mv $(HASKELL_LIB_PATH_LINUX) $(OUT_DIR_LINUX);
	mv $(HASKELL_EXEC_PATH) $(OUT_DIR_LINUX);
	
move_exec_windows: 
	mv $(HASKELL_LIB_PATH_WINDOWS)* $(OUT_DIR_WINDOWS);
	mv $(HASKELL_EXEC_PATH).exe $(OUT_DIR_WINDOWS);

# --------------------------------------------------------------

.PHONY: test

test: HASKELL_LIB remove_main build_test

remove_main: 
	rm $(TEMP_DIR)/main.o && echo "[OK]  $@"

build_test:
	$(COMPILE_TEST) && echo "[OK]  $@"

.PHONY: clean, clear

clean clear:
	@rm -f src/*.o && echo "[CL]  src"
	@rm -f src/haskell/*.o src/haskell/*.hi src/haskell/*.h && echo "[CL]  src/haskell"
	@rm -r -f $(OUT_DIR)/ && echo "[CL]  target"
	@rm -r -f $(TEMP_DIR)/ && echo "[CL]  tmp"
