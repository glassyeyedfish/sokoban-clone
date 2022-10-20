CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -Iinclude
LDFLAGS = -lSDL2

TGT = squaregame
SRC = $(shell find -type f -name "*.c")
OBJ = $(SRC:./src/%.c=./build/%.o)
SRC_DIR =  $(shell find src -type d)
OBJ_DIR = $(SRC_DIR:src/%=build/%)

all: ${OBJ_DIR} ${TGT}

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./${TGT} tests/test.taf

${OBJ_DIR}:
	mkdir -p $@

build/%.o: src/%.c
		${CC} -c ${CFLAGS} $< -o $@

${TGT}: ${OBJ}
		${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
		rm -fr build/
		rm ${TGT}