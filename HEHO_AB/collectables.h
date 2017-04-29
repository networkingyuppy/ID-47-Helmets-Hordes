#ifndef COLLACTBLES_H
#define COLLACTBLES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_GOLDBARS                             9

byte goldBarFrames = 0;
const unsigned char PROGMEM goldBarSequence[] = {0, 1, 2, 3, 4, 3, 2, 1};

struct DifferentItems
{
  public:
    int x;
    byte y;
    boolean isVisible;
    boolean active;
};

DifferentItems goldBar[MAX_ONSCREEN_GOLDBARS];


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

void updateGoldBars()
{
  if (arduboy.everyXFrames(8))goldBarFrames++;
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (arduboy.everyXFrames(2))goldBar[i].x--;
    if (goldBar[i].x < -16)
    {
      goldBar[i].x = 128;
      goldBar[i].active = false;
      goldBar[i].isVisible = false;
    }
  }
}

goldBarSetInLine()
{
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    goldBar[i].x = 128 + (16*i);
    goldBar[i].y = 28;
    goldBar[i].isVisible = true;
    goldBar[i].active = true;
  }
}

void drawGoldBars()
{

  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (goldBar[i].isVisible == true)
    {
      sprites.drawPlusMask(goldBar[i].x, goldBar[i].y, treasureBar_plus_mask,  pgm_read_byte(&goldBarSequence[(goldBarFrames) % 8]));
    }
  }
}

#endif
