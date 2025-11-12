
#include "Mazethingie.h"
#include "SaveData.h"

typedef struct {
	int w;
	int h;
} SaveData;

void LoadSettings()
{
	SaveData save;
	save.w = MaxMazeWidth;
	save.h = MaxMazeHeight;
	
	SDFile* fp;
	fp = pd->file->open("settings.dat", kFileReadData);
	if (fp)
	{
		pd->file->read(fp, &save, sizeof(SaveData));
		pd->file->close(fp);
	}

	MazeWidth = save.w;
	MazeHeight = save.h;
	if (MazeWidth > MaxMazeWidth)
		MazeWidth = MaxMazeWidth;
	if (MazeHeight > MaxMazeHeight)
		MazeHeight = MaxMazeHeight;
}

void SaveSettings()
{
	SaveData save;
	save.w = MazeWidth;
	save.h = MazeHeight;
	SDFile* fp;
	fp = pd->file->open("settings.dat", kFileWrite);
	if (fp)
	{
		pd->file->write(fp, &save, sizeof(SaveData));
		pd->file->close(fp);
	}
}
