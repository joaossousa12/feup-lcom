#ifndef SPRITES_H
#define SPRITES_H

#include "../devices/video/video.h"
#include "../devices/video/VBE.h"
#include "../imgs/InitialMenu.xpm"

typedef struct Sprite{
    uint32_t *colors;
    uint16_t height, width;
} Sprite;

Sprite *InitialMenu;

Sprite *createSprite(xpm_map_t xpmMap);

int drawSprite(Sprite *sprite, int x, int y);

void destroy_sprite(Sprite *sprite);

void loadSprites();

void unloadSprites();

#endif
