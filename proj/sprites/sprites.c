#include "sprites.h"

extern int gameMode;
extern int x;
extern int y;
extern uint8_t *imageBuffer;
extern uint16_t xRes, yRes;
extern unsigned BytesPerPixel;
extern char word[24];

Sprite *createSprite(xpm_map_t sprite){
    Sprite *sprite (Sprite *) malloc (sizeof(Sprite));
    if(sprite == NULL) return NULL;

    xpm_map_t image;
    sprite->colors = (uint32_t *) xpm_load(sprite, XPM888, &image); // falta definir funºão xpm_load e macro XPM888
    sprite->height = image.height;
    sprite->width = image.width;

    if(sprite->colors == NULL){
        free(sprite); //TODO
        return NULL;
    }

    return sprite;
}

int drawSprite(Sprite *sprite, int x, int y){ 
    uint16_t height = sprite->height, width = sprite->width;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        if (draw_pixel(x + w, y + h, sprite->colors[w + h*width], &imageBuffer)) return 1;
      }
    }
    return 0; 
}

void loadSprites(){
  gameTitle = createSprite((xpm_map_t) title_xpm);
}

void unloadSprites(){
  destroy_sprite(gameTitle);
}