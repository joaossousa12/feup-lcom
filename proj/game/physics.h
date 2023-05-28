#ifndef _PHYSICS_H_
#define _PHYSICS_H_


#include <lcom/lcf.h>

extern vbe_mode_info_t mode_info;
int trajectory_x[]; //deprecate this
int trajectory_y[]; //deprecate this
uint8_t trajectory_indexes[160];   //stores frame_buffer indexes of pertaining to trajectory
extern unsigned bytesPerPixel;


/*
Falta testar todas as  funcionalidades
Falta fazer uma funçao de atrito
*/
// funcao para colisao talvez seja necessaria, ou entao voltar a chamar a displacent com o valor de power e de angulo ajustado na direcao da reflexao

extern int ball_pos_X;         //this x is actually X (caaps) to late to change
extern int ball_pos_y;

double ball_velocity;
double x_ball_velocity = 0;
double y_ball_velocity = 0;
double init_ball_velocity = 0;
double init_x_ball_velocity = 0;
double init_y_ball_velocity = 0;
double ball_angle = 0;
int ball_dir_x = 1;
int ball_dir_y = 1;
float ball_friction = 0.01;

int velocity(double distance);


int set_initial_ball_state(uint16_t delta_x, uint16_t delta_y, bool can_move);

int ball_in_motion(double time, bool can_move);


int colision_detector(int x_target, int y_target, uint32_t wall_color, uint8_t *frame_buffer);

double angle_finder(int x_object, int y_object, int x_mouse, int y_mouse, int power);

int force(int aceleration, int ball_mass);

int diplacement(int *x_object, int *y_object, double angle, int aceleration);

int friction(uint32_t color, int x_object, int y_object);

double findSqrt(double x);

double slope_funtion(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, uint16_t delta_y, double *b);


int trajectory_builder(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, double slope, double b, uint32_t wall_color, double init_ball_velocity, uint8_t *frame_buffer);

#endif

