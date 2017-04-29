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
    helenaRect =
    {
      .x = helena.x + HELENA_COLLISION_X_OFFSET,
      .y = helena.y + HELENA_COLLISION_Y_OFFSET - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]),
      .width = HELENA_COLLISION_WIDTH,
      .height = HELENA_COLLISION_HEIGHT
    };
    arduboy.drawRect(
      helena.x + HELENA_COLLISION_X_OFFSET,
      helena.y + HELENA_COLLISION_Y_OFFSET - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]),
      HELENA_COLLISION_WIDTH,
      HELENA_COLLISION_HEIGHT,
      WHITE
    );
  }
  else
  {
    helenaRect = {
      .x = helena.x + HELENA_COLLISION_X_OFFSET,
      .y = helena.y + HELENA_COLLISION_Y_OFFSET + (helena.frame % 2),
      .width = HELENA_COLLISION_WIDTH,
      .height = HELENA_COLLISION_HEIGHT
    };
    arduboy.drawRect(
      helena.x + HELENA_COLLISION_X_OFFSET,
      helena.y + HELENA_COLLISION_Y_OFFSET + (helena.frame % 2),
      HELENA_COLLISION_WIDTH,
      HELENA_COLLISION_HEIGHT,
      WHITE
    );
  }

  ////// Check collision weapon with enemies /////
  ////////////////////////////////////////////////

  //arduboy.collide(helenaRect,

  ////// Check collision Helena with Orcs ////////
  ////////////////////////////////////////////////
  Rect enemyRect;
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    enemyRect =
    {
      .x = orc[i].x + 2,
      .y = ORC_Y - 10 + ((orcFrames + i) % 2),
      .width = ORC_COLLISION_WIDTH,
      .height = ORC_COLLISION_HEIGHT
    };
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

    if ((orc[i].characteristics & 0b00000011) == ENEMY_ORC_FLAT_SPEAR)
    {
      enemyRect =
      {
        .x = orc[i].x - 14,
        .y = ORC_Y + 3 + ((orcFrames + i) % 2),
        .width = SPEAR_F_COLLISION_WIDTH,
        .height = SPEAR_F_COLLISION_HEIGHT
      };
    }
    if ((orc[i].characteristics & 0b00000011) == ENEMY_ORC_UP_SPEAR)
    {
      enemyRect =
      {
        .x = orc[i].x,
        .y = ORC_Y - 22 + ((orcFrames + i) % 2),
        .width = SPEAR_U_COLLISION_WIDTH,
        .height = SPEAR_U_COLLISION_HEIGHT
      };
    }
    if (bitRead(orc[i].characteristics, 4) && !bitRead(orc[i].characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!helena.isImune)
      {
        helena.isImune = true;
        playerScore = 0;
        //helena.life--;
      }
    }
  }


  ////// Check collision Helena with Spikes //////
  ////////////////////////////////////////////////
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
  {
    enemyRect =
    {
      .x = spike[i].x + 3,
      .y = SPIKE_Y + 2,
      .width = SPIKE_COLLISION_WIDTH,
      .height = SPIKE_COLLISION_HEIGHT
    };
    if (bitRead(spike[i].characteristics, 4) && !bitRead(spike[i].characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!helena.isImune)
      {
        helena.isImune = true;
        playerScore = 0;
        //helena.life--;
      }
      if (!bitRead(spike[i].characteristics, 6))
      {
        bitSet(spike[i].characteristics, 5);
      }
    }
  }
  ////// Check collision Helena with Flames //////
  ////////////////////////////////////////////////
  
  enemyRect =
  {
    .x = badWalkingFlame.x,
    .y = badWalkingFlame.y,
    .width = BADWALKINGFLAME_COLLISION_WIDTH,
    .height = BADWALKINGFLAME_COLLISION_HEIGHT
  };
  
  arduboy.drawRect(
    badWalkingFlame.x,
    badWalkingFlame.y,
    BADWALKINGFLAME_COLLISION_WIDTH,
    BADWALKINGFLAME_COLLISION_HEIGHT
  );

  if (bitRead(badWalkingFlame.characteristics, 4) && !bitRead(badWalkingFlame.characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!helena.isImune)
    {
      helena.isImune = true;
      playerScore = 0;
      //helena.life--;
    }
    if (!bitRead(badWalkingFlame.characteristics, 6))
    {
      bitSet(badWalkingFlame.characteristics, 5);
    }
  }

}





#endif
