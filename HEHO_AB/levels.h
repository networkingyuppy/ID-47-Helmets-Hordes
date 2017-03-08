#ifndef LEVELS_H
#define LEVELS_H

#include "globals.h"

#define FLOORPART_Y                               48
#define TORCHHANDLE_Y                             20
#define TORCHFLAME_Y                              4

byte flameFrame = 0;

struct BackGroundStuff
{
  int x;
};

BackGroundStuff floorPart[3];
BackGroundStuff torchHandles[2];
BackGroundStuff torchFlames[2];


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


void setFloorPart()
{
  for (byte i = 0; i < 3; i++) floorPart[i].x = 64 * i;
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

void setTorchHandles()
{
  torchHandles[0].x = 18;
  torchHandles[1].x = 98;
}

void setTorchFlames()
{
  torchFlames[0].x = 15;
  torchFlames[1].x = 95;
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
    if (arduboy.everyXFrames(3)) bricks[i].x --;
    if (bricks[i].x < -111) bricks[i].x = 128;
    if (bricks[i].type < 3) sprites.drawSelfMasked (bricks[i].x, bricks[i].y, dungeonBricks, bricks[i].type);
  }
}

void drawTorchHandles()
{
  for (byte i = 0; i < 2; i++)
  {
    if (arduboy.everyXFrames(3)) torchHandles[i].x --;
    if (torchHandles[i].x < -31) torchHandles[i].x = 128;
    sprites.drawSelfMasked (torchHandles[i].x, TORCHHANDLE_Y, torchHandle, 0);

  }
}

void drawTorchFlames()
{
  if (arduboy.everyXFrames(4)) flameFrame = (++flameFrame) % 4;
  for (byte i = 0; i < 2; i++)
  {
    if (arduboy.everyXFrames(3)) torchFlames[i].x --;
    if (torchFlames[i].x < -31) torchFlames[i].x = 128;
    sprites.drawSelfMasked (torchFlames[i].x, TORCHFLAME_Y, torchFlame, flameFrame);

  }
}

void checkCollisions()
{

}

#endif
