#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

uint8_t  accumlatorRegister;
uint8_t  indexXRegister;
uint8_t  indexYRegister;

uint8_t  stackPointer;
uint8_t  statusRegister;

uint16_t instructionRegister;
uint16_t programCounter;

void resetCpu( void );

void initCpu( void );

void execute( void );

void singleStep( void );

#endif
