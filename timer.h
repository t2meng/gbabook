///////////////////////////////////////////////////////////////
// File:    timer.h                                          //
// Author:  Benjamin D. Hale AKA WhatZdat D. Pimp            //
// Purpose: Function defs. and Basic Defines for timers etc. //
///////////////////////////////////////////////////////////////

// Includes

// Defines
#define FREQUENCY_0		0x0
#define FREQUENCY_64	BIT0
#define FREQUENCY_256	BIT1
#define FREQUENCY_1024	BIT0 | BIT1

#define TIMER_CASCADE	BIT2
#define TIMER_IRQ		BIT6
#define TIMER_ENABLE	BIT7
#define REG_TM0D       *(volatile unsigned short*)0x4000100
#define REG_TM0CNT     *(volatile unsigned short*)0x4000102
#define REG_TM1D       *(volatile unsigned short*)0x4000104
#define REG_TM1CNT     *(volatile unsigned short*)0x4000106
#define REG_TM2D       *(volatile unsigned short*)0x4000108
#define REG_TM2CNT     *(volatile unsigned short*)0x400010A
#define REG_TM3D       *(volatile unsigned short*)0x400010C
#define REG_TM3CNT     *(volatile unsigned short*)0x400010E



// Function prototypes
void WaitBlanks(int NumBlanks);
void WaitVBlank(void);
void WaitTime(int Seconds, int MSeconds);
void WaitVSync(void);
