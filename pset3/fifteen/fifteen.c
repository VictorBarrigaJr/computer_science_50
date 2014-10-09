/*******************************************************************************
 * fifteen.c (c) by Victor Barriga
 * 
 * fifteen.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * fifteen.c 
 * Computer Science 50
 * Problem Set 3 - Fifteen
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// blanks location
int blank_r, blank_c;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/***
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/***
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/***
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // num of numbered tiles(1 blank)= d * d 
    int tiles = d * d;                    
    for (int row = 0; row < d; ++row)
    {
        for (int column = 0; column < d; ++column)
        {
            // assign tile numbers greatest to smallest.
            board[row][column] = --tiles;
        }
    }
    // assign blank
    board[d - 1][d - 1] = 915;
    // assing zero (blank tile) to track.
    blank_r = d - 1;
    blank_c = d - 1;
    
    // if tiles % 2 = 0, swap tiles 1 and 2
    if (d % 2 == 0) 
    {        
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }              
}

/***
 * Prints the board in its current state.
 */
void draw(void)
{ 
    printf("\n\t");
    // display board to console
    for (int row = 0; row < d; ++row)
    {
        for (int dashes = 0; dashes <= d; ++dashes)
        {
            
            printf("-----");
        }
        printf("\n\t ");
        printf("||");
        
        for (int column = 0; column < d; ++column)
        {
            if (board[row][column] == 915 || board[row][column] == 0)
            {
                printf("    |");
            }
            else
            {
            printf(" %2i |", board[row][column]);
            }
        }
        printf("|");
        printf("\n\t");
    }
        
    for (int dashes = 0; dashes <= d; ++dashes)
    {
        printf("-----");
    }
    printf("\n");
}

/***
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // check if tile out of boards range.
    if (tile <= 0 || tile >= d * d)
    {
        return false;
    }
    
    // find tile within board and check if its position is next to blank
    for (int row = 0; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        { 
            if (board[row][column] == tile) 
            {
                // check position above tile is blank, swaps 
                if (board[row - 1][column] == 915)
                {
                    board[blank_r][blank_c] = tile;
                    blank_r += 1;
                    board[row][column] = 915;
                    return true;
                }
                // check position below tile is blank, swaps
                else if (board[row + 1][column] == 915)
                {                    
                    board[blank_r][blank_c] = tile;
                    blank_r -= 1;
                    board[row][column] = 915;
                    return true;
                }
                // check position to the right of tile is blank, swaps 
                else if (board[row][column + 1] == 915)
                {                    
                    board[blank_r][blank_c] = tile;
                    blank_c -= 1;
                    board[row][column] = 915;
                    return true;
                }
                // check position to the left of tile is blank, swaps
                else if (board[row][column - 1] == 915)
                {                    
                    board[blank_r][blank_c] = tile;
                    blank_c += 1;
                    board[row][column] = 915;
                    return true;
                }
            }                
        }
     }
     return false;
}

/***
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{     
    if (board[d - 1][d - 1] != 915) // if false, does not go through loop.
    {
        return false;
    }
      
    // check if board is in order.
    for (int row = 0, tiles = 1; row < d; row++)
    {
        for (int column = 0; column < d; column++)
        {   
            if ((row == d - 1) && (column == d - 1)) // check last tile.
            {
                return true;
            }
            else if (board[row][column] != tiles) // if tile does not match
            {
                return false;
            }
            tiles++;
        }     
    }    
    return false;
    
}

/***
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
