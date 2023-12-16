#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jakestering.h"
#include "lcd128x64.h"

typedef struct _ball
{
  int x, y;
  int velx, vely;
  float friction;
} Ball;

typedef struct _paddle
{
  int x1, y1;
  int x2, y2;
  int vely;
} Paddle;

Ball *ballInit( int x, int y, int speed, float friction );

Paddle *paddleInit( int x1, int y1, int x2, int y2, int vely );

float getRandomNumber( float value1, float value2 );

LCD128 *lcd;

Ball *ball;

Paddle *paddleLeft;
Paddle *paddleRight;

int main( int argc, char **argv )
{
  setupIO();

  lcd = initLcd128( 0, 2,  3, 4, 5, 6, 7, 8, 9, 10, 12 ); //Initalize the 128x64 lcd

  ball = ballInit( 64, 24, 8, 0.89f );

  paddleLeft = paddleInit( 8, 24, 8, 40, 8 ); 
  paddleRight = paddleInit( 120, 24, 120, 40, -8 ); 

  setGraphicsMode( lcd );

  lcd128ClearGraphics( lcd );

  while (1)
  {
    ball->x += ball->velx; //Move the ball
    ball->y += ball->vely;

    paddleLeft->y1 = ball->y - 8; //Simple "AI" so the paddles will match the ball's y position and always make a hit
    paddleLeft->y2 = paddleLeft->y1 + 16;

    paddleRight->y1 = ball->y - 8;
    paddleRight->y2 = paddleRight->y1 + 16;

    if ( ( paddleLeft->y2 >= 63 ) || ( paddleLeft->y1 <= 0 ) ) //Reverse the paddle velocity if it hits a edge
    {
      if ( paddleLeft->y2 >= 63 )
      {
        paddleLeft->y2 = 63;
      }

      else if ( paddleLeft->y1 <= 0 )
      {
        paddleLeft->y1 = 0;
      }
    }

    if ( ( paddleRight->y2 >= 63 ) || ( paddleRight->y1 <= 0 ) )
    {
      if ( paddleRight->y2 >= 63 )
      {
        paddleRight->y2 = 63;
      }

      else if ( paddleRight->y1 <= 0 )
      {
        paddleRight->y1 = 0;
      }
    }

    if ( ( ( ball->x <= paddleLeft->x2 ) && ( ball->x >= paddleLeft->x1 ) && ( ball->y <= paddleLeft->y2 ) && ( ball->y >= paddleLeft->y1 ) ) ) //Check if the ball is within the paddles and it hasn't just been hit
    {
      ball->velx = -ball->velx;
      printf( "ball hit left\n" );
    }

    if ( ( ( ball->x <= paddleRight->x2 ) && ( ball->x >= paddleRight->x1 ) && ( ball->y <= paddleRight->y2 ) && ( ball->y >= paddleRight->y1 ) ) )
    {
      ball->velx = -ball->velx;
      printf( "ball hit right\n" );
    }

    if ( ( ball->x >= 128 ) || ( ball->x <= 0 ) ) //Check if ball hit play field egde if it hits on the x game ball is reset to the center
    {
      ball->velx = -ball->velx;
    }

    if ( ( ball->y >= 64 ) || ( ball->y <= 0 ) ) //If ball hits on the y egde the velocity is reversed
    {
      ball->vely = -ball->vely;
    }

    setGraphicsMode( lcd ); //Have to set graphics mode if you want to draw graphics

    lcd128DrawPixel( lcd, ball->x, ball->y );

    lcd128DrawLine( lcd, paddleRight->x1, paddleRight->y1, paddleRight->x2, paddleRight->y2 );
    lcd128DrawLine( lcd, paddleLeft->x1, paddleLeft->y1, paddleLeft->x2, paddleLeft->y2 );

    lcd128UpdateScreen( lcd ); //This updates the screen with the current frame buffer
  }

  free( lcd );
  free( ball );

  return 0;
}

Ball* ballInit( int x, int y, int speed, float friction )
{
  Ball *ball = ( Ball* )malloc( sizeof( Ball ) );

  ball->x = x;
  ball->y = y;
  ball->velx = speed;
  ball->vely = speed;
  ball->friction = friction;

  return ball;
}

Paddle *paddleInit( int x1, int y1, int x2, int y2, int vely )
{
  Paddle *paddle = ( Paddle* )malloc( sizeof( Paddle ) );

  paddle->x1 = x1;
  paddle->y1 = y1;
  paddle->x2 = x2;
  paddle->y2 = y2;

  paddle->vely = vely;

  return paddle;
}

