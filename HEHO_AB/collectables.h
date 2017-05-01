#ifndef COLLACTBLES_H
#define COLLACTBLES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_GOLDBARS                             9

#define GOLDBAR_COLLISION_WIDTH                           10
#define GOLDBAR_COLLISION_HEIGHT                          16


byte goldBarFrames = 0;
const unsigned char PROGMEM goldBarSequence[] = {0, 1, 2, 3, 4, 3, 2, 1};

struct DifferentItems
{
  public:
    int x;
    byte y;
    byte characteristics;   //0b00000000;   //this byte holds all the orc characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1  | type of item ( 0 to 7 )
    //                          |||||└--->  2 /
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5
    //                          |└------->  6
    //                          └-------->  7 the enemy is active    (0 = false / 1 = true)
};

DifferentItems goldBar[MAX_ONSCREEN_GOLDBARS];
DifferentItems helmetPickUp;


void setGoldBars()
{
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    goldBar[i].x = 128;
    goldBar[i].y = 28;
    goldBar[i].characteristics = 0;
  }
}

void updateGoldBars()
{
  if (arduboy.everyXFrames(8))goldBarFrames++;
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (arduboy.everyXFrames(2))goldBar[i].x--;
    if (goldBar[i].x < -16)
    {
      goldBar[i].x = 128;
      goldBar[i].characteristics = 0;
    }
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
    if (bitRead(goldBar[i].characteristics, 4))
    {
      sprites.drawPlusMask(goldBar[i].x, goldBar[i].y, treasureBar_plus_mask,  pgm_read_byte(&goldBarSequence[(goldBarFrames) % 8]));
    }
  }
}


void setHelmetPickUp()
{
  HelmetPickUp.x = 128;
  HelmetPickUp.y = 28;
  HelmetPickUp.characteristics = 0;
}

void updateHelmetPickUp()
{
  if (arduboy.everyXFrames(2))HelmetPickUp.x--;
  if (HelmetPickUp.x < -16)
  {
    HelmetPickUp.x = 128;
    HelmetPickUp.characteristics = 0;
  }
}

helmetPickUpSetInLine(byte type)
{
  HelmetPickUp.x = 128;
  HelmetPickUp.y = 28;
  HelmetPickUp.characteristics = 0b10010000 + type;
}

void drawhelmetPickUp()
{
  if (bitRead(HelmetPickUp.characteristics, 4))
  {
    sprites.drawPlusMask(HelmetPickUp.x, HelmetPickUp.y, playerHelmets_plus_mask, HelmetPickUp.characteristics & 0b00000111);
  }
}


#endif
