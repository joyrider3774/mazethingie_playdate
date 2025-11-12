#include <string.h>
#include "Mazethingie.h"
#include "pd_api.h"

void DrawMaze()
{

    int X, Y, I;
    //clear_screen (color_red);
    for (Y = 0; Y < MazeHeight; Y++)
        for (X = 0; X < MazeWidth; X++)
        {
            I = (Y * MazeWidth) + X;
            //north wall
            if (Maze[I] & 1)
            {
                pd->graphics->drawLine(xoffset + (X + 1) * BoxWidth, yoffset + (Y + 1) * BoxHeight, xoffset + (X + 2) * BoxWidth - 1, yoffset + (Y + 1) * BoxHeight, 1, kColorWhite);
            }

            //east wall
            if (Maze[I] & 2)
            {
                pd->graphics->drawLine(xoffset + (X + 2) * BoxWidth, yoffset + (Y + 1) * BoxHeight, xoffset + (X + 2) * BoxWidth, yoffset + (Y + 2) * BoxHeight, 1, kColorWhite);
            }

            //south wall
            if (Maze[I] & 4)
            {
                pd->graphics->drawLine(xoffset + (X + 1) * BoxWidth, yoffset + (Y + 2) * BoxHeight, xoffset + (X + 2) * BoxWidth - 1, yoffset + (Y + 2) * BoxHeight, 1, kColorWhite);
            }

            //west wall
            if (Maze[I] & 8)
            {
                pd->graphics->drawLine(xoffset + (X + 1) * BoxWidth, yoffset + (Y + 1) * BoxHeight, xoffset + (X + 1) * BoxWidth, yoffset + (Y + 2) * BoxHeight, 1, kColorWhite);
            }
        }
}

void GenerateMaze()
{
    srand(framecount + MazeWidth + MazeHeight);
    uint16_t neighbours[4];
    uint16_t cellStack[MaxMazeSize];
    uint16_t cc = 0;
    uint16_t currentPoint = 0;
    uint16_t visitedRooms = 1;
    uint16_t tmp2;
    uint16_t selectedNeighbour;
    uint16_t rnd;

    //intial all walls value in every room we will remove bits of this value to remove walls
    memset(Maze, 0xfu, (size_t)(MaxMazeSize));

    while (visitedRooms != MazeHeight * MazeWidth)
    {
        uint16_t neighboursFound = 0;
        uint16_t lookUpX = currentPoint % MazeWidth;
        uint16_t lookUpY = currentPoint / MazeWidth;
        uint16_t tmp = currentPoint + 1;
        //tile has neighbour to the right which we did not handle yet
        if ((lookUpX + 1 < MazeWidth) && (Maze[tmp] == 0xfu))
            neighbours[neighboursFound++] = tmp;

        tmp = currentPoint - 1;
        //tile has neighbour to the left which we did not handle yet
        if ((lookUpX > 0) && (Maze[tmp] == 0xfu))
            neighbours[neighboursFound++] = tmp;

        tmp = currentPoint - MazeWidth;
        //tile has neighbour the north which we did not handle yet
        if ((lookUpY > 0) && (Maze[tmp] == 0xfu))
            neighbours[neighboursFound++] = tmp;

        tmp = currentPoint + MazeWidth;
        //tile has neighbour the south which we did not handle yet
        if ((lookUpY + 1 < MazeHeight) && (Maze[tmp] == 0xfu))
            neighbours[neighboursFound++] = tmp;

        switch (neighboursFound)
        {
        case 0:
            currentPoint = cellStack[--cc];
            continue;
            break;
        default:
            rnd = (uint16_t)(rand() % neighboursFound);
            break;
        }
        selectedNeighbour = neighbours[rnd];
        tmp = (selectedNeighbour % MazeWidth);
        //tile has neighbour to the east
        if (tmp > lookUpX)
        {
            //remove west wall neighbour
            Maze[selectedNeighbour] &= ~(8);
            //remove east wall tile
            Maze[currentPoint] &= ~(2);
        }
        else // tile has neighbour to the west
        {
            if (tmp < lookUpX)
            {
                //remove east wall neighbour
                Maze[selectedNeighbour] &= ~(2);
                //remove west wall tile
                Maze[currentPoint] &= ~(8);
            }
            else // tile has neighbour to the north
            {
                tmp2 = selectedNeighbour / MazeWidth;
                if (tmp2 < lookUpY)
                {
                    //remove south wall neighbour
                    Maze[selectedNeighbour] &= ~(4);
                    //remove north wall tile
                    Maze[currentPoint] &= ~(1);
                }
                else // tile has neighbour to the south
                {
                    if (tmp2 > lookUpY)
                    {
                        //remove north wall neighbour
                        Maze[selectedNeighbour] &= ~(1);
                        //remove south wall tile
                        Maze[currentPoint] &= ~(4);
                    }
                }
            }
        }

        //add tile to the cellstack
        if (neighboursFound > 1)
        {
            cellStack[cc++] = currentPoint;
        }
        //set tile to the neighbour   
        currentPoint = selectedNeighbour;
        visitedRooms++;
    }
    Maze[0] &= ~(1);
    Maze[(MazeWidth) * (MazeHeight)-1] &= ~(4);
    PlayerPosX = MazeWidth - 1;
    PlayerPosY = MazeHeight - 1;
    xoffset = (((WINDOW_WIDTH / BoxWidth) - (MazeWidth + 2)) * BoxWidth) >> 1;
    yoffset = (((WINDOW_HEIGHT / BoxHeight) - (MazeHeight + 2)) * BoxHeight) >> 1;
}
