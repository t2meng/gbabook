///////////////////////////////////////////////////////////////
// File:    GBA.h                                            //
// Author:  Benjamin D. Hale AKA WhatZdat D. Pimp            //
// Purpose: Function defs. and Basic Defines                 //
///////////////////////////////////////////////////////////////
//<lcd.h>   variables\functions dealing with the LCD
//<keys.h>  variables\functions dealing with the D-pad and buttons
//<timer.h> variables\functions dealing with timing, waits etc.

// Includes

// Typedefs

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;
typedef signed char		s8;
typedef signed short	s16;
typedef signed long		s32;
typedef s32				bool;

// Defines

#define NULL                     0
#define true                     1
#define false                    0

#define BIT0                     (1)
#define BIT1                     (1<<1)
#define BIT2                     (1<<2)
#define BIT3                     (1<<3)
#define BIT4                     (1<<4)
#define BIT5                     (1<<5)
#define BIT6                     (1<<6)
#define BIT7                     (1<<7)
#define BIT8                     (1<<8)
#define BIT9                     (1<<9)
#define BIT10                    (1<<10)
#define BIT11                    (1<<11)
#define BIT12                    (1<<12)
#define BIT13                    (1<<13)
#define BIT14                    (1<<14)
#define BIT15                    (1<<15)
#define BIT16                    (1<<16)
#define BIT17                    (1<<17)
#define BIT18                    (1<<18)
#define BIT19                    (1<<19)
#define BIT20                    (1<<20)
#define BIT21                    (1<<21)
#define BIT22                    (1<<22)
#define BIT23                    (1<<23)
#define BIT24                    (1<<24)
#define BIT25                    (1<<25)
#define BIT26                    (1<<26)
#define BIT27                    (1<<27)
#define BIT28                    (1<<28)
#define BIT29                    (1<<29)
#define BIT30                    (1<<30)
#define BIT31                    (1<<31)

#define BITS2                    (BIT2 - 1)
#define BITS3                    (BIT3 - 1)
#define BITS4                    (BIT4 - 1)
#define BITS5                    (BIT5 - 1)
#define BITS6                    (BIT6 - 1)
#define BITS7                    (BIT7 - 1)
#define BITS8                    (BIT8 - 1)
#define BITS9                    (BIT9 - 1)
#define BITS10                   (BIT10 - 1)
#define BITS11                   (BIT11 - 1)
#define BITS12                   (BIT12 - 1)
#define BITS13                   (BIT13 - 1)
#define BITS14                   (BIT14 - 1)
#define BITS15                   (BIT15 - 1)
#define BITS16                   (BIT16 - 1)
#define BITS17                   (BIT17 - 1)
#define BITS18                   (BIT18 - 1)
#define BITS19                   (BIT19 - 1)
#define BITS20                   (BIT20 - 1)
#define BITS21                   (BIT21 - 1)
#define BITS22                   (BIT22 - 1)
#define BITS23                   (BIT23 - 1)
#define BITS24                   (BIT24 - 1)
#define BITS25                   (BIT25 - 1)
#define BITS26                   (BIT26 - 1)
#define BITS27                   (BIT27 - 1)
#define BITS28                   (BIT28 - 1)
#define BITS29                   (BIT29 - 1)
#define BITS30                   (BIT30 - 1)
#define BITS31                   (BIT31 - 1)
#define BITS32                   (BITS31 | BIT31)

// Registers
// Variables
#define DMA_16                                                             0x00000000
#define DMA_32                                                             0x04000000
#define DMA_32NOW                          0x80000000| 0x00000000 |DMA_32 
#define DMA_16NOW                          0x80000000| 0x00000000 |DMA_16 

// Function prototypes
void DMA_Copy(u8 channel, void* source, void* dest, u32 WordCount, u32 mode);
