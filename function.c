//////////////////////////////////////////////////////////////
// File: function.c                                         //
// Author: Benjamin D. Hale AKA WhatZdat D. Pimp            //
// Purpose: Generic functions for commonly used tasks.      //
//////////////////////////////////////////////////////////////
 
// Includes/Defines
 
#include "malloc.h"
#include "stdlib.h"
#include "string.h"
//#include <gba.h>
//#include <lcd.h>
//#include <keys.h>
//#include <timer.h>
#include "common.h"
#include "gfx\gbazk.h" 


//add
#include "song-12-gb2312.h"
#define PANEL_W 320
//字库放置的存储器地址
#define HZLIBADR   song2312_1612







// Variables
  extern u16 pal[256];
int Seconds, MSeconds, NumBlanks, i;
unsigned short  *pDst, *pSrc, *iDst, iSrc;

// Functions

void Mode4DisplayImage(unsigned short *pSrc, unsigned short *iSrc)
{
	int i;
	pDst = (unsigned short*)SCREEN_PALETTE;
	iDst = (unsigned short*)VRAM_BASE;
		for(i = 0; i < 256; i++)
			pDst[i] = pSrc[i];

        DMA_Copy(3,iSrc,iDst,192,DMA_16NOW);
	//SetMode(MODE_4 | BG2_ENABLE);
}
 
void WaitBlanks(int NumBlanks)
{
	int i = 0;

	while(i < NumBlanks)
	{
		WaitVSync();
		i++;
	}
}

void WaitTime(int Seconds, int MSeconds)
{
	REG_TM2CNT = FREQUENCY_256 | TIMER_ENABLE;
	REG_TM3CNT = TIMER_CASCADE | TIMER_ENABLE;

	REG_TM2D = 0;
	REG_TM3D = 0;

	while(REG_TM3D < Seconds)
	{
	}

	REG_TM2D = 0;

	while(REG_TM2D / (65536/1000) < MSeconds)
	{
	}

	REG_TM2CNT = 0;
	REG_TM3CNT = 0;
	
    REG_TM2D = 0;
	REG_TM3D = 0;
}

void WaitVBlank(void)
{
	while(*((volatile unsigned short*)0x04000004) & (1<<0));
}

void WaitVSync(void)
{
	while(*((volatile unsigned short*)0x04000004) & (1<<0));
	while(!((*((volatile unsigned short*)0x04000004) & (1<<0))));
}
void DoScreenFadeOut(){
#ifdef __debug__ 
    return;
#endif
	//u16* _pal=malloc(256*sizeof(u16));
	u16* _pal=SCREEN_PALETTE;
	int l,loop; 
	u16 r,g,b;
	for(loop=0;loop<32;loop++){
	//	WaitVSync();
	//	WaitVSync();
	//	WaitVSync();
	//	WaitVSync();
		WaitVSync();
		for(l=0;l<256;l++){
			   getRGB(r,g,b,_pal[l]);
			   if(r>0) r--;
			   if(g>0) g--;
			   if(b>0) b--;
			   _pal[l]=(u16)RGB(r,g,b);
		}
	}
}
void DoScreenFadeIn(u16* dPal){
	u16* _pal=(u16*)SCREEN_PALETTE;
	int l,loop;
	u16 r,g,b,r1,g1,b1;
	for(loop=0;loop<32;loop++){
		//WaitVSync();
	//	WaitVSync();
	//	WaitVSync();
	//	WaitVSync();
		WaitVSync();
		for(l=0;l<256;l++){
			getRGB(r,g,b,_pal[l]);
			getRGB(r1,g1,b1,dPal[l]);
			if(r<r1) r++;
			if(g<g1) g++;
			if(b<b1) b++;
			_pal[l]=(u16)RGB(r,g,b);
		}
	}
}
void putpixel(int x,int y,u8 col) 
{ 
	u16 *tc; 
	tc=VRAM_BASE+(y)*120+(x>>1); 
	if(x&1) *tc=((*tc&255)+(col<<8)); 
	else 
		*tc=(*tc&65280)+col; 
} 
inline int convert(u16 str,int n) 
{ 
	return((str>>n)&0x1); 
}


//
//输出16*12点阵图形，同样可以用来输出汉字
//16*12
//
inline void print_song2312(char *word,int pixel_x,int pixel_y,u8 color)
{
 int bit_long = 8;
 int num_in_line = 2;
 int line = 12;
 int i=0,j=0,k=0;
 int value=0; 
 
 for(k=0;k<line;k++)
  {
     for(j=0;j<num_in_line;j++)
         {
             value = (word+k*num_in_line)[j];
        for(i=0; i<bit_long; i++)
            {
               if (value & 0x80)
                  putpixel(pixel_x+j*8+i,pixel_y+k,color);
                                  
               value = value << 1; 
            }
         }
  }


}

//
//去字库中找到汉字点阵数据，读出来，然后调用DisplayFont显示点阵数据
//
inline void ChineseOut(short x,short y,char *buf,u8 color)
{

	unsigned char CH,CL;
	int		Pos;
	char * pHZPos=NULL;
	char     pData[32];
	int offset=2;
	short nX,nY;
	int n_cp;
	
	
	nX=x;nY=y;	
	while(*buf)
	{

		CH = buf[0];//对应区编码
		CL = buf[1];//对应区内编码
		if (CH >= 0xA0 && CH < 0xF8 && CL >= 0xA0 && CL < 0xFF) 
		{
			if(CH>0xA9)//特别：第55区仅含有89个汉字，除此之外，其他区均为94个汉字。24为每个字所占字节数
          		Pos = ((CH - 0xA7) * 94 + (CL - 0xA1)) * 24;
          	else
          		Pos = ((CH - 0xA1) * 94 + (CL - 0xA1)) * 24;
	
          	pHZPos = (char *)HZLIBADR + Pos; 
			
			for(n_cp = 0; n_cp < 32; n_cp++)
			{
				pData[n_cp]=((char *)pHZPos)[n_cp];
			}
			
			//DisplayFont(nX,nY,pData,color);
			print_song2312(pData,nX,nY,color);
			buf +=offset;
			
		}

		nX += 13;
		if(nX > PANEL_W - 64)
		{	nX =0;
			nY += 12;
		}
	}
}

//
//	文本函数
//
void DrawText(char *str,int x,int y,u8 col)
{
	unsigned char CH,CL;
	int		Pos;
	char * pHZPos=NULL;
	char     pData[32];
	int offset=2;
	short nX,nY;
	int n_cp;
	
	nX=x;nY=y;	
	while(*str)
	{

		CH = str[0];//对应区编码
		CL = str[1];//对应区内编码
		if (CH >= 0xA0 && CH < 0xF8 && CL >= 0xA0 && CL < 0xFF) 
		{
			if(CH>0xA9)//特别：第55区仅含有89个汉字，除此之外，其他区均为94个汉字。24为每个字所占字节数
          		Pos = ((CH - 0xA7) * 94 + (CL - 0xA1)) * 24;
          	else
          		Pos = ((CH - 0xA1) * 94 + (CL - 0xA1)) * 24;
	
          	pHZPos = (char *)HZLIBADR + Pos; 
			
			for(n_cp = 0; n_cp < 32; n_cp++)
			{
				pData[n_cp]=((char *)pHZPos)[n_cp];
			}
			
			print_song2312(pData,nX,nY,col);
			str +=offset;
			
		}

		nX += 13;
		if(nX > PANEL_W - 64)
		{	nX =0;
			nY += 12;
		}
	}
}

//
//	带WaitTime版本的文本函数
//
void DrawTextB(char *str,int x,int y,u8 col)
{
	unsigned char CH,CL;
	int		Pos;
	char * pHZPos=NULL;
	char     pData[32];
	int offset=2;
	short nX,nY;
	int n_cp;
	
	nX=x;nY=y;	
	while(*str)
	{

		CH = str[0];//对应区编码
		CL = str[1];//对应区内编码
		if (CH >= 0xA0 && CH < 0xF8 && CL >= 0xA0 && CL < 0xFF) 
		{
			if(CH>0xA9)//特别：第55区仅含有89个汉字，除此之外，其他区均为94个汉字。24为每个字所占字节数
          		Pos = ((CH - 0xA7) * 94 + (CL - 0xA1)) * 24;
          	else
          		Pos = ((CH - 0xA1) * 94 + (CL - 0xA1)) * 24;
	
          	pHZPos = (char *)HZLIBADR + Pos; 
			
			for(n_cp = 0; n_cp < 32; n_cp++)
			{
				pData[n_cp]=((char *)pHZPos)[n_cp];
			}
			
			print_song2312(pData,nX,nY,col);
			str +=offset;
			
		}

		nX += 13;
		if(nX > PANEL_W - 64)
		{	nX =0;
			nY += 12;
		}

		WaitTime(0,50);
	}
}

/*
void DrawText(char *str,int x,int y,u8 col)
{
	int i,j,k,n;
	// 字符所在区,位,实际位置
	int qu, wei, location;

	while(*str)
	{
		// 得到单字的区位码
		qu = *(str++)-0xa0; 
		wei = *(str++)-0xa0; 
		location = qu*94+wei; 
		
		// 在字库里查找
		for(n=0 ;n<NUM_STR;n++)
		{
			if(ZKQW[n]==location)
			{
				// 根据字符数据画出字符
				for(i=0;i<12;i++)
					for(j=0;j<2;j++)
						for(k=0;k<8;k++) 
							if(convert(ZKDATA[n*24+i*2+j],7-k))
								putpixel(x+j*8+k,y+i,col); 
							x+=12; 
			}
		}
	}
}

void DrawTextB(char *str,int x,int y,u8 col)
{
	int i,j,k,n;
	// 字符所在区,位,实际位置
	int qu, wei, location;
	
	while(*str)
	{
		// 得到单字的区位码
		qu = *(str++)-0xa0; 
		wei = *(str++)-0xa0; 
		location = qu*94+wei; 
		
		// 在字库里查找
		for(n=0 ;n<NUM_STR;n++)
		{
			if(ZKQW[n]==location)
			{
				// 根据字符数据画出字符
				for(i=0;i<12;i++)
					for(j=0;j<2;j++)
						for(k=0;k<8;k++) 
							if(convert(ZKDATA[n*24+i*2+j],7-k))
								putpixel(x+j*8+k,y+i,col); 
							x+=12; 
			}
		}
		WaitTime(0,50);
	}
} 
*/

void clearPalette(){
	u16* _pal=(u16*) SCREEN_PALETTE;
	//WaitVSync();
	int loop;
	for(loop=0;loop<256;loop++) *_pal++=0;
}

//
//  BltTo
//	复制图片到显存（源，目标，位置，大小，是否使用透明色）
//  透明色为第一像素
//
void BltTo(u16* src,u16* dst,u16 x,u16 y,u16 width,u16 height,bool bTrans)  
{
	if(!src) 
		return;
	u16 w,h;
	u16* _vram=dst;
	width=width>>1;
	x=x>>1;
	if(width+x<120) 
		w=width ;
	else 
		w=120-x;

	if(height+y<160) 
		h=height ;
	else 
		h=160-y;
	
	u16 keycol=src[0]>>8;
	//u16 keycol2=keycol1<<8;
	u16 x1,y1,i,j;

	if(bTrans)
	{
		for(y1=0;y1<h;y1++)
		{
			for(x1=0;x1<w;x1++)
			{
				i=y1*width+x1;
				j=(y1+y)*120+x1+x;
				if(src[i]>>8!=keycol) 
					_vram[j]=(_vram[j]&0xff)|(src[i]&0xff00);
				if((src[i]&0xff)!=keycol) 
					_vram[j]=(_vram[j]&0xff00)|(src[i]&0xff);
			}
		}
	}
	else
	{
		for(y1=0;y1<h;y1++)
		{
			for(x1=0;x1<w;x1++)
				_vram[(y1+y)*120+x1+x]=src[y1*width+x1];
	//	DMA_Copy(3,src+y1*width+x1,_vram+(y1+y)*120+x1+x,2,DMA_16NOW);
		}
	}
}


void DMA_Copy(u8 channel, void* source, void* dest, u32 WordCount, u32 mode)
{	
	switch (channel)	
	{	
	case 0: 
		*(u32*)0x40000B0= (u32)source;	
		*(u32*)0x40000B4= (u32)dest;                                            	
		*(u32*)0x40000B8= WordCount | mode;	
		break;		
	case 1:		
		*(u32*)0x40000BC = (u32)source;		
		*(u32*)0x40000C0 = (u32)dest;		
		*(u32*)0x40000C4 = WordCount | mode;		
		break;		
	case 2:		
		*(u32*)0x40000C8 = (u32)source;	
		*(u32*)0x40000CC = (u32)dest;		
		*(u32*)0x40000D0 = WordCount | mode;		
		break;				
	case 3:	
		*(u32*)0x40000D4 = (u32)source;		
		*(u32*)0x40000D8 = (u32)dest;		
		*(u32*)0x40000DC = WordCount | mode;		
		break;						
	}	
}
void InitializeSprites(){	
	u16 loop;	
	for(loop = 0; loop < 128; loop++){		
		sprites[loop].attribute0 = 160;  //y to > 159		
		sprites[loop].attribute1 = 240;  //x to > 239		
	}	
}
void CopyOAM(){	
	u16 loop;	
	u16* temp;	
	u16* _OAM = (u16*)0x7000000;	
	temp = (u16*)sprites;	
	for(loop = 0; loop < 128*4; loop++)		
	{		
		_OAM[loop] = temp[loop];		
	}	
}
void setpallete(u8 bGrey, u16 dPal[]){
	u16 loop;
	u16 r,g,b,rgb;
	if(!bGrey){
	for(loop=0;loop<256;loop++)	SCREEN_PALETTE[loop]=dPal[loop];
	}else{
		for(loop=0;loop<256;loop++) {
			getRGB(r,g,b,dPal[loop]);
			rgb=(r+g+b)/3;
			SCREEN_PALETTE[loop]=RGB(rgb,rgb,rgb);
		}
	}
}

void setspritepallete(u8 bGrey, u16 dPal[]){
	u16 loop;
	u16 r,g,b,rgb;
	if(!bGrey){
	for(loop=0;loop<256;loop++)	SPRITE_PALETTE[loop]=dPal[loop];
	}else{
		for(loop=0;loop<256;loop++) {
			getRGB(r,g,b,dPal[loop]);
			rgb=(r+g+b)/3;
			SPRITE_PALETTE[loop]=RGB(rgb,rgb,rgb);
		}
	}
}
