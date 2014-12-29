//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*                                                                      */
/************************************************************************/
//#include "gfx.h"
#define GAME_QUIT 0
#define GAME_SPLASH 1
#define GAME_MAINMENU 2
#define GAME_LOADGAME 3
#define GAME_OPTION 4
#define GAME_PLAYING 5
typedef struct tagGAMEDATA{
	unsigned char nSaveCount;
	unsigned short nPos;
	unsigned long title;
} GAMEDATA,*LPGAMEDATA;
void doSplash();
void Initgraph();
int Mainmenu();
void startgame(LPGAMEDATA g);
void option();
void Playing();
void loadgame(LPGAMEDATA dd);
