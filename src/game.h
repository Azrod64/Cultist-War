#ifndef _GAME_H
#define _GAME_H

#include "game_types.h" //test-2

void initGame(board, unitsArray); //initialize the board, put obstacles and neutral units (symetric)

void printBoard(board board); //print the board on terminal

void wait(void);

int algo_Bresenham(board board, int x1, int y1, int x2, int y2,tab_move tableau_mouv);

void print_unitsArray(unitsArray nb_unite); //print the unitsArray

void move(board, unitsArray, int unitId, int x, int y);

void shoot(board, unitsArray, int unitId, int targetId,tab_move tableau_mouv);

void convert(board, unitsArray, int unitId, int targetId);

#endif
