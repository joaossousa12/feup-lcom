//
// Created by Bernardo on 25/05/2023.
//

#ifndef SRC_VIDEO_H
#define SRC_VIDEO_H

#include <lcom/lcf.h>
#include <math.h>
#include "VBE.h"

int (set_graphic_mode)(uint16_t submode);

int (set_frame_buffer)(uint16_t mode);

int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif //SRC_VIDEO_H
