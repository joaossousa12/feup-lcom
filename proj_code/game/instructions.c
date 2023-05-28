//
// Created by Bernardo on 24/05/2023.
//

#include "instructions.h"
#include "../MACROS.h"
#include "../devices/keyboard/i8042.h"

extern int gameMode;

int drawInstructionsPage(){
    drawSprite(instructionsFirst,0,0);
    return 0;
}

void process_keyboard_instructions(uint8_t scancode){
    switch (scancode) {
        case MAKE_ESC:
            gameMode = MENU_MODE;
            break;
        default:
            break;

    }
}


