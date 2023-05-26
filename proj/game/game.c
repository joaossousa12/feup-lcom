#include "game.h"

extern uint8_t *frame_buffer;
extern vbe_mode_info_t mode_info;

int drawGame(){
    memset(frame_buffer, 0xDDDDDD, mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8));
    for(int i = 0; i < mode_info.YResolution; i++){
        if(i <= 10 || i >= (mode_info.YResolution - 11)){
            for(int j = 0; j < mode_info.XResolution; j++){
                drawSprite(border, j, i);
            }
        } else{
            for(int j = 0; j < 11; j++){
                drawSprite(border, j, i);
            }
            for(int j = 11; j < mode_info.XResolution - 11; j++){
                drawSprite(middle, j, i);
            }
            for(int j = 0; j < 11; j++){
                drawSprite(border, mode_info.XResolution - j - 1, i);
            }
        }
    }
    return 0;
}

void process_keyboard_game(uint8_t scancode){

}

void process_tacada_MOUSE (uint8_t x,uint8_t y){

}

