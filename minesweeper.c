/**
* @file minesweeper.c
* @author rbcksdls <rbcksdls@naver.com>
*/

#include "function.h"

int main(int argc, char *argv[]) {
	char ch;
	int nMines = 10; // the number of the remaining mines
	int value;

	newGame(argc, argv, nMines, ch, value);

	return 0;
}