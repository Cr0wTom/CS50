//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

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

// height and width of the paddle
#define PADDLE_H 10
#define PADDLE_W 50

// height and width of the bricks
#define BRICK_H 10
#define BRICK_W (WIDTH / 10 - 5 )

// vertical placement of paddle
#define PAD_VERT 520

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

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
	
    // ball's initial velocity
    double x_vel = drand48();
    double y_vel = (drand48() * 1.5);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // bounce if ball hits the top
        if (getY(ball) <= 0)
        {
            y_vel = -y_vel;
        }
        
        // bounce if ball hits the edges
        if(getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_vel = -x_vel;
        }
        else if (getX(ball) <= 0)
        {
            x_vel = -x_vel;
        }
        
        // collision detection
        if (detectCollision(window,ball)!=NULL)
        {           
            GObject collision = detectCollision(window, ball);
            
            if (strcmp(getType(collision), "GRect") == 0)
            {          
                if (collision != paddle)
                {
                    removeGWindow(window, collision);
                    points++;
                    bricks--;
                    updateScoreboard(window, label, points);
                    y_vel = -y_vel;
                }
                
                if (collision == paddle)
                {
                    y_vel = -y_vel;
                }           
            }     
        } 
        
        // pause if ball hits the bottom
        if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;         
            waitForClick();
            y_vel = -y_vel;
        }
        
        // make ball move
        move(ball, x_vel, y_vel);
        pause(3);
             
        // move the paddle horizontally
        // and check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if a mouse event takes place
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // we ensure that paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, PAD_VERT);
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
    int x = 2;
    int y = 5;
    for (int i = 1; i <= ROWS; i++)
    {
        for (int j = 1; j <= COLS; j++)
        {
            GRect brick = newGRect(x, y, BRICK_W, BRICK_H);
            setFilled(brick, true);
            setColor(brick, "BLUE");
            add(window, brick);
            x+=(BRICK_W + 5);
        }
        x = 2;
        y+=(BRICK_H + 5);
    }   
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate circle
    GOval ball = newGOval((WIDTH/2 - RADIUS), (HEIGHT/2 - RADIUS), 2*RADIUS, 2*RADIUS);
    setFilled(ball, true);
    setColor(ball, "RED"); 
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH/2 - .5*PADDLE_W, PAD_VERT, PADDLE_W, PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-18");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) + getFontAscent(label)) / 2;
    setLocation(label, x, y);
    add(window, label);
    
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
