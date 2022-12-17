CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g -Iinclude
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

TGT = sokoban-clone
SRC = $(shell find -type f -name "*.c")
OBJ = $(SRC:./src/%.c=./build/%.o)
SRC_DIR =  $(shell find src -type d)
OBJ_DIR = $(SRC_DIR:src/%=build/%)

EMFLAGS = -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=['png']
EMFLAGS += -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 --preload-file res

WEB_DIR = web_build

all: ${OBJ_DIR} ${TGT}

web: ${WEB_DIR} ${SRC}
	emcc ${SRC} ${CFLAGS} ${EMFLAGS} -o ${WEB_DIR}/index.html

${WEB_DIR}:
	mkdir -p $@

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
		rm -fr web_build/
		rm ${TGT}