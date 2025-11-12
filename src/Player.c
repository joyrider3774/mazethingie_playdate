#include "Player.h"
#include "Mazethingie.h"
#include "pd_api.h"
#include "pd_helperfuncs.h"

void DrawPlayer()
{

	pd->graphics->fillRect((xoffset + ((PlayerPosX + 1) * BoxWidth))+1, (yoffset + ((PlayerPosY + 1) * BoxHeight) + 1),
		BoxWidth - 1, BoxHeight - 1, (LCDColor)kColorGrey);
}

void ErasePlayer()
{
	pd->graphics->fillRect((xoffset + ((PlayerPosX + 1) * BoxWidth))+1, (yoffset + ((PlayerPosY + 1) * BoxHeight) + 1),
		BoxWidth - 1, BoxHeight - 1, kColorBlack);
}
