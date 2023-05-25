#ifndef _MAP_H_
#define _MAP_H_

#include <lcom/lcf.h>
#include "video.c"

int draw_map_border(uint8_t *frame_buffer, uint32_t wall_color){
    if(frame_buffer == NULL) return 1;

    return draw_rectangle(0, 0, mode_info.XResolution - 1, mode_info.YResolution - 1, wall_color, frame_buffer); //draws overall borders according to framebuffer resolution
}

int draw_tutorial_map(uint8_t *frame_buffer, uint32_t wall_color){
    if(frame_buffer == NULL) return 1;
    if(draw_map_border(frame_buffer, wall_color) != 0) return 1;
    // begin drawing map1

    if(draw_vertical_line(349, 20, 499, wall_color, frame_buffer) != 0) return 1;
    if(draw_vertical_line(449, 20, 499, wall_color, frame_buffer) != 0) return 1;
    if(draw_line(349, 20, 100, wall_color, frame_buffer) != 0) return 1;

    return 0;

}




#endif

