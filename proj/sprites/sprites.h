#ifndef SPRITES_H
#define SPRITES_H

#include "../devices/video/video.h"
#include "../imgs/title.xpm"



typedef struct Sprite{
    uint32_t *colors;
    uint16_t height, width;
} Sprite;

Sprite *gameTitle;

Sprite *createSprite(xpm_map_t sprite);

int drawSprite(Sprite *sprite, int x, int y);

void destroy_sprite(Sprite *sprite);

void loadSprites();

void unloadSprites();

#endif

