#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define ENEMY_LEFT_OFFSCREEN_LIMIT              -32
#define ENEMY_START_X                           144

#define MAX_ORCS_IN_WAVE                        9
#define ORC_Y                                   40

#define ENEMY_ORC_NO_SPEAR                      0
#define ENEMY_ORC_FLAT_SPEAR                    1
#define ENEMY_ORC_UP_SPEAR                      2

byte orcFrames;

//////// Orc functions ///////////////////
//////////////////////////////////////////
struct Orcs
{
  public:
    int x;
    byte characteristics;   //0b00000000;   //this byte holds all the orc characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1 / Orc type: 0 = no spear | 1 = flat spear | 2 = up spear
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};


Orcs orc[MAX_ORCS_IN_WAVE];

void setOrcs()
{
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    orc[i] =
    {
      ENEMY_START_X,
      0,
    };
  }
}

void updateOrcs()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) orcFrames++;

  if (arduboy.everyXFrames(WALKINGSPEED))
  {
    for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
    {
      if (orc[i].x > ENEMY_LEFT_OFFSCREEN_LIMIT) orc[i].x -= 3;
      else 
      {
        orc[i].x = ENEMY_START_X;
        orc[i].characteristics = 0;
      }
    }
  }
}


void OrcsSetInLine(byte orcType, byte firstOrc, byte lastOrc, int x, int spacingX)
{
  for (byte i = firstOrc; i < lastOrc + 1; i++)
  {
    orc[i].characteristics = orcType;
    bitSet(orc[i].characteristics, 4);
    bitSet(orc[i].characteristics, 7);
    orc[i].x = x + (spacingX * (i - firstOrc));
  }
}

void drawOrcs()
{
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    if (bitRead(orc[i].characteristics, 4))
    {
      sprites.drawPlusMask(orc[i].x - 2, ORC_Y - 12 + ((orcFrames + i) % 2), orcHead_plus_mask, 0);
      switch (orc[i].characteristics & 0b00000011)
      {
        case ENEMY_ORC_NO_SPEAR:
          sprites.drawPlusMask(orc[i].x, ORC_Y + ((orcFrames + i) % 2), orcBody_plus_mask, pgm_read_byte(&frameSequence[(orcFrames + i) % 4]));
          break;
        case ENEMY_ORC_FLAT_SPEAR:
          sprites.drawPlusMask(orc[i].x - 18, ORC_Y + ((orcFrames + i) % 2), orcBodySpearF_plus_mask, pgm_read_byte(&frameSequence[(orcFrames + i) % 4]));
          break;
        case ENEMY_ORC_UP_SPEAR:
          sprites.drawPlusMask(orc[i].x - 1, ORC_Y + ((orcFrames + i) % 2), orcBodySpearU_plus_mask, pgm_read_byte(&frameSequence[(orcFrames + i) % 4]));
          sprites.drawPlusMask(orc[i].x - 2, ORC_Y + ((orcFrames + i) % 2)-24, orcSpearU_plus_mask, 0);
          break;
      }
    }
  }
}


#endif
