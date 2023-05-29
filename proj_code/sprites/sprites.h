/**
 * @file sprites
 * 
 * @brief This file defines the structure and functions related to sprites in a graphical user interface.
 * 
 * @author João Pedro Sousa, Bernardo Pinto, Carlos Madaleno
 * 
 * @date 28/05/2023
*/

#ifndef SPRITES_H
#define SPRITES_H

#include "../devices/video/video.h"
#include "../devices/video/VBE.h"
<<<<<<< HEAD
#include "../imgs/InitialMenu.xpm"
#include "../imgs/border.xpm"
#include "../imgs/ball.xpm"
#include "../imgs/obstacle.xpm"
#include "../imgs/instructionsFIrst.xpm"
#include "../imgs/middle.xpm"
#include "../imgs/hole.xpm"
#include "../imgs/mouse.xpm"
=======

#include "../images/InitialMenu.xpm"
#include "../images/border.xpm"
#include "../images/ball.xpm"
#include "../images/obstacle.xpm"
#include "../images/instructionsFIrst.xpm"
#include "../images/middle.xpm"
#include "../images/hole.xpm"
#include "../images/mouse.xpm"

#define MAX_SPRITES 8
>>>>>>> 89413b28e9ef45364418a97d373bd3a8ba9808a8

typedef struct Sprite{
    uint32_t *colors;
    uint16_t height, width;
} Sprite;

<<<<<<< HEAD
Sprite *InitialMenu;
Sprite *instructionsFirst;
Sprite *border;
Sprite *middle;
Sprite *obstacle;
Sprite *hole;
Sprite *ball;
Sprite *mouse;

Sprite *createSprite(xpm_map_t xpmMap);

int drawSprite(Sprite *sprite, int x, int y);

void destroy_sprite(Sprite *sprite);

void loadSprites();

void unloadSprites();
=======
Sprite *sprites[MAX_SPRITES]; // sprite's array

/**
 * @brief Draws a sprite on the screen.
 * 
 * @param sprite Pointer to the sprite structure containing the sprite data.
 * 
 * @param x The x-coordinate of the top-left corner of the sprite on the screen.
 * 
 * @param y The y-coordinate of the top-left corner of the sprite on the screen.
 * 
 * @return 0 on success, non-zero if there was an error drawing the sprite.
*/

int drawSprite(Sprite *sprite, int x, int y);

/**
 * @brief Create the sprites and store them on the array.
*/

void createSpriteArr();

/**
 * @brief Cleans up the array of sprites.
*/

void cleanSpritesArr();
>>>>>>> 89413b28e9ef45364418a97d373bd3a8ba9808a8

#endif

