#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "player.h"

void checkInputs()
{
  if (arduboy.pressed(DOWN_BUTTON));
  if (arduboy.pressed(LEFT_BUTTON));
  if (arduboy.pressed(UP_BUTTON));
  if (arduboy.pressed(RIGHT_BUTTON));

  if (arduboy.justPressed(A_BUTTON)) player.armor = !player.armor;
  if (arduboy.justPressed(B_BUTTON)) player.helmet = (++player.helmet) %8;
}


#endif
