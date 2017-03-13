#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ATMlib.h>
#include "bitmaps.h"
#include "songs.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5

//define game states (on main menu)
#define STATE_GAME_PLAYING           6
#define STATE_GAME_PAUSE             7
#define STATE_GAME_OVER              8

#define GAME_TOP                     0
#define GAME_BOTTOM                  48
#define GAME_LEFT                    0
#define GAME_RIGHT                   112

#define WALKINGSPEED                 3 // lower number = higher speed

#define WAVE_TO_START_WITH           0


Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

byte gameState = STATE_MENU_INTRO;                             // start the game with the TEAM a.r.g. logo
byte globalCounter = 0;
const unsigned char PROGMEM frameSequence[4] = {0, 1, 2, 1};   // this is the frame frequence we are using for the walking animations
boolean menuX = true;
boolean menuY = false;
byte currentWave;
byte previousWave;

#endif
