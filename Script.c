//////////////////////////////////////////////////////////////////////////
#include "common.h" 
#include "story.h" 
#include "demo.h"
#include "script.h"

#define TEXE_COLOR  RGB(255*31/255,136*31/255,196*31/255)
#define DLG_COLOR   RGB(0,0,0)

extern const u16 pal[256];
static u32 curScene;
u16 str,_loop,waitcntr;
u32 temp;
#define TEXT_LENGTH_MAX 31
char dtxt1[TEXT_LENGTH_MAX];
char dtxt2[TEXT_LENGTH_MAX];
inline u16 getLen(char* s)
{
	u16 l=0;
	while (*s++) l++;
	l=l>>1;
	return l;
}  
void savedata(u32 title,u16 pos,LPGAMEDATA g);
void showdialog(char* s,u8 textcol,u8 bgcol,u16 sx);
void wait4key();
//////////////////////////////////////////////////////////////////////////
//minigames
//////////////////////////////////////////////////////////////////////////
//funcs
void RunScript(unsigned short curCmd,unsigned long curGamedata){
	u16 r,g,b,rgb;
	u16 cp[256];
	u8 bGrey=false;

	InitializeSprites();
	CopyOAM();
	clearPalette();
	//背景使用252号色
	SCREEN_PALETTE[252] = DLG_COLOR;
	for(_loop=0;_loop<19200;_loop++) 
		VRAM_BASE[_loop]=(252 << 8) | 252;


	u16 p=curCmd;
	u32 cmd;

	while((cmd=story[p++]) != 0)
	{
		switch(cmd)
		{
		case LOADSCENE:
			curScene=story[p++];
			BltTo((u16 *)curScene,VRAM_BASE,0,0,240,120,0);
			break;
		case ENDSCENE:
			curScene=story[p++];
			switch(story[p++])
			{
			case 0: 
				clearPalette();
				break;
			case 1: 
				DoScreenFadeOut();
				break;
			} 
			break;  
		case DIALOG: 
			//字体使用253号色
			//背景使用252号色
			SCREEN_PALETTE[253] = TEXE_COLOR;
			SCREEN_PALETTE[252] = DLG_COLOR;
			showdialog((char *)stringtable[story[p++]],253,252,20);
			break;		
		case BEGINSCENE:
			clearPalette();
			
			//背景使用252号色
			SCREEN_PALETTE[252] = DLG_COLOR;
			for(_loop=0;_loop<19200;_loop++) 
				VRAM_BASE[_loop]=(252 << 8) | 252;

			BltTo((u16 *)curScene,VRAM_BASE,0,0,240,120,0);
			switch(story[p++])
			{
			case 0: 
				setpallete(bGrey,(u16 *)bg_Palette);
				break;
			case 1:
				if(bGrey)
				{
					for(_loop=0;_loop<256;_loop++)
					{
						getRGB(r,g,b,bg_Palette[_loop]);
						rgb=(r+g+b)/3;
						cp[_loop]=RGB(rgb,rgb,rgb);
					}
					DoScreenFadeIn(cp);
					break;
				}
				else
				{
					DoScreenFadeIn((u16 *)bg_Palette);
				}
			} 
			break;
		case SHOWTITLE:
			str=story[p++]; clearPalette();

			//背景使用252号色
			SCREEN_PALETTE[252] = DLG_COLOR;
			for(_loop=0;_loop<19200;_loop++) 
				VRAM_BASE[_loop]=(252 << 8) | 252;

			DrawText((char *)stringtable[str],120-8*getLen((char *)stringtable[str]),75,255);

			DoScreenFadeIn((u16 *)bg_Palette); 
			temp=0;
w:		    UPDATA_INPUT();
			if(PRESS_ONCE(KEY_A)||temp++>200000)
			{
				DoScreenFadeOut(); 
				break;
			}
			goto w;
		case WAIT:
			WaitTime(0,story[p++]);
			break;
		default:
			DrawText("未知指令",120,80,50);
			savelong(0,p);
			break;
		} 
	}
}

 
void showdialog(char* s,u8 textcol,u8 bgcol,u16 sx)
{
	char* pos=s;
	const int y1 = 127;
	const int y2 = 142;

	u16 _loop;
	for(_loop=240*120/2;_loop<19200;_loop++) 
		VRAM_BASE[_loop]= (bgcol << 8) | bgcol;

	//分几次显示，直到显示完毕
	while(getLen(pos)>TEXT_LENGTH_MAX-1)
	{
		for(_loop=240*120/2;_loop<19200;_loop++) 
			VRAM_BASE[_loop]=(bgcol << 8) | bgcol;


		for(_loop=0;_loop<TEXT_LENGTH_MAX-1;_loop++) 
			dtxt1[_loop]=*pos++; 
		dtxt1[TEXT_LENGTH_MAX-1]=0;
		
		for(_loop=0;_loop<TEXT_LENGTH_MAX-1;_loop++) 
			dtxt2[_loop]=*pos++; 
		dtxt2[TEXT_LENGTH_MAX-1]=0;
		
		DrawTextB(dtxt1,sx,y1,textcol);
		DrawTextB(dtxt2,sx,y2,textcol);

		wait4key();
	} 

	if(getLen(pos)>TEXT_LENGTH_MAX/2)
	{
		for(_loop=240*120/2;_loop<19200;_loop++) 
			VRAM_BASE[_loop]=(bgcol << 8) | bgcol;
	
		for(_loop=0;_loop<TEXT_LENGTH_MAX-1;_loop++) 
			dtxt1[_loop]=*pos++; 
		dtxt1[TEXT_LENGTH_MAX-1]=0;

		for(_loop=0;_loop<TEXT_LENGTH_MAX-1;_loop++) 
			dtxt2[_loop]=*pos++;
		dtxt2[TEXT_LENGTH_MAX-1]=0;
		DrawTextB(dtxt1,sx,y1,textcol);
		DrawTextB(dtxt2,sx,y2,textcol);
		wait4key();
	}
	else
	{
		for(_loop=240*120/2;_loop<19200;_loop++) 
			VRAM_BASE[_loop]=(bgcol << 8) | bgcol;		
		for(_loop=0;_loop<TEXT_LENGTH_MAX-1;_loop++) 
			dtxt1[_loop]=*pos++; 
		dtxt1[TEXT_LENGTH_MAX-1]=0;
		DrawTextB(dtxt1,sx,y1,textcol);
		wait4key();		  
	}
} 



void wait4key()
{ 
	UPDATA_INPUT();
	while(!PRESS_ONCE(KEY_A))
	{
		WaitVSync();
		UPDATA_INPUT();
	}
}


void savedata(u32 title,u16 pos,LPGAMEDATA g)
{
	g->nSaveCount++;
	g->nPos=pos;
	g->title=title;
	savebyte(0,g->nSaveCount);
	saveshort(1,g->nPos);
	savelong(3,g->title);
	savelong(7,(unsigned long)g);
}
