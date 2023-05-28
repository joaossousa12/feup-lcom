//
// Created by Bernardo on 17/05/2023.
//

#ifndef PROJ_MENU_H
#define PROJ_MENU_H

#include <lcom/lcf.h>
#include <stdio.h>
#include <string.h>

#include "../devices/keyboard/i8042.h"
#include "../devices/video/video.h"
#include "../sprites/sprites.h"
#include "../devices/mouse/mouse.h"
#include "../MACROS.h"
#include "game.h"

int drawMenu();

void process_keyboard_menu(uint8_t scancode);

#endif //PROJ_MENU_H
