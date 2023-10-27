#include <wiringPi.h>
#include <lcd.h>

#include <stdint.h>
#include <stdio.h>

#define LCD_RS 11
#define LCD_E  10
#define LCD_D4  0
#define LCD_D5  1
#define LCD_D6  2
#define LCD_D7  3

#define ROWS 4
#define COLS 4

#define PAGE_A 16
#define PAGE_B 15

#define MEMORY_SIZE 0xFFFF

uint8_t memory[ MEMORY_SIZE ] = { 0 };

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

int lcd;

void setupKeypad( void );

char getKey( void );

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

