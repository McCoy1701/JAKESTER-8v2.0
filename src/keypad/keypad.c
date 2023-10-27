#include <wiringPi.h>
#include "keypad.h"

int COL[ COLS ] = { 21, 22, 23, 24 };
int ROW[ ROWS ] = { 30, 14, 13, 12 };

char keypad_0[ ROWS ][ COLS ] = { { 'C', 'D', 'E', 'F' },
                                  { '8', '9', 'A', 'B' },
                                  { '4', '5', '6', '7' },
                                  { '0', '1', '2', '3' }};

char keypad_1[ ROWS ][ COLS ] = { { 'A', 'B', 'C', 'D' },
                                  { 'E', 'F', 'G', 'H' },
                                  { 'I', 'J', 'K', 'L' },
                                  { 'M', 'N', 'O', 'P' }};

char keypad_2[ ROWS ][ COLS ] = { { 'Q', 'R', 'S', 'T' },
                                  { 'U', 'V', 'W', 'X' },
                                  { 'Y', 'Z', ';', ':' },
                                  { ' ', '.', '|', '&' }};

void setupKeypad( void )
{
  pinMode( PAGE_A, INPUT );
  pinMode( PAGE_B, INPUT );

  for ( int i = 0; i < ROWS; i++ )
  {
    pinMode( ROW[i], OUTPUT );
    digitalWrite( ROW[i], HIGH );

  }

  for ( int j = 0; j < COLS; j++ )
  {
    pinMode( COL[j], INPUT );
    pullUpDnControl( COL[j], PUD_UP );
  }
}

char getKey( void )
{
  for ( int i = ROWS; i >= 0; i-- )
  {
    digitalWrite( ROW[i], LOW );

    for ( int j = 0; j < COLS; j++ )
    {
      if ( digitalRead( COL[j] ) == 0 )
      {
        digitalWrite( ROW[i], HIGH );
        delay(250);
        return keypad_0[i][j];
      }
    }
    digitalWrite( ROW[i], HIGH );
  }
  return '\0';
}

