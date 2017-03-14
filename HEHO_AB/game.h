#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "waves.h"

void stateMenuPlay()
{
  setHelena();
  setFloorPart();
  setFLoorWeed();
  setSpikes();
  setOrcs();
  setChains();
  setBricks();
  setTorchHandles();
  setTorchFlames();
  setBadFlame();
  
  setGoldBarsRow();
  currentWave = WAVE_TO_START_WITH;
  previousWave = 255;
  globalCounter = 0;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  checkInputs();

  updateHelena();

  ((FunctionPointer) pgm_read_word (&allWaves[currentWave]))();

  drawFloorPart();
  drawSpikes();
  drawFloorWeed();
  

  drawBricks();
  drawTorchHandles();
  drawTorchFlames();
  drawBadFlame();
  //drawGoldBars();

  drawOrcs();
  drawHelena();
  drawChains();
};

void stateGamePause()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{

};



#endif
