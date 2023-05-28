
#ifndef PROJ_GAME_H
#define PROJ_GAME_H

#include <lcom/lcf.h>

#include "../devices/keyboard/i8042.h"
#include "../devices/video/video.c"
#include "../sprites/sprites.h"
#include "../devices/mouse/mouse.c"
#include "../game/physics.h"

extern int ball_pos_X;         //this x is actually X (caaps) to late to change
extern int ball_pos_y;

void drawGame();

void process_keyboard_game(uint8_t scancode);

void process_tacada_MOUSE(uint16_t delta_X, uint16_t delta_y, bool can_move, mouse_init_info mouse_state); //mouse_state has to be defined when drawing sprite

#endif //PROJ_GAME_H

