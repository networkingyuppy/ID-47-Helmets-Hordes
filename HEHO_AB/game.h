#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "collectables.h"
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
  setBadWalkingFlame();
  setBadWeed();

  setGoldBars();
  currentWave = WAVE_TO_START_WITH;
  previousWave = 255;
  globalCounter = 0;
  scorePlayer = 0;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  checkInputs();

  updateHelena();

  ((FunctionPointer) pgm_read_word (&allWaves[currentWave]))();
  
  drawBricks();
  drawBadWeed();
  drawFloorWeed();
  drawFloorPart();
  drawSpikes();
  //drawFloorWeed();


  //drawBricks();
  drawTorchHandles();
  drawTorchFlames();
  drawGoldBars();
  drawBadFlame();
  drawBadWalkingFlame();

  drawOrcs();
  drawStatueFront();
  drawArrows();
  drawStatueBack();

  drawHelena();
  drawChains();
  drawScore(2, 48);
  scorePlayer++;
};

void stateGamePause()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{

};



#endif
