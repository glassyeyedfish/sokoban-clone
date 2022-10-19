CC = cc
CFLAGS = -ansi -pedantic -Wall -Wextra -g
LDFLAGS = -lSDL2

TGT = squaregame
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

all: build/ ${TGT}

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./${TGT}

build/:
	mkdir -p build

build/%.o: src/%.c
		${CC} -c ${CFLAGS} $< -o $@

${TGT}: ${OBJ}
		${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
		rm build/*
		rm ${TGT}
