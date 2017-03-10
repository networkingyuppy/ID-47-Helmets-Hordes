#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"

void stateMenuPlay()
{
  setHelena();
  setFloorPart();
  setEnemies();
  setChains();
  setBricks();
  setTorchHandles();
  setTorchFlames();
  setGoldBarsRow();
  gameState = STATE_GAME_NEXT_LEVEL;
};


void stateGameNextLevel()
{
  level++;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  checkInputs();
  
  updateOrcs();
  updateHelena();

  drawBricks();
  drawTorchHandles();
  drawTorchFlames();
  drawGoldBars();
  drawFloor();
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
