
#ifndef PROJ_GAME_H
#define PROJ_GAME_H

#include <lcom/lcf.h>

#include "../devices/keyboard/i8042.h"
#include "../devices/video/video.c"
#include "../sprites/sprites.h"
#include "../devices/mouse/mouse.c"

void drawGame();

void process_keyboard_game(uint8_t scancode);

void process_tacada_MOUSE(uint16_t delta_X, uint16_t delta_y);

#endif //PROJ_GAME_H

