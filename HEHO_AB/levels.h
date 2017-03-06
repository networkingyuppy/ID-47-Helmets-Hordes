#ifndef LEVELS_H
#define LEVELS_H

#include "globals.h"

#define FLOORPART_Y                               48

struct FloorParts
{
  int x;
};

FloorParts floorPart[3];

struct dungeonChains
{
  int x;
  byte y;
};

dungeonChains chain[6];

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

void setChains()
{

  chain[0].x = 128;
  chain[0].y = 0;
  chain[1].x = 144;
  chain[1].y = 0;
  chain[2].x = 144;
  chain[2].y = 16;
}

void drawChains()
{
  for (byte i = 0; i < 3; i++)
  {
    if (arduboy.everyXFrames(1)) chain[i].x -= 2;
    if (chain[i].x < -256) chain[i].x = 128;
    sprites.drawPlusMask (chain[i].x, chain[i].y, dungeonChain_plus_mask, 0);
  }
}

void checkCollisions()
{

}

#endif
