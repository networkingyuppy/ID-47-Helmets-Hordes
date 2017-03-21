#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_GOLDBARS                             9
#define FLOORPART_Y                                       48
#define PILLAR_Y                                          48
#define FLOORWEED_Y                                       41
#define TORCHHANDLE_Y                                     20
#define TORCHFLAME_Y                                      4

const unsigned char PROGMEM goldBarSequence[] = {0, 1, 2, 3, 4, 3, 2, 1};
byte goldBarFrames = 0;
byte flameFrame = 0;

// create all elements
//////////////////////

struct DifferentItems
{
  public:
    int x;
    byte y;
    boolean isVisible;
    boolean active;
};

DifferentItems goldBar[MAX_ONSCREEN_GOLDBARS];


struct BackGroundStuff
{
  int x;
  boolean isVisible;
};

BackGroundStuff floorPart[3];
BackGroundStuff torchHandles[2];
BackGroundStuff torchFlames[2];
BackGroundStuff floorWeed;
BackGroundStuff pillar;


struct ForGroundStuff
{
  int x;
  byte y;
};

ForGroundStuff chain[6];


struct BrickParts
{
  int x;
  byte y, type;
};

BrickParts bricks[12];


// Set all elements
///////////////////

void setFloorPart()
{
  for (byte i = 0; i < 3; i++) floorPart[i].x = 64 * i;
}

void setTorchHandles()
{
  torchHandles[0].x = 18;
  torchHandles[1].x = 98;
}

void setTorchFlames()
{
  torchFlames[0].x = 15;
  torchFlames[1].x = 95;
  torchFlames[0].isVisible = true;
  torchFlames[1].isVisible = true;
}

void setFLoorWeed()
{
  floorWeed.x = 64;
}

void setPillars()
{
  pillar.x = 196;
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

void setBricks()
{
  byte counter = 0;
  for (byte h = 0; h < 3; h++)
  {
    for (byte k = 0; k < 2; k++)
    {
      for (byte i = 0; i < 2; i++)
      {
        bricks[counter].x = (h * 80) + (k * 32);
        bricks[counter].y = 16 * i;
        bricks[counter].type = random(0, 6);
        counter++;
      }
    }
  }
}


void setGoldBars()
{
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    goldBar[i].x = 128;
    goldBar[i].y = 28;
    goldBar[i].isVisible = false;
    goldBar[i].active = false;
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

void drawTorchHandles()
{
  for (byte i = 0; i < 2; i++)
  {
    if (arduboy.everyXFrames(3)) torchHandles[i].x--;
    if (torchHandles[i].x < -31) torchHandles[i].x = 128;
    sprites.drawSelfMasked (torchHandles[i].x, TORCHHANDLE_Y, torchHandle, 0);
  }
}

void drawTorchFlames()
{
  if (arduboy.everyXFrames(4)) flameFrame = (++flameFrame) % 4;
  for (byte i = 0; i < 2; i++)
  {
    if (arduboy.everyXFrames(3)) torchFlames[i].x--;
    if (torchFlames[i].x < -31)
    {
      torchFlames[i].x = 128;
      torchFlames[i].isVisible = true;
    }
    if (torchFlames[i].isVisible)sprites.drawSelfMasked (torchFlames[i].x, TORCHFLAME_Y, torchFlame, flameFrame);
  }
}

void drawFloorWeed()
{
  if (arduboy.everyXFrames(2)) floorWeed.x--;
  if (floorWeed.x < -512) floorWeed.x = 128;
  sprites.drawPlusMask (floorWeed.x, FLOORWEED_Y, dungeonWeed_plus_mask, 0);
}

void drawPillars()
{

  if (arduboy.everyXFrames(1)) pillar.x -= 2;
  if (pillar.x < -63) pillar.x = 128;
  sprites.drawPlusMask (pillar.x, PILLAR_Y, dungeonPillarBase_plus_mask, 0);
  sprites.drawPlusMask (pillar.x + 2, PILLAR_Y - 16, dungeonPillar_plus_mask, 0);
  sprites.drawPlusMask (pillar.x + 2, PILLAR_Y - 32, dungeonPillar_plus_mask, 0);
  sprites.drawPlusMask (pillar.x + 2, PILLAR_Y - 48, dungeonPillar_plus_mask, 0);
}

void drawChains()
{
  for (byte i = 0; i < 3; i++)
  {
    if (arduboy.everyXFrames(1)) chain[i].x -= 2;
    if (chain[i].x < -255) chain[i].x = 128;
    sprites.drawPlusMask (chain[i].x, chain[i].y, dungeonChain_plus_mask, 0);
  }
}

void drawBricks()
{
  for (byte i = 0; i < 12; i++)
  {
    if (arduboy.everyXFrames(3)) bricks[i].x--;
    if (bricks[i].x < -111) bricks[i].x = 128;
    if (bricks[i].type < 3) sprites.drawSelfMasked (bricks[i].x, bricks[i].y, dungeonBricks, bricks[i].type);
  }
}

void drawGoldBars()
{
  if (arduboy.everyXFrames(8))goldBarFrames++;
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {

    if (arduboy.everyXFrames(2))goldBar[i].x--;
    if (goldBar[i].x < -16)
    {
      goldBar[i].x = 128;
    }

    if (goldBar[i].isVisible == true)
    {
      sprites.drawPlusMask(goldBar[i].x, goldBar[i].y, treasureBar_plus_mask,  pgm_read_byte(&goldBarSequence[(goldBarFrames) % 8]));
    }
  }
}


#endif
