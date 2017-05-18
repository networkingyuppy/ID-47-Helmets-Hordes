/*
  Helmets & Hordes: http://www.team-arg.org/HEHO-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/HEHO-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2016 - Grapple Bug - JO3RI

  License for the game CODE: MIT : https://opensource.org/licenses/MIT
  License for the game ART:
  License for the game Banner:
  License for the game idea en concept: 

*/

//determine the game
#define GAME_ID 47

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "collectables.h"
#include "elements.h"
#include "enemies.h"
#include "waves.h"
#include "collision.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}

