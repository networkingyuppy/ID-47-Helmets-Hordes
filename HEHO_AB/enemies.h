#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_ORCS                       1
#define ENEMY_LEFT_OFFSCREEN_LIMIT              -32

#define ENEMY_START_X                           160
#define ENEMY_START_Y                           40

#define ENEMY_ORC_NO_SPEAR                      0
#define ENEMY_ORC_FLAT_SPEAR                    1
#define ENEMY_ORC_UP_SPEAR                      3

byte enemyFrames;

struct Orc
{
  public:
    int x, y;
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


Orc orcs[MAX_ONSCREEN_ORCS];

void setEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_ORCS; i++)
  {
    orcs[i] =
    {
      ENEMY_START_X,
      ENEMY_START_Y,
      0b00010001,
    };
  }
}

void updateOrcs()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) enemyFrames++;

  if (arduboy.everyXFrames(WALKINGSPEED))
  {
    for (byte i = 0; i < MAX_ONSCREEN_ORCS; i++)
    {
      if (orcs[i].x > ENEMY_LEFT_OFFSCREEN_LIMIT) orcs[i].x -= 3;
      else orcs[i].x = ENEMY_START_X;
    }
  }
}

void drawOrcs()
{
  for (byte i = 0; i < MAX_ONSCREEN_ORCS; i++)
  {
    if (bitRead(orcs[i].characteristics, 4))
    {
      sprites.drawPlusMask(orcs[i].x - 2, orcs[i].y - 12, orcHead_plus_mask, 0);

      switch (orcs[i].characteristics & 0b00000011)
      {
        case ENEMY_ORC_NO_SPEAR:
          sprites.drawPlusMask(orcs[i].x, orcs[i].y, orcBody_plus_mask, frameSequence[(enemyFrames + i) % 4]);
          break;
        case ENEMY_ORC_FLAT_SPEAR:
          sprites.drawPlusMask(orcs[i].x - 18, orcs[i].y, orcBodySpearF_plus_mask, frameSequence[(enemyFrames + i) % 4]);
          break;
        case ENEMY_ORC_UP_SPEAR:
          break;
      }
    }
  }
}


#endif
