#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"
#include "enemies.h"
#include "elements.h"
#include "player.h"

void checkCollisions()
{
  Rect helenaRect;
  helenaRect = {
    .x = helena.x + HELENA_COLLISION_X_OFFSET,
    .y = 0,
    .width = HELENA_COLLISION_WIDTH,
    .height = HELENA_COLLISION_HEIGHT
  };
  if (helena.jumping) helenaRect.y = helena.y + HELENA_COLLISION_Y_OFFSET - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]);
  else helenaRect.y = helena.y + HELENA_COLLISION_Y_OFFSET + (helena.frame % 2);

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
      .x = spike[i].x + 4,
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
    .x = badWalkingFlame.x + 2,
    .y = badWalkingFlame.y + 4,
    .width = BADFLAME_COLLISION_WIDTH,
    .height = BADFLAME_COLLISION_HEIGHT
  };

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

  enemyRect =
  {
    .x = badFlame.x + 2,
    .y = badFlame.y + 4,
    .width = BADFLAME_COLLISION_WIDTH,
    .height = BADFLAME_COLLISION_HEIGHT
  };
  if (bitRead(badFlame.characteristics, 4) && !bitRead(badFlame.characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!helena.isImune)
    {
      helena.isImune = true;
      playerScore = 0;
      //helena.life--;
    }
    if (!bitRead(badFlame.characteristics, 6))
    {
      bitSet(badFlame.characteristics, 5);
    }
  }
  ////// Check collision Helena with Statue //////
  ////////////////////////////////////////////////
  enemyRect =
  {
    .x = statue.x,
    .y = STATUE_Y,
    .width = STATUE_COLLISION_WIDTH,
    .height = STATUE_COLLISION_HEIGHT
  };
  if (bitRead(statue.characteristics, 4) && !bitRead(statue.characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!helena.isImune)
    {
      //helena.isImune = true;
      helena.x--;
    }
    if (!bitRead(statue.characteristics, 6))
    {
      bitSet(statue.characteristics, 5);
    }
  }

  enemyRect =
  {
    .x = arrow.x,
    .y = ARROW_Y,
    .width = ARROW_COLLISION_WIDTH,
    .height = ARROW_COLLISION_HEIGHT
  };
  if (bitRead(arrow.characteristics, 4) && !bitRead(arrow.characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!helena.isImune)
    {
      helena.isImune = true;
      playerScore = 0;
      //helena.life--;
    }
    if (!bitRead(arrow.characteristics, 6))
    {
      bitSet(arrow.characteristics, 5);
    }
  }
  ////// Check collision Helena with Weed //////
  //////////////////////////////////////////////
  enemyRect =
  {
    .x = badWeed.x + 2,
    .y = badWeed.y + 8,
    .width = BADWEED_COLLISION_WIDTH,
    .height = BADWEED_COLLISION_HEIGHT
  };

  if (bitRead(badWeed.characteristics, 4) && !bitRead(badWeed.characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
  {
    if (!helena.isImune)
    {
      helena.isImune = true;
      playerScore = 0;
      //helena.life--;
    }
    if (!bitRead(badWeed.characteristics, 6))
    {
      bitSet(badWeed.characteristics, 5);
    }
  }
  ////// Check collision Helena with goldbars //////
  //////////////////////////////////////////////////
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    enemyRect =
    {
      .x = goldBar[i].x - 2,
      .y = goldBar[i].y - 2,
      .width = GOLDBAR_COLLISION_WIDTH,
      .height = GOLDBAR_COLLISION_HEIGHT
    };
    if (bitRead(goldBar[i].characteristics, 4) && !bitRead(goldBar[i].characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
    {
      if (!helena.isImune)
      {
        playerScore += 200;
        goldBar[i].characteristics = 0;
      }
    }
  }

  //// Check collision Helena with secret chest ////
  //////////////////////////////////////////////////
  enemyRect =
  {
    .x = secretChest.x,
    .y = secretChest.y,
    .width = SECRET_CHEST_COLLISION_WIDTH,
    .height = SECRET_CHEST_COLLISION_HEIGHT,
  };
  if (bitRead(secretChest.characteristics, 4) && !bitRead(secretChest.characteristics, 5) && arduboy.collide(helenaRect, enemyRect))
  {
    playerScore +=500;
    helena.nextHelmet = (secretChest.characteristics & 0b00000111);
    secretChest.characteristics = 0;
    helena.changingHelmet = true;
  }



  // end of collision detection
}





#endif
