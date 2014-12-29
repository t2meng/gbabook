// Demo.c AGBmain Entry point is contained here (main program loop)
#include <gba.h>
#include "stdlib.h"
#include <lcd.h>
#include <timer.h>
#include <keys.h>
#include "demo.h"
#include "script.h" 
static GAMEDATA curGame;
int AgbMain(void)
{ 
	Initgraph();
	unsigned int nGameState=GAME_SPLASH;
	while(1){
		switch(nGameState){
		case GAME_SPLASH:
			doSplash();
			nGameState=GAME_MAINMENU; break;
		case GAME_MAINMENU: 
			switch(Mainmenu())
			{
			case 0: 
				startgame(&curGame); 
				nGameState=GAME_PLAYING;
				break;
			case 1: 
				nGameState=GAME_LOADGAME;
				break;
			case 2: 
				nGameState=GAME_OPTION;
			} 
			break;
		case GAME_LOADGAME: 
			loadgame(&curGame); 
			nGameState=GAME_MAINMENU;
			break;
		case GAME_OPTION: 
			option();
			nGameState=GAME_MAINMENU; 
			break;
		case GAME_PLAYING: 
			RunScript(curGame.nPos,(unsigned long)(&curGame));
			nGameState=GAME_MAINMENU;
			break;
		}
	}
} 
void loadgame(LPGAMEDATA dd){
	u8 *pSaveMemory = ((u8*)0x0E000000);
	
	// Save the initial data for the fibonai sequence
	pSaveMemory[0] = 1;
	pSaveMemory[1] = 1;
	int i;
	for( i = 2; i < 13; i++)
		pSaveMemory[i] = pSaveMemory[i-1] + pSaveMemory[i-2];
}

//end of entry point


