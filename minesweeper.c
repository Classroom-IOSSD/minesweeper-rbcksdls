/**
* @file minesweeper.c
* @author rbcksdls <rbcksdls@naver.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio.h"
#include "color.h"
#define MAX 10

#define INPUT_MODE 0
#define FLAG_MODE 1
#define CHECK_MODE 2

// global variables
/// global variables
// game table
unsigned char table_array[MAX][MAX];
// location of cursor
int x = 0;
int y = 0;
int game_mode = INPUT_MODE;

/**
* This is a recursive function which uncovers blank cells while they are adjacent
*/
/*This is a recursive function which uncovers blank cells while they are adjacent*/
bool isOutofBound = (rows[i] >= 0 && rows[i] < MAX) && (columns[i] >= 0 && columns[i] < MAX);
int uncover_blank_cell(int row, int col) {
	int value = 0;
	int rows[8] = {};
	int columns[8] = {};
	int i = 0;

	if (table_array[row][col] != 0) {
		return 0; // error
	}
	table_array[row][col] += 10; // uncover current cell

								 // Get position of adjacent cells of current cell
	rows[0] = row - 1;
	columns[0] = col + 1;

	rows[1] = row;
	columns[1] = col + 1;

	rows[2] = row + 1;
	columns[2] = col + 1;

	rows[3] = row - 1;
	columns[3] = col;

	rows[4] = row + 1;
	columns[4] = col;

	rows[5] = row - 1;
	columns[5] = col - 1;

	rows[6] = row;
	columns[6] = col - 1;

	rows[7] = row + 1;
	columns[7] = col - 1;

	for (i = 0; i < 8; i++) {
		value = table_array[rows[i]][columns[i]];

		if (isOutofBound) {	// to prevent negative index and out of bounds
			if (value > 0 && value <= 8) {
				table_array[rows[i]][columns[i]] += 10;
			}	// it is a cell with 1-8 number so we need to uncover
			else if (value == 0) {
				uncover_blank_cell(rows[i], columns[i]);
			}
		}
	}

	return 1; // success!
}

void print_table() {
	// clear screen
	system("clear");

	int i, j, value;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (x == j && y == i) {
				if (game_mode == FLAG_MODE) {
					printf("|%sF%s", BMAG, KNRM);
					continue;
				}
				else if (game_mode == CHECK_MODE) {
					printf("|%sC%s", BMAG, KNRM);
					continue;
				}

			}
			value = table_array[i][j];

			if ((value >= 0 && value <= 8) || value == 0 || value == 99)
				printf("|X");
			else if (value == 10) // clean area
				printf("|%s%d%s", KCYN, value - 10, KNRM);
			else if (value == 11) // the number of near mine is 1
				printf("|%s%d%s", KYEL, value - 10, KNRM);
			else if (value > 11 && value <= 18) // the number of near mine is greater than 1
				printf("|%s%d%s", KRED, value - 10, KNRM);
			else if ((value >= 20 && value <= 28) || value == 100)
				printf("|%sF%s", KGRN, KNRM);
			else
				printf("ERROR"); // test purposes

		}
		printf("|\n");
	}

	printf("cell values: 'X' unknown, '%s0%s' no mines close, '1-8' number of near mines, '%sF%s' flag in cell\n", KCYN, KNRM, KGRN, KNRM);
	if (game_mode == INPUT_MODE) {
		printf("f (put/remove Flag in cell), c (Check cell), n (New game), q (Exit game): ");
	}
	else if (game_mode == FLAG_MODE) {
		printf("Enter (select to put/remove Flag in cell), q (Exit selection): ");
	}
	else if (game_mode == FLAG_MODE) {
		printf("Enter (select to check cell), q (Exit selection): ");
	}


}


int main(int argc, char *argv[]) {
	char ch;
	int nMines = 10; // the number of the remaining mines
	int value;

	newGame(argc, argv, nMines, ch, value);

	return 0;
}

///newGame function
void newGame(int argc, char *argv[], int nMines, char ch, int value) {
	int i;
	int j;
	int r;
	int c;
	int rows[8];
	int columns[8];

	if (argc == 2) {
		nMines = atoi(argv[1]);
	}
	srand(time(NULL));						// random seed
											// setting cursor
	x = 0;
	y = 0;
	// set all cells to 0
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			table_array[i][j] = 0;

	for (i = 0; i < nMines; i++) {
		/* initialize random seed: */

		r = rand() % 10;					// it generates a integer in the range 0 to 9
		c = rand() % 10;

		// put mines
		if (table_array[r][c] != 99) {
			table_array[r][c] = 99;

			// Get position of adjacent cells of current cell
			rows[0] = r - 1;
			columns[0] = c + 1;
			rows[1] = r;
			columns[1] = c + 1;
			rows[2] = r + 1;
			columns[2] = c + 1;
			rows[3] = r - 1;
			columns[3] = c;
			rows[4] = r + 1;
			columns[4] = c;
			rows[5] = r - 1;
			columns[5] = c - 1;
			rows[6] = r;
			columns[6] = c - 1;
			rows[7] = r + 1;
			columns[7] = c - 1;

			for (j = 0; j < 8; j++) {
				value = table_array[rows[j]][columns[j]];
				if ((rows[j] >= 0 && rows[j] < MAX) && (columns[j] >= 0 && columns[j] < MAX)) {	// to prevent negative index and out of bounds
					if (value != 99)																// to prevent remove mines
						table_array[rows[j]][columns[j]] += 1;									// sums 1 to each adjacent cell
				}
			}

		}
		else {							// to make sure that there are the properly number of mines in table
			i--;
			continue;
		}
	}

	//
	while (nMines != 0) {			// when nMines becomes 0 you will win the game
		print_table();

		ch = getch();
		// cursor direction
		char direction;
		switch (ch) {

			// flag
		case 'f':
		case 'F':
			flagMode(argc, argv, direction, nMines, value, ch);
			break;
			// check cell
		case 'c':
		case 'C':
			checkMode(argc, argv, direction, nMines, value, ch);
			break;
			// jump to a new game
		case 'n':
		case 'N':
			newGame(argc, argv, nMines, ch, value);
			break;
			// exit
		case 'q':
		case 'Q':
			endGame(argc, argv, nMines, ch, value);
		default:
			break;
		}
	}
}

///endGame function
void endGame(int argc, char *argv[], int nMines, char ch, int value) {

	game_mode = INPUT_MODE;
	print_table();
	printf("\nGAME OVER\n");

	if (nMines == 0)
		printf("you won!!!!\n");

	else
		printf("BOOM! you LOOSE!\n");

	do {
		printf("Are you sure to exit? (y or n)? ");
		ch = getch();
		putchar('\n');
		if (ch == 'y' || ch == 'Y') {
			break;
		}
		else if (ch == 'n' || ch == 'N') {
			newGame(argc, argv, nMines, ch, value);
		}
		printf("Please answer y or n\n");
	} while (1);
	printf("See you next time!\n");

	fflush(stdin);
}

///flagMode function
void flagMode(int argc, char *argv[], char direction, int nMines, int value, char ch) {
	game_mode = FLAG_MODE;
	do {
		print_table();
		direction = getch();
		// arrow direction
		if (direction == '8') {
			// up
			y = (MAX + --y) % MAX;
		}
		else if (direction == '2') {
			// down
			y = ++y % MAX;
		}
		else if (direction == '4') {
			x = (MAX + --x) % MAX;
		}
		else if (direction == '6') {
			x = ++x % MAX;
		}
		else if (direction == 'c' || direction == 'C') {
			checkMode(argc, argv, direction, nMines, value, ch);
		}
		else if (direction == '\n') {
			value = table_array[y][x];

			if (value == 99) {				// mine case
				table_array[y][x] += 1;
				nMines -= 1;				// mine found
			}
			else if (value >= 0 && value <= 8) {	// number of mines case (the next cell is a mine)
				table_array[y][x] += 20;
			}
			else if (value >= 20 && value <= 28) {
				table_array[y][x] -= 20;
			}

			if (nMines == 0)
				break;
		}
	} while (direction != 'q' && direction != 'Q');
	game_mode = INPUT_MODE;
}

///checkMode function
void checkMode(int argc, char *argv[], char direction, int nMines, int value, char ch) {
	game_mode = CHECK_MODE;
	do {
		print_table();
		direction = getch();

		// arrow direction
		if (direction == '8') {
			// up
			y = (MAX + --y) % MAX;
		}
		else if (direction == '2') {
			// down
			y = ++y % MAX;
		}
		else if (direction == '4') {
			x = (MAX + --x) % MAX;
		}
		else if (direction == '6') {
			x = ++x % MAX;
		}
		else if (direction == 'f' || direction == 'F') {
			flagMode(argc, argv, direction, nMines, value, ch);
		}

		else if (direction == '\n') {
			value = table_array[y][x];
			if (value == 0)						// blank case
				uncover_blank_cell(y, x);
			else if (value == 99)				// mine case
				endGame(argc, argv, nMines, ch, value);
			else if (value > 0 && value <= 8)	// number case (the next cell is a mine)
				table_array[y][x] += 10;

			//	break;
		}
	} while (direction != 'q' && direction != 'Q');
	game_mode = INPUT_MODE;
}