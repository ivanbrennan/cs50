/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

// constants
#define DIM_MIN  3
#define DIM_MAX  9
#define GOD_MODE 0

// board
int board[DIM_MAX][DIM_MAX];

// index
int index[DIM_MAX * DIM_MAX];
typedef struct
{
	int x;
	int y;
} point;

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
point tileLocation(int tileNum);
point indexToPoint(int idx);
int pointToIndex(point p);
void makeRandomMoves(void);
void makeRandomMove(void);
void draw(void);
int getTile(void);
void getInput(char input[], const int maxInput);
void removeNewline(char * const str);
void discardExcessInput(void);
void godSolve(void);
bool move(int tile);
bool isLegalMove(point fromPoint, point toPoint);
bool isLegalTile(point p);
bool coordsAreLegal(int row, int col);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
		int tile = getTile();
		if (tile == GOD_MODE)
		{
			/* godSolve(); */
			break;
		}

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        /* usleep(500000); */
    }

    // success
    return 0;
}

int getTile(void)
{
	const int maxInput = 4;
	char input[maxInput];

	int tile = 0;

	while (!tile)
	{
		getInput(input, maxInput);

		if (strcmp(input, "GOD") == 0) {
			return GOD_MODE;
		} else {
			tile = atoi(input);
		}
		if (!tile) {
			printf("Retry: ");
		}
	}

	return tile;
}

void getInput(char input[], const int maxInput)
{
	fgets(input, maxInput, stdin);

	removeNewline(input);
	if (strlen(input) == maxInput-1)
	{
		discardExcessInput();
	}
}

void removeNewline(char * const str)
{
	char *newline;

	if ((newline = strchr(str, '\n')) != NULL)
	{
		*newline = '\0';
	}
}

void discardExcessInput(void)
{
	while (getchar() != '\n')
	{
		// do nothing
	}
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
	for (int i = 1; i < d*d; i++)
	{
		int idx = i - 1;
		point p = indexToPoint(idx);
		board[p.x][p.y] = i;
		index[i] = idx;
	}
	board[d-1][d-1] = 0;
	index[0] = d*d - 1;

	makeRandomMoves();
}

void makeRandomMoves(void)
{
	srand48((long int) time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		makeRandomMove();
	}
}

void makeRandomMove(void)
{
	point blank = tileLocation(0);

	point candidates[4];
	point *p = candidates;

	for (double r = 0; r < 2*M_PI; r += M_PI_2)
	{
		int row = blank.x + cos(r);
		int col = blank.y + sin(r);

		if (coordsAreLegal(row, col))
		{
			*(p++) = (point) { row, col };
		}
	}

	int num_candidates = p - candidates;
	int rand = (int) (drand48() * num_candidates);
	int tileNum = board[candidates[rand].x][candidates[rand].y];

	move(tileNum);
}

point tileLocation(int tileNum)
{
	int idx = index[tileNum];
	return indexToPoint(idx);
}

point indexToPoint(int idx)
{
	point p = { .x = (idx / d), .y = (idx % d) };
	return p;
}

int pointToIndex(point p)
{
	return (p.x * d) + (p.y % d);
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
		{
			if (board[i][j] > 0)
			{
				printf("%3i", board[i][j]);
			}
			else
			{
				printf("  _");
			}
		}
		printf("\n\n");
	}
}

void godSolve(void)
{
	int moves[4] = { 0 };
	int iMove = 0;
	printf("possible moves:");
	for (int i = 0; i < iMove; i++)
	{
		printf(" %i", moves[i]);
	}
	printf("\n");
	// for (int i = 0; i < iMove; i++)
	//   if fVal(currentMove) < bestMove
	//     bestMove = currentMove
	// move(bestMove)
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tileNum)
{
	point blank = tileLocation(0);
	point tile  = tileLocation(tileNum);

	if (isLegalMove(tile, blank))
	{
		board[blank.x][blank.y] = tileNum;
		board[tile.x][tile.y]   = 0;

		index[tileNum] = pointToIndex(blank);
		index[0]       = pointToIndex(tile);

		return true;
	}
	else
	{
		return false;
	}
}

bool isLegalMove(point pointA, point pointB)
{
	if (isLegalTile(pointA) && isLegalTile(pointB))
	{
		int xDiff = abs(pointA.x - pointB.x);
		int yDiff = abs(pointA.y - pointB.y);

		return xDiff + yDiff == 1;
	}
	else
	{
		return false;
	}
}

bool isLegalTile(point p)
{
	return coordsAreLegal(p.x, p.y);
}

bool coordsAreLegal(int row, int col)
{
	bool isLegalRow = row >= 0 && row < d;
	bool isLegalCol = col >= 0 && col < d;

	return isLegalRow && isLegalCol;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
	for (int i = 1; i < d*d; i++)
	{
		if (index[i] != i-1)
		{
			return false;
		}
	}

	return true;
}
