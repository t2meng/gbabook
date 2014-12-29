///////////////////////////////////////////////////////////////
// File:    keys.h                                           //
// Author:  Benjamin D. Hale AKA WhatZdat D. Pimp            //
// Purpose: Function defs. and Basic Defines keypad/d-pad    //
///////////////////////////////////////////////////////////////

// Includes

// Defines

#define REG_KEY                  ((volatile unsigned short*)0x4000130)
#define KEY_A_PRESSED            (!((*REG_KEY) & (1<<0)))
#define KEY_B_PRESSED            (!((*REG_KEY) & (1<<1)))
#define KEY_SELECT_PRESSED       (!((*REG_KEY) & (1<<2)))
#define KEY_START_PRESSED        (!((*REG_KEY) & (1<<3)))
#define KEY_RIGHT_PRESSED        (!((*REG_KEY) & (1<<4)))
#define KEY_LEFT_PRESSED         (!((*REG_KEY) & (1<<5)))
#define KEY_UP_PRESSED           (!((*REG_KEY) & (1<<6)))
#define KEY_DOWN_PRESSED         (!((*REG_KEY) & (1<<7)))
#define KEY_R_PRESSED            (!((*REG_KEY) & (1<<8)))
#define KEY_L_PRESSED            (!((*REG_KEY) & (1<<9)))
//////////////////////////////////////////////////////////////////////////
#define KEY_A		1
#define KEY_B		2
#define KEY_SELECT	4
#define KEY_START	8
#define KEY_RIGHT	16
#define KEY_LEFT	32
#define KEY_UP		64
#define KEY_DOWN	128
#define KEY_R		256
#define KEY_L		512

// Variables
/*static */u16 keypadState;
/*static */u16 keyTrig;
/*static */u16 keyCont;

// Function prototypes
#define  UPDATA_INPUT() 	keypadState=	((*(u16*)0x04000130) ^ 0xFFFF); \
                            keyTrig=keypadState&(keypadState^keyCont);      \
                            keyCont=keypadState;                           
#define PRESS_ONCE(k)   (k&keyTrig)

