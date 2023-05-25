//
// Created by Bernardo on 24/05/2023.
//

#ifndef PROJ_INSTRUCTIONS_H
#define PROJ_INSTRUCTIONS_H

#include <lcom/lcf.h>

#include "../devices/keyboard/i8042.h"
#include "../devices/video/video.h"
#include "../sprites/sprites.h"

void drawInstructionsPage();


void process_keyboard_instructions(uint8_t scancode);


#endif //PROJ_INSTRUCTIONS_H




