#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"

#define FLOORPART_Y                                       48
#define FLOORWEED_Y                                       39
#define TORCHHANDLE_Y                                     20
#define TORCHFLAME_Y                                      4
#define WINDOW_Y                                          3

byte flameFrame = 0;

// create all elements
//////////////////////

struct BackGroundStuff
{
  int x;
  boolean isVisible;
};

BackGroundStuff floorPart[3];
BackGroundStuff torchHandles[2];
BackGroundStuff torchFlames[2];
BackGroundStuff floorWeed;
BackGroundStuff window[2];


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
  for (byte i = 0; i < 2; i++) torchHandles[i].isVisible = true;
}

void setTorchFlames()
{
  torchFlames[0].x = 15;
  torchFlames[1].x = 95;
  for (byte i = 0; i < 2; i++) torchFlames[i].isVisible = true;
}

void setFLoorWeed()
{
  floorWeed.x = 64;
}


void setChains()
{
  chain[0].x = 128;
  chain[0].y = 0;
  chain[1].x = 128;
  chain[1].y = 16;
  chain[2].x = 128;
  chain[2].y = 24;

  chain[3].x = 144;
  chain[3].y = 0;
  chain[4].x = 144;
  chain[4].y = 16;
  chain[5].x = 144;
  chain[5].y = 32;
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

void setWindows()
{
  for (byte i = 0; i < 2; i++)
  {
    window[i].x = 56 + (80 * i);
    window[i].isVisible = random(2);
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
    if (torchHandles[i].x < -28)
    {
      torchHandles[i].x = 131;
      torchHandles[i].isVisible = random(2);
    }
    if (torchHandles[i].isVisible)sprites.drawSelfMasked (torchHandles[i].x, TORCHHANDLE_Y, torchHandle, 0);
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
      torchFlames[i].isVisible = torchHandles[i].isVisible;
    }
    if (torchFlames[i].isVisible)sprites.drawSelfMasked (torchFlames[i].x, TORCHFLAME_Y, torchFlame, flameFrame);
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

void drawWindows()
{
  for (byte i = 0; i < 2; i++)
  {
    if (arduboy.everyXFrames(3)) window[i].x--;
    if (window[i].x < -31)
    {
      window[i].x = 128;
      window[i].isVisible = random(2);
    }
    if (window[i].isVisible)sprites.drawSelfMasked (window[i].x, WINDOW_Y, dungeonWindow, 0);
  }
}


#endif
