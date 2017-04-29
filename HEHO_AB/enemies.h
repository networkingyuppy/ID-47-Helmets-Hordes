#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"
#include "elements.h"

#define ENEMY_LEFT_OFFSCREEN_LIMIT              -32
#define FLAME_FALL_OFF_LIMIT                    102
#define WEED_HIDING_LIMIT                       102
#define ENEMY_START_X                           144
#define BADWALKINGFLAME_START_X                 128
#define BADFLAME_START_X                        128
#define BADWEED_START_X                         128

#define MAX_ORCS_IN_WAVE                        9
#define MAX_SPIKES_IN_WAVE                      3

#define ORC_Y                                   39
#define SPIKE_Y                                 41
#define BADWALKINGFLAME_Y                       4
#define BADFLAME_Y                              4
#define STATUE_Y                                32
#define ARROW_Y                                 40
#define BADWEED_Y                               40

#define ORC_COLLISION_WIDTH                     14
#define SPEAR_F_COLLISION_WIDTH                 28
#define SPEAR_U_COLLISION_WIDTH                 3
#define SPIKE_COLLISION_WIDTH                   8
#define BADWALKINGFLAME_COLLISION_WIDTH         12
#define BADFLAME_COLLISION_WIDTH                80
#define STATUE_COLLISION_WIDTH                  80
#define ARROW_COLLISION_WIDTH                   80
#define BADWEED_COLLISION_WIDTH                 80

#define ORC_COLLISION_HEIGHT                    18
#define SPEAR_F_COLLISION_HEIGHT                3
#define SPEAR_U_COLLISION_HEIGHT                24
#define SPIKE_COLLISION_HEIGHT                  8
#define BADWALKINGFLAME_COLLISION_HEIGHT        12
#define BADFLAME_COLLISION_HEIGHT               80
#define STATUE_COLLISION_HEIGHT                 80
#define ARROW_COLLISION_HEIGHT                  80
#define BADWEED_COLLISION_HEIGHT                80

#define ENEMY_ORC_NO_SPEAR                      0
#define ENEMY_ORC_FLAT_SPEAR                    1
#define ENEMY_ORC_UP_SPEAR                      2

#define BADFLAME_ON_TORCH                       0
#define BADFLAME_FALLING                        1
#define BADFLAME_RUNNING                        2

#define BADWEED_HIDING                          0
#define BADWEED_PEEKING                         1
#define BADWEED_SHOWING                         2

#define BADFLAME_TOTAL_FALING_FRAMES            10
#define BADWEED_TOTAL_PEEKING_FRAMES            9

byte orcFrames;
byte weedFrame;

const unsigned char PROGMEM flameJumpSequence[] = {3, 0, 0, 0, 3, 6, 10, 15, 21, 32};
const unsigned char PROGMEM weedPeekSequence[] = {34, 34, 30, 30, 28 , 30, 30 , 32, 32};



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
      sprites.drawPlusMask(spike[i].x, SPIKE_Y, hazardSpike_plus_mask, 0);
    }
  }
}

//////// Bad Walking Flame functions /////
//////////////////////////////////////////
struct BadWalkingFlames
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

BadWalkingFlames badWalkingFlame;

void setBadWalkingFlame()
{
  badWalkingFlame =
  {
    BADWALKINGFLAME_START_X,
    BADWALKINGFLAME_Y,
    0,
    0,
  };
}

void updateBadWalkingFlame()
{
  switch (badWalkingFlame.characteristics & 0B00000011)
  {
    case BADFLAME_ON_TORCH:
      if (arduboy.everyXFrames(3))
      {

        if (badWalkingFlame.x > FLAME_FALL_OFF_LIMIT) badWalkingFlame.x--;
        else badWalkingFlame.characteristics++;
      }
      break;
    case BADFLAME_FALLING:
      if (arduboy.everyXFrames(WALKINGSPEED))
      {
        badWalkingFlame.x -= 3;
        if (badWalkingFlame.fallingFrame < BADFLAME_TOTAL_FALING_FRAMES)
        {
          badWalkingFlame.y = pgm_read_byte(&flameJumpSequence[badWalkingFlame.fallingFrame]);
          badWalkingFlame.fallingFrame++;
        }
        else
        {
          badWalkingFlame.fallingFrame = 0;
          badWalkingFlame.characteristics++;
        }
      }
      break;
    case BADFLAME_RUNNING:
      if (arduboy.everyXFrames(WALKINGSPEED))
      {
        if (badWalkingFlame.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badWalkingFlame.x -= 3;
        else
        {
          badWalkingFlame.x = BADWALKINGFLAME_START_X;
          badWalkingFlame.y = BADWALKINGFLAME_Y;
          badWalkingFlame.characteristics = 0;
        }
      }
      break;
  }
}

void badWalkingFlameSetInLine()
{
  badWalkingFlame.characteristics = 0;
  bitSet(badWalkingFlame.characteristics, 4);
  bitSet(badWalkingFlame.characteristics, 6);
  bitSet(badWalkingFlame.characteristics, 7);
  badWalkingFlame.x = BADFLAME_START_X;
}

void drawBadWalkingFlame()
{
  if (bitRead(badWalkingFlame.characteristics, 4))
  {
    sprites.drawPlusMask(badWalkingFlame.x, badWalkingFlame.y, monsterFlame_plus_mask, flameFrame);
  }
}

//////// Bad Flame functions /////////////
//////////////////////////////////////////
struct BadFlames
{
  public:
    int x;
    byte y;
    byte characteristics;   //0b00000000;   //this byte holds all the bad flame characteristics
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

BadFlames badFlame;

void setBadFlame()
{
  badFlame =
  {
    BADFLAME_START_X,
    BADFLAME_Y,
    0,
  };
}

void updateBadFlame()
{
  if (arduboy.everyXFrames(3))
  {

    if (badFlame.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badFlame.x--;
    else
    {
      badFlame.x = BADFLAME_START_X;
      badFlame.y = BADFLAME_Y;
      badFlame.characteristics = 0;
    }
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
    sprites.drawPlusMask(badFlame.x, badFlame.y, monsterFlame_plus_mask, flameFrame);
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

//////// Bad Weed functions ///////////
///////////////////////////////////////
struct BadWeeds
{
  public:
    int x;
    byte y;
    byte peekingFrame;
    byte weedFrame;
    byte characteristics;   //0b00000000;   //this byte holds all the bad weed characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1 / Weed type: 0 = hidding | 1 = peeking | 2 = showing
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

BadWeeds badWeed;

void setBadWeed()
{
  badWeed =
  {
    BADWEED_START_X,
    BADWEED_Y,
    0,
    0,
    0,
  };
}

void updateBadWeed()
{
  switch (badWeed.characteristics & 0B00000011)
  {
    case BADWEED_HIDING:
      if (arduboy.everyXFrames(2))
      {

        if (badWeed.x > WEED_HIDING_LIMIT) badWeed.x--;
        else badWeed.characteristics++;
      }
      break;
    case BADWEED_PEEKING:
      if (arduboy.everyXFrames(4)) badWeed.weedFrame = (++badWeed.weedFrame) % 4;
      if (arduboy.everyXFrames(2))
      {
        badWeed.x--;
        if (badWeed.peekingFrame < BADWEED_TOTAL_PEEKING_FRAMES)
        {
          badWeed.y = pgm_read_byte(&weedPeekSequence[badWeed.peekingFrame]);
          badWeed.peekingFrame++;
        }
        else
        {
          badWeed.peekingFrame = 0;
          badWeed.weedFrame = 0;
          badWeed.characteristics++;
        }
      }
      break;
    case BADWEED_SHOWING:
      if (arduboy.everyXFrames(2))
      {
        if (badWeed.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badWeed.x--;
        else
        {
          badWeed.x = BADWEED_START_X;
          badWeed.y = BADWEED_Y;
          badWeed.characteristics = 0;
        }
      }
      break;
  }
}

void badWeedSetInLine()
{
  badWeed.characteristics = 0;
  bitSet(badWeed.characteristics, 4);
  bitSet(badWeed.characteristics, 6);
  bitSet(badWeed.characteristics, 7);
  badWeed.x = BADWEED_START_X;
}

void drawBadWeed()
{
  if (bitRead(badWeed.characteristics, 4))
  {
    switch (badWeed.characteristics & 0B00000011)
    {
      case BADWEED_HIDING:
        sprites.drawPlusMask(badWeed.x, badWeed.y, monsterWeed_plus_mask, badWeed.weedFrame);
        sprites.drawErase (badWeed.x, FLOORWEED_Y + 8, weedMask, 0);
        break;
      case BADWEED_PEEKING:
        sprites.drawPlusMask(badWeed.x, badWeed.y, monsterWeed_plus_mask, badWeed.weedFrame);
        sprites.drawErase (badWeed.x, FLOORWEED_Y + 8, weedMask, 0);
        break;
      case BADWEED_SHOWING:
        sprites.drawPlusMask(badWeed.x, badWeed.y, monsterWeed_plus_mask, badWeed.weedFrame);
        sprites.drawErase (badWeed.x, FLOORWEED_Y + 8, weedMask, 0);
        break;
    }
  }
}
#endif
