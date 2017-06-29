#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define HELENA_START_X                             20
#define HELENA_START_Y                             33

#define HELENA_DEAD                                 0
#define HELENA_NAKED                                1
#define HELENA_ARMOR                                2
#define HELENA_HELMET                               3

#define HELMET_NO_HELMET                            0
#define HELMET_WARRIOR                              1
#define HELMET_FOOTBALL                             2
#define HELMET_THIEF                                3
#define HELMET_CUTTER                               4
#define HELMET_MAGNET                               5
#define HELMET_ATLAS                                6
#define HELMET_BATTERY                              7

#define WEAPON_NONE                                 0
#define WEAPON_DAGGER                               1
#define WEAPON_SWORD                                2

#define HELENA_IMUNE_TIME                          30
#define HELENA_FLICKER_TIME                        15

#define HELENA_COLLISION_X_OFFSET                   3
#define HELENA_COLLISION_Y_OFFSET                   -2
#define HELENA_COLLISION_WIDTH                      8
#define HELENA_COLLISION_HEIGHT                     14


const unsigned char PROGMEM helenaJumpSequence[] = {6, 14, 20, 23, 23, 25, 25, 25, 26, 26, 26, 26, 25, 25, 25, 23, 23, 20, 14, 6};

struct Players
{
  public:
    int x, y;
    byte life, frame, helmet, nextHelmet, jumpSequenceCounter, imuneTimer, flickerTimer;
    byte characteristics;   //0b00000000;   //this byte holds all the players characteristics
    //                          ||||||||
    //                          |||||||└->  0 \ weapon type ( 0 = none / 1 = dagger / 2 = sword)
    //                          ||||||└-->  1 /
    //                          |||||└--->  2 - the player is changing helmets    (0 = false / 1 = true)
    //                          ||||└---->  3 - the players helmet is flickering  (0 = false / 1 = true)
    //                          |||└----->  4 - the player is visible             (0 = false / 1 = true)
    //                          ||└------>  5 - the player is Imune               (0 = false / 1 = true)
    //                          |└------->  6 - the player is jumping             (0 = false / 1 = true)
    //                          └-------->  7 - the player is stabbing            (0 = false / 1 = true)
};


Players helena;

void setHelena()
{
  helena =
  {
    HELENA_START_X, HELENA_START_Y,                     // start position
    HELENA_ARMOR,                                       // start life with armor
    //HELENA_NAKED,
    0,                                                  // start animation at frame 0
    HELMET_NO_HELMET,                                   // start without a helmet
    HELMET_NO_HELMET,                                   // start without a next helmet
    0,                                                  // start the sequence counter at 0
    0,                                                  // start the imuneTimer at 0
    0,                                                  // start the flickerTimer at 0
    0b00110010,                                         // start visible / imune and with sword
  };
}

void checkWeapon()
{

}

void updateHelena()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) helena.frame = (++helena.frame) % 4;

  if (helena.characteristics & 0B00100000) //if imune
  {
    if (arduboy.everyXFrames(3))
    {
      helena.imuneTimer++;
      helena.characteristics ^= 0B00010000;
    }
    if (helena.imuneTimer > HELENA_IMUNE_TIME)
    {
      helena.imuneTimer = 0;
      helena.characteristics &= 0B11011111;
      helena.characteristics |= 0B00010000;
    }
  }
  if (helena.characteristics & 0B01000000)  // if jumping
  {
    if (arduboy.everyXFrames(2)) helena.jumpSequenceCounter++;
    if (helena.jumpSequenceCounter > 19)
    {
      helena.jumpSequenceCounter = 0;
      helena.characteristics &= 0B10111111;
    }
  }
  else if (helena.x < HELENA_START_X && arduboy.everyXFrames(2)) helena.x++;

  if (helena.characteristics & 0B00000100)
  {
    if (arduboy.everyXFrames(5))
    {
      helena.flickerTimer++;
      helena.characteristics ^= 0B00001000;
    }
    if (helena.flickerTimer > HELENA_FLICKER_TIME)
    {
      helena.flickerTimer = 0;
      helena.characteristics &= 0B11110011;
      helena.helmet = helena.nextHelmet;
    }
  }

  if (helena.life < HELENA_HELMET) helena.helmet = 0;
  switch (helena.helmet)
  {
    case HELMET_NO_HELMET:
      if (helena.life == HELENA_NAKED) helena.characteristics = (helena.characteristics & 0B11111100) + 1;
      else helena.characteristics = (helena.characteristics & 0B11111100) + 2;
      break;
    case HELMET_WARRIOR:
      helena.characteristics = (helena.characteristics & 0B11111100) + 2;
      break;
    case HELMET_FOOTBALL:
      helena.characteristics = (helena.characteristics & 0B11111100) + 0;
      break;
    case HELMET_THIEF:
      helena.characteristics = (helena.characteristics & 0B11111100) + 1;
      break;
    case HELMET_CUTTER:
      helena.characteristics = (helena.characteristics & 0B11111100) + 0;
      break;
    case HELMET_MAGNET:
      helena.characteristics = (helena.characteristics & 0B11111100) + 2;
      break;
    case HELMET_ATLAS:
      helena.characteristics = (helena.characteristics & 0B11111100) + 0;
      break;
    case HELMET_BATTERY:
      helena.characteristics = (helena.characteristics & 0B11111100) + 0;
      break;
  }
  if (helena.x < 1) helena.life = HELENA_DEAD;
  if (helena.life == HELENA_DEAD) gameState = STATE_MENU_MAIN;
}


void drawHelena()
{
  switch (helena.characteristics & 0B11010000)
  {
    case 0B00010000:        // visible
      sprites.drawPlusMask(helena.x, helena.y + (helena.frame % 2), playerNaked_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
      if (!(helena.characteristics & 0B00001000))sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.helmet);
      if ((helena.characteristics & 0B00001100) == 0B00001100) sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.nextHelmet);
      if (helena.life > HELENA_NAKED)
      {
        if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 13 + pgm_read_byte(&frameSequence[helena.frame]), helena.y  + (helena.frame % 2) + 6, playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
        sprites.drawPlusMask(helena.x - 2 , helena.y + 4 + (helena.frame % 2), playerArmor_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
      }
      else if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 12 + pgm_read_byte(&frameSequence[helena.frame]), helena.y  + (helena.frame % 2) + 6, playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
      break;
    case 0B01010000:        // visible & jumping
      sprites.drawPlusMask(helena.x - 3 , helena.y - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerNakedJump_plus_mask, 0);
      if (!(helena.characteristics & 0B00001000)) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.helmet);
      if ((helena.characteristics & 0B00001100) == 0B00001100) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.nextHelmet);
      if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 16, helena.y  + 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
      if (helena.life > HELENA_NAKED) sprites.drawPlusMask(helena.x - 5 , helena.y + 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerArmorJump_plus_mask, 0);
      break;
  }
}


#endif
