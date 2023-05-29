 #include "game.h"

extern int gameMode;
extern uint8_t *frame_buffer;
extern uint8_t *auxiliar_buffer;
extern vbe_mode_info_t mode_info;
extern uint16_t width;
extern uint16_t height;
extern unsigned bytesPerPixel;

extern int x;
extern int y;

extern Sprite *sprites[MAX_SPRITES];

int xBall;
int yBall;
int direction;
int xHole = 680;
int yHole = 45;


void (drawMouse)(){
    if(gameMode == GAME_MODE)
        drawSprite(sprites[7], x, y);
}

int drawGame(){
    direction = 0;
    int i = 0;
    xBall = 50;
    yBall = 550;
    while(i < mode_info.YResolution){
        if(i <= 10 || i >= (mode_info.YResolution - 11)){
            for(int j = 0; j < mode_info.XResolution; j++){
                drawSprite(sprites[2], j, i); // top/bottom wall
            }
        } else{
            for(int j = 0; j < 11; j++){ // left wall
                drawSprite(sprites[2], j, i);
            }

            int l = 11;
            while(l < mode_info.XResolution - 11){
                if((i <= 100 && (l >= 300 && l <= 380))){
                    drawSprite(sprites[4], l, i);
                } else if((i > 100 && i <= 140) && ((l >= 100 && l <= 225) || (l >= 300 && l <= 380) || (l >= 550))){
                    drawSprite(sprites[4], l, i);
                } else if((i > 140 && i <= 240) && ((l >= 100 && l <= 225) || (l >= 300 && l <= 380) || (l >= 670 && l <= 730))){
                    drawSprite(sprites[4], l, i);
                } else if((i > 240 && i <= 280) && ((l >= 100 && l <= 225) || (l >= 300 && l <= 380))){
                    drawSprite(sprites[4], l, i);
                } else if((i > 280 && i <= 340) && (l >= 100 && l <= 225)){
                    drawSprite(sprites[4], l, i);
                } else if((i > 350 && i <= 420) && ((l >= 320 && l <= 590) || (l >= 630 && l <= 740))){
                    drawSprite(sprites[4], l, i);
                } else if((i > 460 && i <= 520) && ((l <= 225) || (l >= 400 && l <= 610))){
                    drawSprite(sprites[4], l, i);
                } 
                else{
                    drawSprite(sprites[3], l, i);
                }
                l++;
            }
            
            for(int j = 0; j < 11; j++){ // right wall
                drawSprite(sprites[2], mode_info.XResolution - j - 1, i);
            }
        }
        i++;
    }
    drawSprite(sprites[5], 680, 45);
    memcpy(auxiliar_buffer,frame_buffer,width * height * bytesPerPixel);
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

void checkIfBallInHole(){
    if((xBall-xHole <=18 && xBall-xHole >=-18) && (yBall-yHole <=18 && yBall - yHole >=-18)){
        gameMode = MENU_MODE;
        memset(auxiliar_buffer, 0 ,width * height * bytesPerPixel);
    }
}

void process_tacada_MOUSE (uint8_t x,uint8_t y){
    direction++;
    if(direction==4) direction=0;
}


