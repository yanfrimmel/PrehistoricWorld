LIB := ghc -c -O src/haskell/** -outputdir tmp
CC := gcc
GHC := ghc --make `sdl2-config --libs --cflags` -optc-O src/c/*.c src/haskell/*.hs -no-hs-main -outputdir tmp -lSDL2_image -o targetLinux/PrehistoricWorld
FLAGS := `sdl2-config --libs --cflags`  -ggdb3 -O0 --std=c99 -lSDL2_image -lm -Wall -I/usr/lib/ghc/include -Idist/build/
HDRS := $(wildcard src/c/*.h) 
SRCS := $(wildcard src/c/*.c)
OBJS := $(SRCS:src/c/%.c=tmp/%.o)
EXEC := targetLinux/PrehistoricWorld
#---------------------------------------------------------- test
FLAGS_TEST    := $(FLAGS)
SRCS_TEST     := $(wildcard test/c/*.c)
OBJS_TEST     := $(filter-out tmp/main.o, $(OBJS)) $(SRCS_TEST:test/c/%.c=tmp/%.o)
EXEC_TEST     := targetLinux/test

.SUFFIXES:
#---------------------------------------------------------- Targets

.PHONY: all

all: lib ghc
	
lib: 
	$(LIB) && echo "[OK]  $@"

# $(EXEC): $(OBJS) $(HDRS) Makefile
# 	$(CC) -o $@ $(OBJS) $(FLAGS) && echo "[OK]  $@"

ghc: 
	$(GHC) && echo "ghc [OK]  $@"
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
	@rm -r -f targetLinux/* && echo "[CL]  targetLinux/"
	@rm -r -f tmp/* && echo "[CL]  tmp/"
