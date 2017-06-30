#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "player.h"

void checkInputs()
{
  if (arduboy.pressed(DOWN_BUTTON));
  if (arduboy.pressed(LEFT_BUTTON));
  if (arduboy.pressed(UP_BUTTON)) gameState = STATE_MENU_MAIN;
  if (arduboy.pressed(RIGHT_BUTTON));

  if (arduboy.justPressed(A_BUTTON)) if ((helena.characteristics & 0B10000000) != 0B10000000) helena.characteristics |= 0B10000000;
  if (arduboy.justPressed(B_BUTTON)) 
  {
    helena.characteristics |= 0B01000000;
    helena.characteristics &= 0B01111111;
  }
}


#endif
