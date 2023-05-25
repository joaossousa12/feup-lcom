//
// Created by Bernardo on 24/05/2023.
//

#ifndef PROJ_INSTRUCTIONS_H
#define PROJ_INSTRUCTIONS_H

#include <lcom/lcf.h>

#include "../devices/keyboard/i8042.h"
#include "../devices/video/video.c"
#include "../sprites/sprites.h"

void drawIntructionsPage();


void process_keyboard(uint8_t scancode);


#endif //PROJ_INSTRUCTIONS_H
