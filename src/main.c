#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <lcd.h>
#include <keypad.h>
#include <lcd128x64.h>
#include <jakestering.h>

LCD *lcd;
LCD128 *lcd128;
Keypad keypad;

int main ( int argc, char *argv[] )
{
  setupIO();

  lcd128 = initLcd128( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10,  11, 12 ); //Initalize the 128x64 lcd
  
  lcd = initLcd( 4, 20,  0, 1, 13,  3, 4, 5, 6, 7, 8, 9, 10 ); //Initialize the 4x20 lcd

  keypad = initKeypad( 14, 15, 17, 16, 20, 21, 19, 18 );

  setGraphicsMode( lcd128 );

  lcd128ClearGraphics( lcd128 );

  lcd128DrawFilledCircle( lcd128, 20, 20, 15 ); 

  lcd128UpdateScreen( lcd128 );

  lcdClear( lcd );
  lcdPosition( lcd, 0, 0 );
  lcdPrintf( lcd, "Hello, World!" );

  while ( 1 )
  {
    char key = checkKeypad( keypad, 0 );
    if ( key != '\0' )
    {
      printf( "%c\n", key );

      lcdPosition( lcd, 0, 3 );
      
      lcdPrintf( lcd, "%c", key );
    }
  }

  free( lcd128 );
  free( lcd );
  
  return 0;
}


