#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "player.h"

void checkInputs()
{
  if (arduboy.justPressed(UP_BUTTON | RIGHT_BUTTON | DOWN_BUTTON)) gameState = STATE_GAME_PAUSE;
  if (arduboy.justPressed(LEFT_BUTTON)) gameState = STATE_MENU_MAIN;

  if (arduboy.justPressed(A_BUTTON) && (helena.characteristics & 0B00000011))
  {
    if (!(helena.characteristics & 0B10000000)) setStab();
  }
  if (arduboy.justPressed(B_BUTTON))
  {
    helena.characteristics |= 0B01000000; // jump
    helena.characteristics &= 0B01111111; // no longer stab
  }
}


#endif
