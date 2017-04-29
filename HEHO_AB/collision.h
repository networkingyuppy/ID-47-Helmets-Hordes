#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"
#include "enemies.h"
#include "elements.h"
#include "player.h"

void checkCollisions()
{
  Rect helenaRect;
  if (helena.jumping)
  {
    helenaRect = {
      .x = helena.x + HELENA_COLLISION_X_OFFSET,
      .y = helena.y + HELENA_COLLISION_Y_OFFSET - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]),
      .width = HELENA_COLLISION_WIDTH,
      .height = HELENA_COLLISION_HEIGHT
    };
  }
  else
  {
    helenaRect = {
      .x = helena.x + HELENA_COLLISION_X_OFFSET,
      .y = helena.y + HELENA_COLLISION_Y_OFFSET - 9 + (helena.frame % 2),
      .width = HELENA_COLLISION_WIDTH,
      .height = HELENA_COLLISION_HEIGHT
    };
  }

  ////// Check collision weapon with enemies /////
  ////////////////////////////////////////////////

  //arduboy.collide(helenaRect,

  ////// Check collision Helena with enemies /////
  ////////////////////////////////////////////////
  Rect enemyRect;
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    enemyRect = {.x = orc[i].x + 2, .y = ORC_Y - 10 + ((orcFrames + i) % 2), .width = ORC_COLLISION_WIDTH, .height = ORC_COLLISION_HEIGHT};
    if (bitRead(orc[i].characteristics, 4) && !bitRead(orc[i].characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!helena.isImune)
      {
        helena.isImune = true;
        playerScore = 0;
        //helena.life--;
      }
      if (!bitRead(orc[i].characteristics, 6))
      {
        bitSet(orc[i].characteristics, 5);
      }
    }
  }
}





#endif
