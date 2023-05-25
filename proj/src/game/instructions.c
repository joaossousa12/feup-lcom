//
// Created by Bernardo on 24/05/2023.
//

#include "instructions.h"
#include "../../MACROS.h"

extern int gameMode;

void process_keyboard(uint8_t scancode){
    switch (scancode) {
        case Make_ESC:
            gameMode = MENU_MODE;
            break;
        default:
            break;

    }
}

int drawInstructionsPage(){
    copyDrawingToBuffer();
    return 0;
}
