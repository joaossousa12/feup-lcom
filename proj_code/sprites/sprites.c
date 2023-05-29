#include "sprites.h"
#include "stdlib.h"

extern int gameMode;
extern int x;
extern int y;
extern char word[24];

<<<<<<< HEAD
Sprite *createSprite(xpm_map_t xpmMap){
    Sprite *sprite = (Sprite *) malloc (sizeof(Sprite));
    if(sprite == NULL) return NULL;
=======
void createSpriteArr(){
    char **fileNames[MAX_SPRITES] = { InitialMenu_xpm, instructionsFIrst_xpm, border_xpm, middle_xpm, obstacle_xpm, hole_xpm, ball_xpm, mouse_xpm};
    
    for(int i=0; i < MAX_SPRITES; i++){
        Sprite *s = (Sprite *) malloc (sizeof(Sprite));
        if(s == NULL) continue;
>>>>>>> 89413b28e9ef45364418a97d373bd3a8ba9808a8

    xpm_image_t image;
    sprite->colors = (uint32_t *) xpm_load(xpmMap, XPM_8_8_8_8, &image);
    sprite->height = image.height;
    sprite->width = image.width;

    if(sprite->colors == NULL){
        free(sprite);
        return NULL;
    }

    return sprite;
}

void destroy_sprite(Sprite *sprite){
    if(sprite == NULL) return;
    else if(sprite->colors) free(sprite->colors);

<<<<<<< HEAD
    free(sprite);
    sprite = NULL;
=======
        free(sprites[i]);

        sprites[i] = NULL;
    }
>>>>>>> 89413b28e9ef45364418a97d373bd3a8ba9808a8
}


int drawSprite(Sprite *sprite, int x, int y){
    uint16_t height = sprite->height, width = sprite->width;

    for (int h = 0 ; h < height ; h++) {
        for (int w = 0 ; w < width ; w++) {
            if (draw_pixel(x + w, y + h, sprite->colors[w + h*width])) return 1;
        }
    }

    return 0; 
}

void loadSprites(){
    InitialMenu = createSprite((xpm_map_t) InitialMenu_xpm);
    instructionsFirst = createSprite((xpm_map_t) instructionsFIrst_xpm);
    border = createSprite((xpm_map_t) border_xpm);
    middle = createSprite((xpm_map_t) middle_xpm);
    obstacle = createSprite((xpm_map_t) obstacle_xpm);
    hole = createSprite((xpm_map_t) hole_xpm);
    ball = createSprite((xpm_map_t) ball_xpm);
    mouse = createSprite((xpm_map_t) mouse_xpm);
}

void unloadSprites(){
    destroy_sprite(InitialMenu);
    destroy_sprite(instructionsFirst);
    destroy_sprite(border);
    destroy_sprite(middle);
    destroy_sprite(obstacle);
    destroy_sprite(hole);
    destroy_sprite(ball);
    destroy_sprite(mouse);
}
