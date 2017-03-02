#ifndef MENU_H
#define MENU_H

#include "globals.h"

const unsigned char PROGMEM sparkleFrameSequence[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5};
byte sparkleFrame = 0;


void titleScreen()
{
  sprites.drawSelfMasked(2, 0, titleName, 0);
  for (byte i = 0; i < 3; i++) sprites.drawSelfMasked(1 + (i * 42), 24, titleImage, i);
}


void showSparkles()
{
  if (arduboy.everyXFrames(6))sparkleFrame++;
  sprites.drawPlusMask((22 - (9 * menuY)) + (menuX * (61 + (menuY * 18))), 28 + (menuY * 11), effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 9) % 15]));
  sprites.drawPlusMask((26 - (9 * menuY)) + (menuX * (61 + (menuY * 18))), 36 + (menuY * 11), effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 15) % 15]));
  sprites.drawPlusMask((30 - (9 * menuY)) + (menuX * (61 + (menuY * 18))), 28 + (menuY * 11), effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 3) % 15]));
  sprites.drawPlusMask((34 - (9 * menuY)) + (menuX * (61 + (menuY * 18))), 36 + (menuY * 11), effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 6) % 15]));
  sprites.drawPlusMask((38 - (9 * menuY)) + (menuX * (61 + (menuY * 18))), 28 + (menuY * 11), effectShine_plus_mask, pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + 12) % 15]));
}

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  titleScreen();

  for (byte k = 0; k < 2; k++)
  {
    for (byte j = 0; j < 2; j++)
    {
      sprites.drawSelfMasked((24 - (9 * k)) + (j * (61 + (k * 18))), 34 + (k * 11), titleMenu, j + (2 * k));
    }
  }

  //sprites.drawPlusMask((22 - (9 * menuY)) + (menuX * (61 + (menuY * 18))), 32 + (menuY * 11), bubbles_plus_mask, blingBlingFrame);
  showSparkles();
  if (arduboy.justPressed(RIGHT_BUTTON) && (!menuX)) menuX = !menuX;
  if (arduboy.justPressed(LEFT_BUTTON) && (menuX)) menuX = !menuX;
  if (arduboy.justPressed(DOWN_BUTTON) && (!menuY)) menuY = !menuY;
  if (arduboy.justPressed(UP_BUTTON) && (menuY)) menuY = !menuY;
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = 2 + menuX + (2 * menuY);
}

void stateMenuHelp()
{
  sprites.drawSelfMasked(32, 0, qrcode, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}


void stateMenuInfo()
{
  sprites.drawSelfMasked(16, 36, info, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  titleScreen();
  for (byte k = 0; k < 2; k++)
  {
    for (byte j = 0; j < 2; j++)
    {
      sprites.drawSelfMasked((24 - (9 * k)) + (j * (61 + (k * 18))), 34 + (k * 11), soundMenu, j + (2 * k));
    }
  }
  //sprites.drawPlusMask((22 - (9 * arduboy.audio.enabled())) + (61 + (arduboy.audio.enabled() * 18)), 32 + (arduboy.audio.enabled() * 11), bubbles_plus_mask, blingBlingFrame);
  if (arduboy.justPressed(RIGHT_BUTTON | DOWN_BUTTON)) arduboy.audio.on();
  if (arduboy.justPressed(LEFT_BUTTON | UP_BUTTON)) arduboy.audio.off();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
}


#endif
