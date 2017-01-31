#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define WALKINGSPEED                               16 // lower number = higher speed

struct Players
{
  public:
    int x;
    int y;
    byte frame;
    unsigned long score; 
    boolean armor;
    byte helmet;
};

byte frameSequence[] = {0, 1, 2, 1};

Players player = { .x = 20, .y = 40, .frame = 0 };

void drawPlayer()
{
  if (arduboy.everyXFrames(WALKINGSPEED)) player.frame = (++player.frame) %4;
  sprites.drawPlusMask(player.x, player.y + (player.frame%2), playerBody_plus_mask, frameSequence[player.frame]);
  sprites.drawPlusMask(player.x-4 , player.y-16 + (player.frame%2), playerHead_plus_mask, player.helmet);
  if (player.armor) sprites.drawPlusMask(player.x-2 , player.y-3 + (player.frame%2), playerArmor_plus_mask, frameSequence[player.frame]);
}

#endif
