#include "cpu.h"
#include "memory.h"

void initCpu( void )
{
  resetCpu();
}

void resetCpu( void )
{
  uint8_t  accumlatorRegister  = 0;
  uint8_t  indexXRegister      = 0;
  uint8_t  indexYRegister      = 0;

  uint8_t  stackPointer        = 0;
  uint8_t  statusRegister      = 0;

  uint16_t instructionRegister = 0;
  uint16_t programCounter      = 0;
  
  resetRam();
}

void execute( void )
{

}

void singleStep( void )
{

}

