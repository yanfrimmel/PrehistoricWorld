COMPILE_HASKELL := ghc -c -O src/haskell/** -outputdir tmp
COMPILE_C := ghc --make `sdl2-config --libs --cflags` -lSDL2_image -optc-O src/c/*.c src/haskell/*.hs -no-hs-main -outputdir tmp -o target/linux/PrehistoricWorld -Wall

CC := gcc
FLAGS := `sdl2-config --libs --cflags`  -ggdb3 -O0 --std=c99 -lSDL2_image -lm -Wall -I/usr/lib/ghc/include -Idist/build/

COMPILE_C_WINDOWS := ghc --make `x86_64-w64-mingw32-gcc -lmingw32` -lSDL2main -lSDL2 -lSDL2_image -optc-O src/c/*.c src/haskell/*.hs -no-hs-main -outputdir tmp -o target/windows/PrehistoricWorld.exe -Wall

CC_WINDOWS := x86_64-w64-mingw32-gcc
FLAGS_WINDOWS := -lmingw32 -lSDL2main -lSDL2 -ggdb3 -O0 --std=c99 -lSDL2_image -lm  -Wall

HDRS := $(wildcard src/c/*.h) 
SRCS := $(wildcard src/c/*.c)
OBJS := $(SRCS:src/c/%.c=tmp/%.o)
EXEC := targetLinux/PrehistoricWorld
#---------------------------------------------------------- test
FLAGS_TEST    := $(FLAGS)
SRCS_TEST     := $(wildcard test/c/*.c)
OBJS_TEST     := $(filter-out tmp/main.o, $(OBJS)) $(SRCS_TEST:test/c/%.c=tmp/%.o)
EXEC_TEST     := targetLinux/test
#---------------------------------------------------------- Targets
.PHONY: all
all: linux windows
linux: COMPILE_HASKELL COMPILE_C
windows: COMPILE_HASKELL COMPILE_C_WINDOWS
	
COMPILE_HASKELL: 
	$(COMPILE_HASKELL) && echo "[OK]  $@"

COMPILE_C: 
	$(COMPILE_C) && echo "[OK]  $@"

COMPILE_C_WINDOWS: 
	$(COMPILE_C_WINDOWS) && echo "[OK]  $@"	

# $(EXEC): $(OBJS) $(HDRS) Makefile
# 	$(CC) -o $@ $(OBJS) $(FLAGS) && echo "[OK]  $@"
# --------------------------------------------------------------

.PHONY: test

test: $(EXEC_TEST)

$(EXEC_TEST): $(OBJS_TEST)
	$(CC) -o $@ $(OBJS_TEST) $(FLAGS_TEST) && echo "EXEC_TEST [OK] $@"

# --------------------------------------------------------------

tmp/%.o: src/c/%.c
	@$(CC) $(FLAGS) -c $< -o $@ && echo "tmp/%.o: src/c/%.c [OK]  $@"

tmp/%.o: test/c/%.c
	@$(CC) $(FLAGS_TEST) -c $< -o $@ && echo "tmp/%.o: test/c/%.c [OK]  $@"

.PHONY: clean, clear

clean clear:
	@cabal clean
	@rm -r -f target/linux/* && echo "[CL]  target/linux/"
	@rm -r -f target/windows/* && echo "[CL]  target/windows/"
	@rm -r -f tmp/* && echo "[CL]  tmp/"
