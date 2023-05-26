#include "menu.h"

extern uint8_t *frame_buffer;
extern vbe_mode_info_t mode_info;

int drawMenu(){
    memset(frame_buffer, 0xDDDDDD, mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8));
    drawSprite(InitialMenu, 0, 0);
    return 0;
}

void process_keyboard_menu(uint8_t scancode){

}



