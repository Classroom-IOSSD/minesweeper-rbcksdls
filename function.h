#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio.h"
#include "color.h"
#define MAX 10

#define INPUT_MODE 0
#define FLAG_MODE 1
#define CHECK_MODE 2

#define BIT(x) (0x01 << (x))
#define BITMASK_SET(x, y) ((x) |= (y))
#define BITMASK_CLEAR(x, y) ((x) &= (~(y)))
#define BITMASK_FLIP(x, y) ((x) ^= (y))
#define BITMASK_CHECK(x, y) (((x) & (y)) == (y))

// global variables
/// global variables
// game table
unsigned char table_array[MAX][MAX];
// location of cursor
int x = 0;
int y = 0;
int game_mode = INPUT_MODE;

const unsigned int FLAG_MASK = BIT(4);
const unsigned int UNCOVERED_MASK = BIT(5);
const unsigned int MINE_MASK = BIT(6);

/**
* This is a recursive function which uncovers blank cells while they are adjacent
*/
/*This is a recursive function which uncovers blank cells while they are adjacent*/

