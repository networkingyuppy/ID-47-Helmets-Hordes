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
    int x, y;
    byte life, frame, helmet, weapon;
    unsigned long score;
    char frameSequence[4];
};


Players player;

void setPlayer()
{
  player =
  {
    PLAYER_START_X, PLAYER_START_Y,                     // start position
    PLAYER_ARMOR,                                       // start life with armor
    0,                                                  // start animation at frame 0
    HELMET_NO_HELMET,                                   // start without a helmet
    WEAPON_SWORD,                                       // start with the sword
    0,                                                  // start without score ;)
    {0, 1, 2, 1},                                       // this is the frame frequence we are using for the walking animation
  };
}

void checkWeapon()
{
  
}

void drawPlayer()
{
  if (arduboy.everyXFrames(WALKINGSPEED*2)) player.frame = (++player.frame) % 4;
  if (player.weapon) sprites.drawPlusMask(player.x + 13 + player.frameSequence[player.frame], player.y  + (player.frame % 2) - 1, playerWeapon_plus_mask, player.weapon - 1);
  sprites.drawPlusMask(player.x, player.y + (player.frame % 2), playerBody_plus_mask, player.frameSequence[player.frame]);
  sprites.drawPlusMask(player.x - 4 , player.y - 16 + (player.frame % 2), playerHead_plus_mask, player.helmet);
  if (player.life > PLAYER_NAKED) sprites.drawPlusMask(player.x - 2 , player.y - 3 + (player.frame % 2), playerArmor_plus_mask, player.frameSequence[player.frame]);
}

#endif
