CC = gcc
CCFLAGS = -Wall -g

all: game game.o 

game.o: game.c game.h
	${CC} ${CCFLAGS} -c game.c

game: game.o game_types.h
	${CC} ${CCFLAGS} -o game game.o 

#autoconf
#automake