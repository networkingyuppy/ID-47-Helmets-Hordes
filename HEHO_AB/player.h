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
#define HELMET_ONE                                  1
#define HELMET_TWO                                  2
#define HELMET_THREE                                3
#define HELMET_FOUR                                 4
#define HELMET_FIVE                                 5
#define HELMET_SIX                                  6
#define HELMET_SEVEN                                7

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
    byte life, frame, helmet, nextHelmet, weapon, jumpSequenceCounter, imuneTimer, flickerTimer;
    boolean isVisible;
    boolean isImune;
    boolean jumping;
    boolean changingHelmet;
    boolean flickeringHelmet;
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
    WEAPON_SWORD,                                       // start with the sword
    0,                                                  // start the sequence counter at 0
    0,                                                  // start the imuneTimer at 0
    0,                                                  // start the flickerTimer at 0
    true,                                               // start with the player visible (used to make her blink)
    true,                                               // start with the player being imune for a short while
    false,                                              // start with the player NOT jumping
    false,                                              // start with the player NOT changing her helmet
    false,                                              // start with the player helmet NOT flickering
  };
}

void checkWeapon()
{

}

void updateHelena()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) helena.frame = (++helena.frame) % 4;

  if (helena.isImune)
  {
    if (arduboy.everyXFrames(3))
    {
      helena.imuneTimer++;
      helena.isVisible = !helena.isVisible;
    }
    if (helena.imuneTimer > HELENA_IMUNE_TIME)
    {
      helena.imuneTimer = 0;
      helena.isImune = false;
      helena.isVisible = true;
    }
  }
  if (helena.jumping)
  {
    if (arduboy.everyXFrames(2)) helena.jumpSequenceCounter++;
    if (helena.jumpSequenceCounter > 19)
    {
      helena.jumpSequenceCounter = 0;
      helena.jumping = false;
    }
  }
  else if (helena.x < HELENA_START_X && arduboy.everyXFrames(2)) helena.x++;
  
  if (helena.changingHelmet)
  {
    if (arduboy.everyXFrames(5))
    {
      helena.flickerTimer++;
      helena.flickeringHelmet = !helena.flickeringHelmet;
    }
    if (helena.flickerTimer > HELENA_FLICKER_TIME)
    {
      helena.flickerTimer = 0;
      helena.flickeringHelmet = false;
      helena.changingHelmet = false;
      helena.helmet = helena.nextHelmet;
    }
  }

  if (helena.x < 1) helena.life = HELENA_DEAD;
  if (helena.life == HELENA_DEAD) gameState = STATE_MENU_MAIN;
}

void drawHelena()
{
  if (helena.isVisible) {
    if (helena.jumping)
    {
      if (helena.weapon) sprites.drawPlusMask(helena.x + 16, helena.y  + 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerWeapon_plus_mask, helena.weapon - 1);
      sprites.drawPlusMask(helena.x - 3 , helena.y - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerNakedJump_plus_mask, 0);
      if (!helena.flickeringHelmet) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.helmet);
      if (helena.changingHelmet && helena.flickeringHelmet) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.nextHelmet);

      if (helena.life > HELENA_NAKED) sprites.drawPlusMask(helena.x - 5 , helena.y + 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerArmorJump_plus_mask, 0);
    }
    else
    {
      sprites.drawPlusMask(helena.x, helena.y + (helena.frame % 2), playerNaked_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
      if (!helena.flickeringHelmet)sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.helmet);
      if (helena.changingHelmet && helena.flickeringHelmet) sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.nextHelmet);
      if (helena.life > HELENA_NAKED)
      {
        if (helena.weapon) sprites.drawPlusMask(helena.x + 13 + pgm_read_byte(&frameSequence[helena.frame]), helena.y  + (helena.frame % 2) + 6, playerWeapon_plus_mask, helena.weapon - 1);
        sprites.drawPlusMask(helena.x - 2 , helena.y + 4 + (helena.frame % 2), playerArmor_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
      }
      else
      {
        if (helena.weapon) sprites.drawPlusMask(helena.x + 12 + pgm_read_byte(&frameSequence[helena.frame]), helena.y  + (helena.frame % 2) + 6, playerWeapon_plus_mask, helena.weapon - 1);
      }
    }
  }
}

#endif
