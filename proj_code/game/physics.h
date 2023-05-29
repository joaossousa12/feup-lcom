#ifndef _PHYSICS_H_
#define _PHYSICS_H_


#include <lcom/lcf.h>
#include "../devices/video/video.h"
#include "game.h"

extern vbe_mode_info_t mode_info;
int trajectory_x[160]; 
int trajectory_y[160]; 
uint8_t trajectory_indexes[160];   //stores frame_buffer indexes of pertaining to trajectory
extern unsigned bytesPerPixel;
extern uint8_t *frame_buffer;

extern int x_ball;
extern int y_ball;

double init_ball_velocity;



int set_initial_ball_state(uint16_t delta_x, uint16_t delta_y);

double findSqrt(double x);

double slope_funtion(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, uint16_t delta_y, double *b);


void trajectory_builder(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, double slope, double b, uint32_t wall_color, double init_ball_velocity);

#endif
