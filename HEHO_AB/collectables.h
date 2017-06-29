#ifndef COLLACTBLES_H
#define COLLACTBLES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_GOLDBARS                             9

#define GOLDBAR_COLLISION_WIDTH                           10
#define GOLDBAR_COLLISION_HEIGHT                          16

#define SECRET_CHEST_Y                                    35
#define SECRET_CHEST_START_X                              128

#define SECRET_CHEST_COLLISION_WIDTH                      16
#define SECRET_CHEST_COLLISION_HEIGHT                     14


byte goldBarFrames = 0;
const unsigned char PROGMEM goldBarSequence[] = {0, 1, 2, 3, 4, 3, 2, 1};

struct DifferentItems
{
  public:
    int x;
    byte y;
    byte characteristics;   //0b00000000;   //this byte holds all the collectable characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1  | type of item ( 0 to 7 )
    //                          |||||└--->  2 /
    //                          ||||└---->  3
    //                          |||└----->  4 the collectable is visible   (0 = false / 1 = true)
    //                          ||└------>  5
    //                          |└------->  6 the twinkles are visible     (0 = false / 1 = true)
    //                          └-------->  7 the collectable is active    (0 = false / 1 = true)
};

DifferentItems goldBar[MAX_ONSCREEN_GOLDBARS];
DifferentItems secretChest;

void updateGoldBars()
{
  if (arduboy.everyXFrames(8))goldBarFrames++;
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (arduboy.everyXFrames(2))goldBar[i].x--;
    if (goldBar[i].x < -16) goldBar[i].characteristics = 0;
  }
}

goldBarSetInLine()
{
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    goldBar[i].x = 128 + (16 * i);
    goldBar[i].y = 28;
    goldBar[i].characteristics = 0b10010000;
  }
}

void drawGoldBars()
{

  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (goldBar[i].characteristics & 0B00010000)
    {
      sprites.drawPlusMask(goldBar[i].x, goldBar[i].y, treasureBar_plus_mask,  pgm_read_byte(&goldBarSequence[(goldBarFrames) % 8]));
    }
  }
}


void updateSecretChest()
{
  if (arduboy.everyXFrames(2))secretChest.x--;
  if (secretChest.x < -16) secretChest.characteristics = 0;
}

void secretChestSetInLine(byte type)
{
  secretChest.x = SECRET_CHEST_START_X;
  secretChest.y = SECRET_CHEST_Y;
  secretChest.characteristics = 0b10010000 + type;
  sparkleFrame = 7;
}

void drawSecretChest()
{
  if (secretChest.characteristics & 0B00010000)
  {
    sprites.drawSelfMasked(secretChest.x, secretChest.y, dungeonChest, 0);
  }
}

void setCollectables()
{
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++) goldBar[i].characteristics = 0;
  secretChest.characteristics = 0;
}

void drawSecretSparkles()
{
  if (secretChest.characteristics & 0B01000000)
  {
    if (arduboy.everyXFrames(6))sparkleFrame++;
    sprites.drawPlusMask(secretChest.x, 32, effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 3) % 15]));
    sprites.drawPlusMask(secretChest.x - 4, 43, effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 1)  % 15]));
    sprites.drawPlusMask(secretChest.x - 11, 37, effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 2) % 15]));
  }
}


#endif
