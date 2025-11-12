#include <string.h>
#include "Mazethingie.h"
#include "SaveData.h"
#include "Maze.h"
#include "Player.h"
#include "Titlescreen.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"

void TitleScreen()
{
	int MenuXPos = 100;
	int MenuYPos = 60;
	pd->graphics->clear(kColorBlack);
	drawTextColor(MonoFont, "MAZE THINGIE", strlen("MAZE THINGIE"),kASCIIEncoding, 130, 0, kColorWhite, false);
	if (Selection == 1)
	{
		drawTextColor(MonoFont,"Play", strlen("Play"), kASCIIEncoding, MenuXPos, MenuYPos, kColorWhite, false);
	}
	else
	{
		
		drawTextColor(MonoFont, "Play", strlen("Play"), kASCIIEncoding, MenuXPos, MenuYPos, (LCDColor)kColorGrey, false);
	}

	char *Text;
	pd->system->formatString(&Text, "Maze Width: %d", MazeWidth);
	if (Selection == 2)
	{
		drawTextColor(MonoFont, Text, strlen(Text), kASCIIEncoding, MenuXPos, MenuYPos + 35, kColorWhite, false);
	}
	else
	{
		drawTextColor(MonoFont, Text, strlen(Text), kASCIIEncoding, MenuXPos, MenuYPos + 35, (LCDColor)kColorGrey, false);
	}
	pd->system->realloc(Text, 0);


	pd->system->formatString(&Text, "Maze Height: %d", MazeHeight);
	if (Selection == 3)
	{
		drawTextColor(MonoFont, Text, strlen(Text), kASCIIEncoding, MenuXPos, MenuYPos + 70, kColorWhite, false);
	}
	else
	{
		drawTextColor(MonoFont, Text, strlen(Text), kASCIIEncoding, MenuXPos, MenuYPos + 70, (LCDColor)kColorGrey, false);
	}
	pd->system->realloc(Text, 0);

	
	drawTextColor(MonoFont, "Created by Willems Davy - 2025", strlen("Created by\nWillems Davy - 2024"), kASCIIEncoding, 15, 200, kColorWhite, false);

	if (currButtons & kButtonUp)
	{
		if (!(prevButtons & kButtonUp))
			frameUpStart = framecount;
		if ((framecount-frameUpStart) % MenuSpeedTickVal == 0)
			if (Selection > 1)
				Selection--;
	}

	if (currButtons & kButtonDown)
	{
		if (!(prevButtons & kButtonDown))
			frameDownStart = framecount;
		if ((framecount - frameDownStart) % MenuSpeedTickVal == 0)
			if (Selection < 3)
				Selection++;
	}

	if ((currButtons & kButtonA) && !(prevButtons & kButtonA))
	{
		SaveSettings();
		GenerateMaze();
		pd->graphics->clear(kColorBlack);
		GameWon = 0;
		DrawMaze();
		DrawPlayer();
		GameState = GSGame;
	}

	if (Selection == 2)
	{
		if(currButtons & kButtonRight)
		{
			if (!(prevButtons & kButtonRight))
				frameRightStart = framecount;
			if ((framecount - frameRightStart) % MenuSpeedTickVal == 0)
				if (MazeWidth < MaxMazeWidth)
				{
					MazeWidth++;
					SaveSettings();
				}
		}

		if (currButtons & kButtonLeft)
		{
			if (!(prevButtons & kButtonLeft))
				frameLeftStart = framecount;
			if ((framecount - frameLeftStart) % MenuSpeedTickVal == 0)
				if (MazeWidth > 10)
				{
					MazeWidth--;
					SaveSettings();
				}
		}

	}

	if (Selection == 3)
	{
		if (currButtons & kButtonRight)
		{
			if (!(prevButtons & kButtonRight))
				frameRightStart = framecount;
			if ((framecount - frameRightStart) % MenuSpeedTickVal == 0)
				if (MazeHeight < MaxMazeHeight)
				{
					MazeHeight++;
					SaveSettings();
				}
		}

		if (currButtons & kButtonLeft)
		{
			if (!(prevButtons & kButtonLeft))
				frameLeftStart = framecount;
			if ((framecount - frameLeftStart) % MenuSpeedTickVal == 0)
				if (MazeHeight > 10)
				{
					MazeHeight--;
					SaveSettings();
				}
		}

	}
}