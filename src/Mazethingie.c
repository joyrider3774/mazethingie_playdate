#include "pd_api.h"
#include "Mazethingie.h"
#include "Titlescreen.h"
#include "SaveData.h"
#include "Maze.h"
#include "Player.h"
#include "Game.h"

LCDFont* MonoFont;
int GameState = GSTitleScreen;
int MazeWidth = MaxMazeWidth, MazeHeight = MaxMazeHeight, PlayerPosX = 32, PlayerPosY = 32, Selection = 1, xoffset = 0, yoffset = 0, framecount = 0, GameWon = 0, showfps = 0;
uint8_t Maze[MaxMazeSize];
PlaydateAPI* pd;
PDButtons currButtons, prevButtons;
int frameUpStart = 0, frameDownStart = 0, frameLeftStart = 0, frameRightStart = 0;

void setPDPtr(PlaydateAPI* p) {
    pd = p;
}

void setupGame()
{
	LoadSettings();
	srand(pd->system->getCurrentTimeMilliseconds());
	const char* outErr = NULL;
	MonoFont = pd->graphics->loadFont("fonts/SpaceMono-Bold", &outErr);
	pd->graphics->setFont(MonoFont);
}

void terminateGame(void)
{

}

int mainLoop(void* ud)
{  
	prevButtons = currButtons;
	pd->system->getButtonState(&currButtons, NULL, NULL);
    switch (GameState) 
	{
		case GSTitleScreen:
			TitleScreen();
			break;
		case GSGame:
			Game();
			break;
		default:
			break;
    }
	framecount++;
	if (showfps)
		pd->system->drawFPS(0, 0);
	return 1;
}
