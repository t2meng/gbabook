///////////////////////////////////////////////////////////////
// File:    lcd.h                                            //
// Author:  Benjamin D. Hale AKA WhatZdat D. Pimp            //
// Purpose: Function defs. and Basic Defines for screen     //
///////////////////////////////////////////////////////////////

// Includes

// Defines
#define REG_DISP_CNT             (*(unsigned short*)0x4000000)
#define REG_DISP_STAT            (*(unsigned short*)0x4000004)
#define REG_DISP_MOSAIC          (*(unsigned short*)0x400004C)
#define REG_SCANLINE_COUNT       (*(unsigned short*)0x4000006)
#define SPRITE_PALETTE           ((unsigned short*)0x05000200)
#define SCREEN_PALETTE           ((unsigned short*)0x05000000)
#define VRAM_BASE                ((unsigned short*)0x06000000)

#define SCREEN_WIDTH             240
#define SCREEN_HALF_WIDTH        (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT            160
#define SCREEN_HALF_HEIGHT       (SCREEN_HEIGHT / 2)

#define RGB( r, g, b )           (((b)<<10)+((g)<<5)+(r))
#define RGB_GET_R( c )           (((c)&(31    ))    )
#define RGB_GET_G( c )           (((c)&(31<< 5))>> 5)
#define RGB_GET_B( c )           (((c)&(31<<10))>>10)
#define getRGB(R,G,B,PAL) (B) = ((PAL) >> 10) & 31; \
	                      (G) = ((PAL) >> 5)  & 31; \
                          (R) = (PAL) & 31;


#define MODE_0                   0x0
#define MODE_1                   BIT0
#define MODE_2                   BIT1
#define MODE_3                   BIT0 | BIT1
#define MODE_4                   BIT2
#define MODE_5                   BIT0 | BIT2
#define BACKBUFFER               BIT4
#define H_BLANK_OAM              BIT5 
#define OBJ_MAP_2D               0x0
#define OBJ_MAP_1D               BIT6
#define FORCE_BLANK              BIT7
#define BG0_ENABLE               BIT8
#define BG1_ENABLE               BIT9 
#define BG2_ENABLE               BIT10
#define BG3_ENABLE               BIT11
#define OBJ_ENABLE               BIT12 
#define WIN1_ENABLE              BIT13 
#define WIN2_ENABLE              BIT14
#define WINOBJ_ENABLE            BIT15
#define SetMode(mode)            REG_DISP_CNT = (mode)
//attribute0 #defines
#define ROTATION_FLAG                        0x100
#define SIZE_DOUBLE                 0x200
#define MODE_NORMAL               0x0
#define MODE_TRANSPARENT      0x400
#define MODE_WINDOWED                     0x800
#define MOSAIC                         0x1000
#define COLOR_16                      0x0000
#define COLOR_256                    0x2000
#define SQUARE                         0x0
#define TALL                             0x4000
#define WIDE                             0x8000
//attribute1 #defines
#define ROTDATA(n)                  ((n)<<9)
#define HORIZONTAL_FLIP                      0x1000
#define VERTICAL_FLIP               0x2000
#define SIZE_8                           0x0
#define SIZE_16                         0x4000
#define SIZE_32                         0x8000
#define SIZE_64                         0xC000

//atrribute2 #defines
#define PRIORITY(n)               ((n)<<10)
#define PALETTE(n)                   ((n)<<12)

// Struct
typedef struct tagOAMEntry
{
	unsigned short attribute0;
	unsigned short attribute1;
	unsigned short attribute2;
	unsigned short attribute3;
}OAMEntry, *pOAMEntry;
//variable
OAMEntry sprites[128];
#define OAMDATA ((unsigned short*)0x6014000)

// Function prototypes
void Mode4DisplayImage(unsigned short *pSrc, unsigned short *iSrc);
// My own display functions here
void DoScreenFadeOut();
void DoScreenFadeIn(u16 dPal[]);
void clearPalette();
void BltTo(u16* src,u16* dst,u16 x,u16 y,u16 width,u16 height,bool bTrans);//BitBlit to front/back buffer at mode4,don't use it to draw on any other memory.
void putpixel(int x,int y,u8 col) ;
inline int convert(u16 str,int n);
void DrawText(char*,int,int,u8);
void InitializeSprites();
void CopyOAM();
void DrawTextB(char *str,int x,int y,u8 col);
void setpallete(u8 bGrey, u16 dPal[]);
void setspritepallete(u8 bGrey, u16 dPal[]);
