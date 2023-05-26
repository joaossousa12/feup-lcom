#include "sprites.h"
#include "stdlib.h"

extern int gameMode;
extern int x;
extern int y;
extern char word[24];

Sprite *createSprite(xpm_map_t xpmMap){
    Sprite *sprite = (Sprite *) malloc (sizeof(Sprite));
    if(sprite == NULL) return NULL;

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

    free(sprite);
    sprite = NULL;
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
  instructionsFIrst = createSprite((xpm_map_t) instructionsFIrst_xpm);
  border = createSprite((xpm_map_t) border_xpm);
  middle = createSprite((xpm_map_t) middle_xpm);
  obstacle = createSprite((xpm_map_t) obstacle_xpm);
  hole = createSprite((xpm_map_t) hole_xpm);
  ball = createSprite((xpm_map_t) ball_xpm);
}

void unloadSprites(){
  destroy_sprite(InitialMenu);
  destroy_sprite(instructionsFIrst);
  destroy_sprite(border);
  destroy_sprite(middle);
  destroy_sprite(obstacle);
  destroy_sprite(hole);
  destroy_sprite(ball);
}
