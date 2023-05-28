#ifndef SPRITES_H
#define SPRITES_H

#include "../devices/video/video.h"
#include "../devices/video/VBE.h"
#include "../images/InitialMenu.xpm"
#include "../images/border.xpm"
#include "../images/ball.xpm"
#include "../images/obstacle.xpm"
#include "../images/instructionsFIrst.xpm"
#include "../images/middle.xpm"
#include "../images/hole.xpm"
#include "../images/mouse.xpm"

#define MAX_SPRITES 8


typedef struct Sprite{
    uint32_t *pixels;
    uint16_t height, width;
} Sprite;

Sprite *sprites[MAX_SPRITES];

int drawSprite(Sprite *sprite, int x, int y);

void createSpriteArr();

void cleanSpritesArr();

#endif

