#include <wiringPi.h>
#include <lcd.h>

#include <stdint.h>
#include <stdio.h>

#include "keypad.h"

#define LCD_RS 11
#define LCD_E  10
#define LCD_D4  0
#define LCD_D5  1
#define LCD_D6  2
#define LCD_D7  3

#define MEMORY_SIZE 0xFFFF

uint8_t memory[ MEMORY_SIZE ] = { 0 };

int lcd;

int main ( int argc, char *argv[] )
{
  wiringPiSetup();
  
  pinMode( 21, OUTPUT );
  
  setupKeypad();

  lcd = lcdInit( 4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0 );

  lcdPosition( lcd, 0, 0 );
  
  lcdPuts( lcd, "Hello, World!" );
  
  lcdPosition( lcd, 0, 1 );
  
  lcdPrintf( lcd, "Memory: %d", sizeof(memory) );
  
  lcdPosition( lcd, 0, 2 );

  while ( 1 )
  {
    char key = getKey();
    if ( key != '\0' )
    {
      lcdPrintf( lcd, "%c", key );
    }
  }
}


