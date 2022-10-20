CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -Iinclude
LDFLAGS = -lSDL2

TGT = squaregame
SRC = $(shell find -type f -name "*.c")
OBJ = $(SRC:./src/%.c=./build/%.o)

all: $(dir ${OBJ}) ${TGT}

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./${TGT} tests/test.taf

$(dir ${OBJ}):
	mkdir -p $(dir ${OBJ})

build/%.o: src/%.c
		${CC} -c ${CFLAGS} $< -o $@

${TGT}: ${OBJ}
		${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
		rm -fr build/
		rm ${TGT}