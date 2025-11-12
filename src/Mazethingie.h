#ifndef MAZETHINGIE_H
#define MAZETHINGIE_H

#include "pd_api.h"

#define FRAMERATE 50

#define GSGame 0
#define GSTitleScreen 1

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 240

#define BoxWidth 10
#define BoxHeight 10

#define MaxMazeWidth ((int)((WINDOW_WIDTH / BoxWidth) -2))
#define MaxMazeHeight ((int)((WINDOW_HEIGHT / BoxHeight) -2))
#define MaxMazeSize (MaxMazeWidth * MaxMazeHeight)

#define PlayerSpeedTickVal 10
#define MenuSpeedTickVal 5

extern LCDFont* MonoFont;
extern int GameState;
extern int MazeWidth, MazeHeight, PlayerPosX, PlayerPosY, Selection , xoffset, yoffset, framecount, GameWon, showfps;
extern int frameUpStart, frameDownStart, frameLeftStart, frameRightStart;
extern uint8_t Maze[MaxMazeSize];
extern PlaydateAPI* pd;
extern PDButtons currButtons, prevButtons;
void setPDPtr(PlaydateAPI* p);
void setupGame();
void terminateGame(void);
int mainLoop(void* ud);

#endif