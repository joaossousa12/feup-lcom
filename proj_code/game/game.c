#include "game.h"

extern int gameMode;
extern uint8_t *frame_buffer;
extern vbe_mode_info_t mode_info;

extern int x;
extern int y;

void (drawMouse)(){
    if(gameMode == GAME_MODE)
        drawSprite(mouse, x, y);
}

int drawGame(){
    int i = 0;
    while(i < mode_info.YResolution){
        if(i <= 10 || i >= (mode_info.YResolution - 11)){
            for(int j = 0; j < mode_info.XResolution; j++){
                drawSprite(border, j, i); // top/bottom wall
            }
        } else{
            for(int j = 0; j < 11; j++){ // left wall
                drawSprite(border, j, i);
            }

            int l = 11;
            while(l < mode_info.XResolution - 11){
                if((i <= 100 && (l >= 300 && l <= 380))){
                    drawSprite(obstacle, l, i);
                } else if((i > 100 && i <= 140) && ((l >= 100 && l <= 225) || (l >= 300 && l <= 380) || (l >= 550))){
                    drawSprite(obstacle, l, i);
                } else if((i > 140 && i <= 240) && ((l >= 100 && l <= 225) || (l >= 300 && l <= 380) || (l >= 670 && l <= 730))){
                    drawSprite(obstacle, l, i);
                } else if((i > 240 && i <= 280) && ((l >= 100 && l <= 225) || (l >= 300 && l <= 380))){
                    drawSprite(obstacle, l, i);
                } else if((i > 280 && i <= 340) && (l >= 100 && l <= 225)){
                    drawSprite(obstacle, l, i);
                } else if((i > 350 && i <= 420) && ((l >= 320 && l <= 590) || (l >= 630 && l <= 740))){
                    drawSprite(obstacle, l, i);
                } else if((i > 460 && i <= 520) && ((l <= 225) || (l >= 400 && l <= 610))){
                    drawSprite(obstacle, l, i);
                } 
                else{
                    drawSprite(middle, l, i);
                }
                l++;
            }
            
            for(int j = 0; j < 11; j++){ // right wall
                drawSprite(border, mode_info.XResolution - j - 1, i);
            }
        }
        i++;
    }
    drawSprite(hole, 680, 45);
    drawSprite(ball, 50, 550);
    return 0;
}

void process_keyboard_game(uint8_t scancode){
    switch (scancode) {
        case MAKE_ESC:
            gameMode = MENU_MODE;
            break;
        default:
            break;

    }
}

void process_tacada_MOUSE (uint8_t x,uint8_t y){

}


