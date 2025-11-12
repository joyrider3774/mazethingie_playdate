#include <string.h>
#include "Mazethingie.h"
#include "Player.h"
#include "Maze.h"
#include "Game.h"
#include "pd_helperfuncs.h"
#include "SaveData.h"

void Game()
{
	if ((currButtons & kButtonB) && !(prevButtons & kButtonB))
		GameState = GSTitleScreen;
	
	if( GameWon )
		if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
			GameState = GSTitleScreen;

	if (!GameWon)
	{
		if (currButtons & kButtonA)
		{
			
			int regen = 0;
			if (currButtons & kButtonLeft)
			{
				if (!(prevButtons & kButtonLeft))
					frameLeftStart = framecount;
				if ((framecount - frameLeftStart) % MenuSpeedTickVal == 0)
					if (MazeWidth > 10)
					{
						MazeWidth--;
						regen = 1;
					}
			}

			if (currButtons & kButtonRight)
			{
				if (!(prevButtons & kButtonRight))
					frameRightStart = framecount;
				if ((framecount - frameRightStart) % MenuSpeedTickVal == 0)
					if (MazeWidth < MaxMazeWidth)
					{
						MazeWidth++;
						regen = 1;
					}
			}

			if (currButtons & kButtonDown)
			{
				if (!(prevButtons & kButtonDown))
					frameDownStart = framecount;
				if ((framecount - frameDownStart) % MenuSpeedTickVal == 0)
					if (MazeHeight < MaxMazeHeight)
					{
						MazeHeight++;
						regen = 1;
					}
			}

			if (currButtons & kButtonUp)
			{
				if (!(prevButtons & kButtonUp))
					frameUpStart = framecount;
				if ((framecount - frameUpStart) % MenuSpeedTickVal == 0)
					if (MazeHeight > 10)
					{
						MazeHeight--;
						regen = 1;
					}
			}

			if (regen)
			{
				SaveSettings();
				GameWon = 0;
				pd->graphics->clear(kColorBlack);
				GenerateMaze();
				DrawMaze();
				DrawPlayer();
			}
		}
		else
		{
			
			if (currButtons & kButtonRight)
			{
				if (!(prevButtons & kButtonRight))
					frameRightStart = framecount;
				if ((framecount - frameRightStart) % PlayerSpeedTickVal == 0)
					if (!(Maze[(PlayerPosY * MazeWidth) + PlayerPosX] & 2))
					{
						ErasePlayer();
						PlayerPosX++;
						DrawPlayer();
					}
			}

			if (currButtons & kButtonLeft)
			{
				if (!(prevButtons & kButtonLeft))
					frameLeftStart = framecount;
				if ((framecount - frameLeftStart) % PlayerSpeedTickVal == 0)
					if (!(Maze[(PlayerPosY * MazeWidth) + PlayerPosX] & 8))
					{
						ErasePlayer();
						PlayerPosX--;
						DrawPlayer();
					}
			}

			if (currButtons & kButtonUp)
			{
				if(!(prevButtons & kButtonUp))
					frameUpStart = framecount;
			
				if ((framecount - frameUpStart) % PlayerSpeedTickVal == 0)
				{
					if ((PlayerPosX == 0) && (PlayerPosY == 0))
					{
						GameWon = 1;
						int tw = pd->graphics->getTextWidth(MonoFont, "let's try another one", strlen("let's try another one"), kASCIIEncoding, 1);
						int th = pd->graphics->getFontHeight(MonoFont) * 4;
						pd->graphics->fillRect(((WINDOW_WIDTH - tw) >> 1) - 10, ((WINDOW_HEIGHT - th) >> 1) - 10, tw + 10, th + 10, kColorBlack);
						pd->graphics->drawRect(((WINDOW_WIDTH - tw) >> 1) - 10 + 3, ((WINDOW_HEIGHT - th) >> 1) - 10 + 3, tw + 10 - 3, th + 10 - 3, kColorWhite);
						drawTextColor(MonoFont, "Congratulations !!!\nYou solved the maze,\nlet's try another one", strlen("Congratulations !!!\nYou solved the maze,\nlet's try another one"), kASCIIEncoding, ((WINDOW_WIDTH - tw) >> 1) + 5, ((WINDOW_HEIGHT - th) >> 1) + 5, kColorWhite, false);
					}
					else
						if (!(Maze[(PlayerPosY * MazeWidth) + PlayerPosX] & 1))
						{
							ErasePlayer();
							PlayerPosY--;
							DrawPlayer();
						}
				}
			}

			if (currButtons & kButtonDown)
			{
				if (!(prevButtons & kButtonDown))
					frameDownStart = framecount;
				if ((framecount-frameDownStart) % PlayerSpeedTickVal == 0)
					if ((PlayerPosX != MazeWidth - 1) || (PlayerPosY != MazeHeight - 1))
						if (!(Maze[(PlayerPosY * MazeWidth) + PlayerPosX] & 4))
						{
							ErasePlayer();
							PlayerPosY++;
							DrawPlayer();
						}
			}
		}
	}
}