#ifndef WAVES_H
#define WAVES_H

#include "globals.h"
#include "enemies.h"
#include "elements.h"

// HELPER FUNCTIONS
///////////////////
boolean checkStartWave()
{
  if (currentWave != previousWave)
  {
    previousWave = currentWave;
    return true;
  }
  return false;
}

boolean checkFlamePosition()
{
  for (byte i = 0; i < 2; i++)
  {
    if (torchFlames[i].x == 128)
    {
      torchFlames[i].isVisible = false;
      return true;
    }
  }
  return false;
}

boolean checkEndWave()
{
  byte test = 0;
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    test += bitRead(orc[i].characteristics, 7);
  }
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
  {
    test += bitRead(spike[i].characteristics, 7);
  }
  test += bitRead(badFlame.characteristics, 7);
  test += bitRead(statue.characteristics, 7);
  test += bitRead(arrow.characteristics, 7);

  if (test < 1) currentWave++;
}

void wait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    currentWave++;
    globalCounter = 0;
  }
}


// DIFFERENT WAVES
//////////////////
void wave000()
{
  wait();
}

void wave001()
{
  if (checkStartWave())
  {
    orcsSetInLine(ENEMY_ORC_NO_SPEAR, 0, 2, 128, 64);
  }
  updateOrcs();
  checkEndWave();
}

void wave002()
{
  if (checkStartWave())
  {
    orcsSetInLine(ENEMY_ORC_FLAT_SPEAR, 0, 2, 128, 64);
  }
  updateOrcs();
  checkEndWave();
}

void wave003()
{
  if (checkStartWave())
  {
    orcsSetInLine(ENEMY_ORC_UP_SPEAR, 0, 2, 128, 64);
  }
  updateOrcs();
  checkEndWave();
}

void wave004()
{
  if (checkStartWave())
  {
    orcsSetInLine(ENEMY_ORC_NO_SPEAR, 0, 0, 128, 0);
    orcsSetInLine(ENEMY_ORC_FLAT_SPEAR, 1, 1, 192, 0);
    orcsSetInLine(ENEMY_ORC_UP_SPEAR, 2, 2, 256, 0);
  }
  updateOrcs();
  checkEndWave();
}

void wave005()
{
  if (checkStartWave())
  {
    spikesSetInLine(0, 2, 128, 56);
  }
  updateSpikes();
  checkEndWave();
}

void wave006()
{
  if (checkFlamePosition())
  {
    if (checkStartWave()) badFlameSetInLine();
  }
  if (badFlame.characteristics)
  {
    updateBadFlame();
    checkEndWave();
  }
}

void wave007()
{
  if (checkStartWave())
  {
    statueSetInLine();
  }
  updateStatue();
  checkEndWave();
}


void wave255()
{
  currentWave = WAVE_TO_START_WITH;
  previousWave = 255;
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM allWaves[] =
{
  wave000,
  wave001,
  wave002,
  wave003,
  wave004,
  wave005,
  wave006,
  wave006,
  wave255,
};



#endif
