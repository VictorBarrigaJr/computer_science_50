/*******************************************************************************
 * breakout.c (c) by Victor Barriga
 * 
 * breakout.c is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 * 
 * breakout.c 
 * Computer Science 50
 * Problem Set 4 - Fifteen
 *
 * Usage: ./breakout d
 *
 * Implements the game breakout
 **/

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // ball velocity
    double dx = 0.06;
    double velocity = pow(dx, 2) * 2;
    double dy = (sqrt(velocity - pow(dx, 2)));

    // wait for user to click the mouse to initiate game
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    
        /* locks paddle to curser by check for mouse event, movement*/
        GEvent mouse = getNextEvent(MOUSE_EVENT); 
        if(mouse != NULL)
        {
            if(getEventType(mouse) == MOUSE_MOVED)
            {
                double x = getX(mouse) - getWidth(paddle) / 2;
                double y = 500;
                setLocation(paddle, x, y);
            }
        }
        
        // Move ball, using ball velocity
        move(ball, dx, dy);
        
        // bounce off window right and left sides
        if ((getX(ball) + getWidth(ball) >= WIDTH) || getX(ball) <= 0)
        {
            // reverse ball direction
            dx *= -1;
        }
        // bounce off window top
        else if (getY(ball) <= 0)
        {
            // reverse ball direction
            dy *= -1;
        }
        // ball missed by paddle, loose a life reset
        else if ((getY(ball) + getHeight(ball) >= HEIGHT))
        {
            // loose life
            lives--;
            // reset ball location
            setLocation(ball, (WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS);
            // reset paddle location
            setLocation(paddle, (WIDTH / 2) - (getWidth(paddle) / 2), 550);
            // reset velocity
            dx = 0.06;
            dy = (sqrt(velocity - pow(dx, 2)));
            // wait for player
            waitForClick();            
        }
                
        // detect Collision
        GObject object = detectCollision(window, ball);
        // initiate if collision is true
        if (object != NULL && strcmp(getType(object), "G3DRect") == 0)
        {
            // reverse ball direction
            dy *= -1;
            // brick hit
            if (object != paddle)
            {
                // remove brick
                removeGWindow(window, object);
                // subtract brick
                bricks--;
                // add point
                points++;
                // update Score board
                updateScoreboard(window, label, points);               
            } 
        }
        
    }
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // initialize brick y window coordinates 
    int brick_y = 100;
    
    for (int i = 0, color_index = 0; i < ROWS; i++, color_index++)
    {
        // initialize x for first left brick in row
        int brick_x = 2;
        // padding & brick demensions
        int padding = 5, width = 35, height = 10; 
        // brick colors by rows
        string colors[] = { "RED", "ORANGE", "YELLOW", "GREEN", "CYAN" };
        
        // draw bricks filled with color by row.
        for(int j = 0; j < COLS; j++)
        {
            G3DRect brick = newG3DRect(brick_x + padding, brick_y, 
                                       width, height, true);
            setColor(brick, colors[color_index]);
            setFilled(brick, true);
            add(window, brick);
            brick_x += (width + padding - 1);
        }
        brick_y += (height + padding);
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // ball constants
    int x = (WIDTH / 2) - RADIUS;
    int y = (HEIGHT / 2) - RADIUS;
    
    // draw ball
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setColor(ball,"BLACK");
    setFilled(ball, true);
    add(window, ball);
        
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // paddle constants
    int width = 70;
    int height = 10;
    
    // draw paddle
    G3DRect paddle = newG3DRect((WIDTH / 2) - (width / 2), 
                                500, width, height, true);
    setFilled(paddle, true);
    setColor(paddle, "BLUE");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate label
    GLabel label = newGLabel("0");
    
    // label constants center
    double x = (WIDTH - getWidth(label)) / 2 - getWidth(label);
    double y = ((HEIGHT - getHeight(label)) / 2) - 20;
    
    setFont(label, "SansSerif-50");
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    setLocation(label, x, y);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
