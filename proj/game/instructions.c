//
// Created by Bernardo on 24/05/2023.
//

#include "instructions.h"

extern int gameMode;
extern uint8_t *frame_buffer;
extern vbe_mode_info_t mode_info;

int drawInstructionsPage(){
    memset(frame_buffer, 0xDDDDDD, mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8));
    drawSprite(instructionsFIrst, 0, 0);
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


