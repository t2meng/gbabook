#define __debug__


#include "demo.h"
#include "common.h"
#include "gfx2.h"

#include "gfx/new/cover01.raw.c"
#include "gfx/new/cover02.raw.c"
#include "gfx/new/cover01.pal.c"
#include "gfx/new/cover02.pal.c"

extern const unsigned char bg04_Bitmap[];
extern const unsigned char bg_Palette[];



int Mainmenu()
{
	WaitVSync();
	
	/*
	clearPalette();
	BltTo((u16 *)BG_MENU,VRAM_BASE,0,0,240,160,0);
	DoScreenFadeIn((u16 *)BG_MENU_PAL);
	*/



	u16 *_pal=SCREEN_PALETTE;
	_pal[254] = 0;
	u16 *_vram=(u16*)VRAM_BASE;
	u16 loop;

	//使用第254色为背景黑色
	for(loop=0;loop<19200;loop++) 
		*_vram++ = 254<<8 | 254;

	BltTo((u16 *)bg04_Bitmap,VRAM_BASE,0,(160-120)/2,240,120,0);
	DoScreenFadeIn((u16 *)bg_Palette);

	//使用255号色！！！下面的程序码要修改这个颜色号的值
	DrawText("按Ａ键开始",80,100,255);


	int b=0;

	InitializeSprites();
	while (1) {
		UPDATA_INPUT();
		if(PRESS_ONCE(KEY_A)) {
			return 0;
		}

		b++;
		if(b %50 > 25)
		{
			SCREEN_PALETTE[255] = RGB(0,0,0);
		}
		else
		{
			SCREEN_PALETTE[255] = RGB(0,255,0);
		}


		WaitVSync();
		CopyOAM();
	}
}

void doSplash()
{
	int loop;
	u16* _vram=(u16*) VRAM_BASE;
	clearPalette();
	for(loop=0;loop<19200;loop++) 
	{
		*_vram++=((u16 *)cover01_Bitmap)[loop];
	}

	DoScreenFadeIn((u16 *)cover01_Palette);


	WaitTime(0,900);
	DoScreenFadeOut();
	clearPalette();
	_vram=(u16*)VRAM_BASE;
	for(loop=0;loop<19200;loop++) 
		*_vram++=((u16 *)cover02_Bitmap)[loop];
	DoScreenFadeIn((u16 *)cover02_Palette);


	WaitTime(0,500);
	DoScreenFadeOut(); 
	for(loop=0;loop<19200;loop++)
		*_vram++=0;
} 
void Initgraph()
{
	SetMode(MODE_4|BG2_ENABLE|OBJ_ENABLE|OBJ_MAP_1D);
    int loop=0;
	u16* _pal=(u16*)SCREEN_PALETTE;
	for(;loop<256;loop++) 
		*_pal++=((u16*)bg_Palette)[loop];//pal[loop];
	_pal=(u16*)SPRITE_PALETTE;
	for(loop=0;loop<256;loop++) 
		*_pal++=((u16*)bg_Palette)[loop];//pal[loop];
}
void Playing()
{
}
void option()
{
}


//
//	载入脚本前的动作
//
void startgame(LPGAMEDATA g)
{
	u16 loop;
	WaitVSync();
	InitializeSprites();
	CopyOAM();
	clearPalette();

	//背景使用252号色
	SCREEN_PALETTE[252] = RGB(0,0,0);
	for(loop=0;loop<19200;loop++) 
		VRAM_BASE[loop]=(252 << 8) | 252;

	g->nSaveCount=0;
	g->nPos=0;
	Initgraph();
	//WaitTime(1,0);
}




















