#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"
#include "elements.h"

#define ENEMY_LEFT_OFFSCREEN_LIMIT              -32
#define FLAME_FALL_OFF_LIMIT                    102
#define ENEMY_START_X                           144
#define BADFLAME_START_X                        128

#define MAX_ORCS_IN_WAVE                        9
#define MAX_SPIKES_IN_WAVE                      3

#define ORC_Y                                   39
#define SPIKE_Y                                 41
#define BADFLAME_Y                              4
#define STATUE_Y                                32
#define ARROW_Y                                 40

#define ENEMY_ORC_NO_SPEAR                      0
#define ENEMY_ORC_FLAT_SPEAR                    1
#define ENEMY_ORC_UP_SPEAR                      2

#define BADFLAME_ON_TORCH                       0
#define BADFLAME_FALLING                        1
#define BADFLAME_RUNNING                        2

#define BADFLAME_TOTAL_FALING_FRAMES            10

byte orcFrames;

const unsigned char PROGMEM flameJumpSequence[] = {3, 0, 0, 0, 3, 6, 10, 15, 21, 32};

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


void orcsSetInLine(byte orcType, byte firstOrc, byte lastOrc, int x, int spacingX)
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
          sprites.drawPlusMask(orc[i].x - 2, ORC_Y + ((orcFrames + i) % 2) - 24, orcSpearU_plus_mask, 0);
          break;
      }
    }
  }
}

//////// Spike functions /////////////////
//////////////////////////////////////////
struct Spikes
{
  public:
    int x;
    byte characteristics;   //0b00000000;   //this byte holds all the spike characteristics
    //                          ||||||||
    //                          |||||||└->  0
    //                          ||||||└-->  1
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

Spikes spike[MAX_SPIKES_IN_WAVE];

void setSpikes()
{
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
  {
    spike[i] =
    {
      ENEMY_START_X,
      0,
    };
  }
}

void updateSpikes()
{
  if (arduboy.everyXFrames(2))
  {
    for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
    {
      if (spike[i].x > ENEMY_LEFT_OFFSCREEN_LIMIT) spike[i].x--;
      else
      {
        spike[i].x = ENEMY_START_X;
        spike[i].characteristics = 0;
      }
    }
  }
}

void spikesSetInLine(byte firstspike, byte lastspike, int x, int spacingX)
{
  for (byte i = firstspike; i < lastspike + 1; i++)
  {
    spike[i].characteristics = 0;
    bitSet(spike[i].characteristics, 4);
    bitSet(spike[i].characteristics, 6);
    bitSet(spike[i].characteristics, 7);
    spike[i].x = x + (spacingX * (i - firstspike));
  }
}

void drawSpikes()
{
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
  {
    if (bitRead(spike[i].characteristics, 4))
    {
      sprites.drawSelfMasked(spike[i].x, SPIKE_Y, hazardSpike, 0);
    }
  }
}

//////// Bad Flame functions /////////////
//////////////////////////////////////////
struct BadFlames
{
  public:
    int x;
    byte y;
    byte fallingFrame;
    byte characteristics;   //0b00000000;   //this byte holds all the bad flame characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1 / flame type: 0 = on torch | 1 = falling | 2 = running
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

BadFlames badFlame;

void setBadFlame()
{
  badFlame =
  {
    BADFLAME_START_X,
    BADFLAME_Y,
    0,
    0,
  };
}

void updateBadFlame()
{
  switch (badFlame.characteristics & 0B00000011)
  {
    case BADFLAME_ON_TORCH:
      if (arduboy.everyXFrames(3))
      {

        if (badFlame.x > FLAME_FALL_OFF_LIMIT) badFlame.x--;
        else badFlame.characteristics++;
      }
      break;
    case BADFLAME_FALLING:
      if (arduboy.everyXFrames(WALKINGSPEED))
      {
        badFlame.x -= 3;
        if (badFlame.fallingFrame < BADFLAME_TOTAL_FALING_FRAMES)
        {
          badFlame.y = pgm_read_byte(&flameJumpSequence[badFlame.fallingFrame]);
          badFlame.fallingFrame++;
        }
        else
        {
          badFlame.fallingFrame = 0;
          badFlame.characteristics++;
        }
      }
      break;
    case BADFLAME_RUNNING:
      if (arduboy.everyXFrames(WALKINGSPEED))
      {
        if (badFlame.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badFlame.x -= 3;
        else
        {
          badFlame.x = BADFLAME_START_X;
          badFlame.y = BADFLAME_Y;
          badFlame.characteristics = 0;
        }
      }
      break;
  }
}

void badFlameSetInLine()
{
  badFlame.characteristics = 0;
  bitSet(badFlame.characteristics, 4);
  bitSet(badFlame.characteristics, 6);
  bitSet(badFlame.characteristics, 7);
  badFlame.x = BADFLAME_START_X;
}

void drawBadFlame()
{
  if (bitRead(badFlame.characteristics, 4))
  {
    switch (badFlame.characteristics & 0B00000011)
    {
      case BADFLAME_ON_TORCH:
        sprites.drawPlusMask(badFlame.x, badFlame.y, monsterFlame_plus_mask, flameFrame);
        break;
      case BADFLAME_FALLING:
        sprites.drawPlusMask(badFlame.x, badFlame.y, monsterFlame_plus_mask, flameFrame);
        break;
      case BADFLAME_RUNNING:
        sprites.drawPlusMask(badFlame.x, badFlame.y, monsterFlame_plus_mask, flameFrame);
        break;
    }
  }
}

//////// Statue functions /////////////
///////////////////////////////////////
struct Statues
{
  public:
    int x;
    byte characteristics;   //0b00000000;   //this byte holds all the statue characteristics
    //                          ||||||||
    //                          |||||||└->  0
    //                          ||||||└-->  1
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

Statues statue;
Statues arrow;

void setStatue()
{
  statue =
  {
    ENEMY_START_X,
    0,
  };
  arrow =
  {
    ENEMY_START_X,
    0,
  };
}

void updateStatue()
{
  if (arduboy.everyXFrames(2))
  {
    if (statue.x > ENEMY_LEFT_OFFSCREEN_LIMIT) statue.x--;
    else
    {
      statue.x = ENEMY_START_X;
      statue.characteristics = 0;
    }
    if (statue.x > 102) arrow.x--;
    else
    {
      if (arrow.x > ENEMY_LEFT_OFFSCREEN_LIMIT) arrow.x -= 4;
      else
      {
        arrow.x = ENEMY_START_X + 3;
        arrow.characteristics = 0;
      }
    }
  }
}

void statueSetInLine()
{
  statue.characteristics = 0;
  bitSet(statue.characteristics, 4);
  bitSet(statue.characteristics, 6);
  bitSet(statue.characteristics, 7);
  statue.x = ENEMY_START_X;

  arrow.characteristics = 0;
  bitSet(arrow.characteristics, 4);
  bitSet(arrow.characteristics, 6);
  bitSet(arrow.characteristics, 7);
  arrow.x = ENEMY_START_X + 3;
}

void drawStatueFront()
{
  if (bitRead(statue.characteristics, 4))
  {
    sprites.drawPlusMask(statue.x, STATUE_Y, statueFront_plus_mask, 0);
  }
}

void drawStatueBack()
{
  if (bitRead(statue.characteristics, 4))
  {
    sprites.drawPlusMask(statue.x + 7, STATUE_Y, statueBack_plus_mask, 0);
  }
}

void drawArrows()
{
  if (bitRead(arrow.characteristics, 4))
  {
    sprites.drawPlusMask(arrow.x, ARROW_Y, statueArrow_plus_mask, 0);
  }
}


#endif
