all: game game.o 

game.o: game.c game.h
	gcc -c game.c

game: game.c game.h game_types.h
	gcc -o game game.c 

