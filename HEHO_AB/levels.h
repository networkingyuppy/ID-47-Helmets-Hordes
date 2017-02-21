#ifndef LEVELS_H
#define LEVELS_H

#include "globals.h"

#define FLOORPART_Y                               48

struct FloorParts
{
  int x;
};

FloorParts floorPart[3];

void setFloorPart()
{
  for (byte i = 0; i < 3; i++) floorPart[i].x = 64 * i;
}

void drawFloor()
{
  
  for (byte i = 0; i < 3; i++)
  {
    if (arduboy.everyXFrames(2)) floorPart[i].x --;
    if (floorPart[i].x < -63) floorPart[i].x = 128;
    sprites.drawSelfMasked (floorPart[i].x, FLOORPART_Y, dungeonFloor, 0);
  }
}

void checkCollisions()
{

}

#endif
