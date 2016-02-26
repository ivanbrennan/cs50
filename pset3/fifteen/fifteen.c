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
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];
int index[DIM_MAX * DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
int  initTileVal(int row, int col);
int countDownFromMax(int row, int col);
int  oneOrTwo(int col);
void draw(void);
void printTile(int tileVal);
bool move(int tile);
bool legalMove(int fromRow, int fromCol, int toRow, int toCol);
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

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
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

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
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
	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d; j++)
		{
			int tile = initTileVal(i, j);

			board[i][j] = tile;
			index[tile] = i*d + j;
		}
	}
}

int initTileVal(int row, int col)
{
	if (row < d-1 || col < d-3)
	{
		return countDownFromMax(row, col);
	}
	else if (col < d-1)
	{
		return oneOrTwo(col);
	}
	else
	{
		return 0;
	}
}

int countDownFromMax(int row, int col)
{
	int maximumValue   = d*d - 1;
	int prevTilesCount = d*row + col;

	return maximumValue - prevTilesCount;
}

int oneOrTwo(int col)
{
	return (d-3 + col + d % 2) % 2 + 1;
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
			printTile(board[i][j]);
		}
		printf("\n\n");
	}
}

void printTile(int tileVal)
{
	if (tileVal)
	{
		printf("%4i", tileVal);
	}
	else
	{
		printf("%4c", '_');
	}
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
	if (tile < 0 || tile >= d*d)
	{
		return false;
	}

	int tileIndex = index[tile];
	int tileRow = tileIndex / d;
	int tileCol = tileIndex % d;

	int emptyIndex = index[0];
	int emptyRow = emptyIndex / d;
	int emptyCol = emptyIndex % d;

	if (legalMove(tileRow, tileCol, emptyRow, emptyCol))
	{
		board[tileRow][tileCol] = 0;
		index[0] = tileIndex;

		board[emptyRow][emptyCol] = tile;
		index[tile] = emptyIndex;

		return true;
	}
	else
	{
		return false;
	}
}

bool legalMove(int fromRow, int fromCol, int toRow, int toCol)
{
	int dist = (fromRow - toRow) + (fromCol - toCol);

	return (dist == 1 || dist == -1);
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
