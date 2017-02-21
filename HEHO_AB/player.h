#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define PLAYER_START_X                             20
#define PLAYER_START_Y                             40

#define PLAYER_DEAD                                 0
#define PLAYER_NAKED                                1
#define PLAYER_ARMOR                                2
#define PLAYER_HELMET                               3

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

struct Players
{
  public:
    int x, y;
    byte life, frame, helmet, weapon;
    unsigned long score;
    boolean isVisible;
    boolean isImune;
};


Players helena;

void setHelena()
{
  helena =
  {
    PLAYER_START_X, PLAYER_START_Y,                     // start position
    PLAYER_ARMOR,                                       // start life with armor
    0,                                                  // start animation at frame 0
    HELMET_NO_HELMET,                                   // start without a helmet
    WEAPON_SWORD,                                       // start with the sword
    0,                                                  // start without score ;)
    true,                                               // start with the player visible (used to make her blink)
    true,                                               // start with the player being imune for a short while
  };
}

void checkWeapon()
{

}

void updateHelena()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) helena.frame = (++helena.frame) % 4;
}

void drawHelena()
{
  if (helena.isVisible) {
    if (helena.weapon) sprites.drawPlusMask(helena.x + 13 + frameSequence[helena.frame], helena.y  + (helena.frame % 2) - 1, playerWeapon_plus_mask, helena.weapon - 1);
    sprites.drawPlusMask(helena.x, helena.y + (helena.frame % 2), playerBody_plus_mask, frameSequence[helena.frame]);
    sprites.drawPlusMask(helena.x - 4 , helena.y - 16 + (helena.frame % 2), playerHead_plus_mask, helena.helmet);
    if (helena.life > PLAYER_NAKED) sprites.drawPlusMask(helena.x - 2 , helena.y - 3 + (helena.frame % 2), playerArmor_plus_mask, frameSequence[helena.frame]);
  }
}

#endif
