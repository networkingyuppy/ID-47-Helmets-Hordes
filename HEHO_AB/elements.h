#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"

#define FLOORPART_Y                                       48
#define FLOORWEED_Y                                       39
#define TORCHHANDLE_Y                                     20
#define TORCHFLAME_Y                                      4
#define WINDOW_Y                                          5

byte flameFrame = 0;

const unsigned char PROGMEM chainSetup[][6][3] =
{
  { {128, 0, false}, {128, 16, false}, {144, 0, true}, {144, 16, false}, {160, 0, true}, {160, 16, true} },
  { {128, 0, true}, {128, 16, true}, {144, 0, true}, {144, 16, false}, {160, 0, false}, {160, 16, false} },
  { {128, 0, true}, {128, 16, true}, {144, 0, false}, {144, 16, false}, {160, 0, true}, {160, 16, false} },
  { {128, 0, true}, {128, 16, false}, {144, 0, true}, {144, 16, false}, {160, 0, true}, {160, 16, true} },
  { {128, 0, false}, {128, 16, false}, {144, 0, true}, {144, 8, true}, {160, 0, true}, {160, 16, true} },
  { {128, 0, true}, {128, 8, true}, {144, 0, true}, {144, 16, false}, {160, 0, true}, {160, 16, true} },
  { {128, 0, true}, {128, 16, false}, {144, 0, true}, {144, 8, true}, {160, 0, false}, {160, 16, false} },
  { {128, 0, true}, {128, 8, true}, {144, 0, true}, {144, 16, true}, {160, 0, false}, {160, 16, false} },
};

const unsigned char PROGMEM brickSetup[][4] =
{
  {3, 2, 0, 1}, {2, 1, 0, 3}, {0, 3, 2, 3}, {0, 3, 3, 0}, {2, 0, 0, 1}, {0, 3, 1, 2}, {0, 1, 0, 2}, {2, 3, 0, 1}, {0, 3, 0, 2}, {0, 2, 2, 1}, {0, 1, 0, 3}, {2, 1, 0, 2}, {0, 2, 1, 0}, {0, 1, 3, 2}, {0, 3, 2, 1}, {2, 0, 0, 3}
};


// create all elements
//////////////////////

struct BackGroundWall
{
  boolean isVisible;
};

BackGroundWall torchHandles[3];
BackGroundWall torchFlames[3];
BackGroundWall window[3];

struct BrickParts
{
  byte y;
  byte type;
};

BrickParts bricks[12];

struct BackgroundParts
{
  int x;
};

BackgroundParts floorPart[3];
BackgroundParts floorWeed;
BackgroundParts wallPart[3];

struct ForGroundStuff
{
  int x;
  byte y;
  boolean isVisible;
};

ForGroundStuff chain[6];


// Set all elements
///////////////////
void setFloorPart()
{
  for (byte i = 0; i < 3; i++) floorPart[i].x = 64 * i;
}


void setFLoorWeed()
{
  floorWeed.x = 64;
}


void setChains()
{
  byte chainSet = random(8);
  for (byte i = 0; i < 6; i++)
  {
    chain[i].x = pgm_read_byte(&chainSetup[chainSet][i][0]);
    chain[i].y = pgm_read_byte(&chainSetup[chainSet][i][1]);
    chain[i].isVisible = pgm_read_byte(&chainSetup[chainSet][i][2]);
  }
}


boolean windowOrTorch()
{
  switch (random(3))
  {
    case 0: case 1:
      return true;
      break;
    case 2:
      return false;
      break;
  }
}

void setWallParts()
{
  for (byte i = 0; i < 3; i++)
  {
    wallPart[i].x = i * 80;

    bricks[(i * 4)].y = 0;
    bricks[(i * 4) + 1].y = 16;
    bricks[(i * 4) + 2].y = 0;
    bricks[(i * 4) + 3].y = 16;
    byte brickSet = random(16);
    for (byte k = 0; k < 4; k++)
    {
      bricks[k + (4 * i)].type = pgm_read_byte(&brickSetup[brickSet][k]);
    }
    window[i].isVisible = windowOrTorch();
    torchHandles[i].isVisible = !window[i].isVisible;
    torchFlames[i].isVisible = torchHandles[i].isVisible;
  }
}



// Update all elementes
///////////////////////
void updateWallParts()
{
  if (arduboy.everyXFrames(4)) flameFrame = (++flameFrame) % 4;
  if (arduboy.everyXFrames(3))
  {
    for (byte i = 0; i < 3; i++)
    {
      wallPart[i].x--;
      if (wallPart[i].x < -79)
      {
        wallPart[i].x = 160;
        window[i].isVisible = windowOrTorch();
        torchHandles[i].isVisible = !window[i].isVisible;
        torchFlames[i].isVisible = torchHandles[i].isVisible;
      }
    }
  }
}


// Draw all elementes
/////////////////////
void drawFloorPart()
{
  for (byte i = 0; i < 3; i++)
  {
    if (arduboy.everyXFrames(2)) floorPart[i].x--;
    if (floorPart[i].x < -63) floorPart[i].x = 128;
    sprites.drawSelfMasked (floorPart[i].x, FLOORPART_Y, dungeonFloor, 0);
  }
}

void drawFloorWeed()
{
  if (arduboy.everyXFrames(2)) floorWeed.x--;
  if (floorWeed.x < -512) floorWeed.x = 128;
  sprites.drawPlusMask (floorWeed.x, FLOORWEED_Y, monsterWeed_plus_mask, 0);
  sprites.drawErase (floorWeed.x, FLOORWEED_Y + 9, weedMask, 0);
}


void drawChains()
{
  for (byte i = 0; i < 6; i++)
  {
    if (arduboy.everyXFrames(1)) chain[i].x--;
    if (chain[i].isVisible)sprites.drawPlusMask (chain[i].x, chain[i].y, dungeonChain_plus_mask, 0);
  }
  if (chain[5].x < -255) setChains();
}



void drawWallParts()
{
  for (byte i = 0; i < 3; i++)
  {
    if (window[i].isVisible)sprites.drawSelfMasked (wallPart[i].x + 16, WINDOW_Y, dungeonWindow, 0);
    if (torchHandles[i].isVisible)sprites.drawSelfMasked (wallPart[i].x + 19, TORCHHANDLE_Y, torchHandle, 0);
    if (torchFlames[i].isVisible)sprites.drawSelfMasked (wallPart[i].x + 16, TORCHFLAME_Y, torchFlame, flameFrame);
    for (byte k = 0; k < 4; k++)
    {
      sprites.drawSelfMasked (wallPart[i].x + ((k / 2) * 32), bricks[k + (4 * i)].y, dungeonBricks, bricks[k + (4 * i)].type);
    }

  }
}


#endif
