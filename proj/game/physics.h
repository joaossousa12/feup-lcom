#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <math.h>
#include <lcom/lcf.h>

/*
Falta testar todas as  funcionalidades
Falta fazer uma funçao de atrito
*/
// funcao para colisao talvez seja necessaria, ou entao voltar a chamar a displacent com o valor de power e de angulo ajustado na direcao da reflexao

int ball_pos_X;         //this x is actually X (caaps) to late to change
int ball_pos_y;
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

int velocity(double distance){
    int velocity;
    //To Implement
    return velocity;
}

 
int set_initial_ball_state(int init_mouse_x, int init_mouse_y, int final_mouse_x, int final_mouse_y, bool can_move){ //ou ang
    if(!can_move) return 1;

    x_ball_velocity = (final_mouse_x - init_mouse_x) / -150;
    init_x_ball_velocity = x_ball_velocity;
    y_ball_velocity = (final_mouse_y - init_mouse_y) / -150;
    init_y_ball_velocity = y_ball_velocity;
    ball_velocity = sqrt(pow(abs(final_mouse_x - init_mouse_x), 2) + pow(abs(final_mouse_y - init_mouse_y), 2));
    init_ball_velocity = ball_velocity;

    float angle = atan2(y_ball_velocity, x_ball_velocity) * (180 / 3.1415) + 90;
    int direction_x = x_ball_velocity /fabs(x_ball_velocity);
    int direction_y = y_ball_velocity / fabs(y_ball_velocity);

    /*if mouse is pressed and ball can move
        i have to make or calculate ratios from position of the the first click and when its unclicked 
        given that the ball and the click are diff

        solution make the person click the ball and calculate the distance to the upressed
    */
    /*
    if(force < 0) return -1;
    if(x == NULL) return -1;
    if(y == NULL) return -1;
    if((angle > 2 * PI) || (angle < 0)) return -1;

    int x_target = aceleration * angle + *x_object;  // dont seem right serves as placeholder  falta friction
    int y_target = aceleration * angle + *y_object;

    *x_object = x_target; // - friction
    *y_object = y_target;
    */
    return 0;

}

int ball_in_motion(double time, bool can_move){
    if(can_move) return 1;

    ball_pos_X = ball_pos_X + x_ball_velocity * time;
    ball_pos_y = ball_pos_y + y_ball_velocity * time;

    if(x_ball_velocity > 0.001 || x_ball_velocity < -0.001 || y_ball_velocity > 0.001 || y_ball_velocity < -0.001){
        if(ball_velocity > 0){
            ball_velocity = ball_velocity - ball_friction * time;
        }else{
            ball_velocity = 0;
        }
        x_ball_velocity = (ball_velocity / init_ball_velocity) * fabs(x_ball_velocity) * ball_dir_x;
        y_ball_velocity = (ball_velocity / init_ball_velocity) * fabs(y_ball_velocity) * ball_dir_y; 
    }else{
        ball_velocity = 0;
        x_ball_velocity = 0;
        y_ball_velocity = 0;
        //set can move to true
    }
}


int colision_detector(int x_target, int y_target, uint32_t wall_color, uint8_t *frame_buffer){     //Can pass an array with all the walls or verify color of the wall, Tests wether the next position creates a colision
    if(x_target >= mode_info.XResolution || y_target >= mode_info.YResolution) return 0;

    unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;
    unsigned int index = (mode_info.XResolution * y_target + x_target) * BytesPerPixel;
    
    if(frame_buffer[index] == wall_color) return 0; //Check color of pixel
    
    return 1;
}

double angle_finder(int x_object, int y_object, int x_mouse, int y_mouse, int power){
    double gradient_object = y_object / x_object;
    double gradient_mouse = y_mouse / x_mouse;

    double tangent = (gradient_object + gradient_mouse) / (1 + gradient_object * gradient_mouse);

    return atan(tangent);
}

int force(int aceleration, int ball_mass){
    if(user_input < 0 || user_input > 80) return -1;
    return ball_mass * aceleration;
}

int diplacement(int *x_object, int *y_object, double angle, int aceleration){ //ou angle
    if(force < 0) return -1;
    if(x == NULL) return -1;
    if(y == NULL) return -1;
    if((angle > 2 * PI) || (angle < 0)) return -1;

    int x_target = aceleration * angle + *x_object;  // dont seem right serves as placeholder  falta friction
    int y_target = aceleration * angle + *y_object;

    *x_object = x_target; // - friction
    *y_object = y_target;

    return 0;

}

int friction(uint32_t color, int x_object, int y_object){
    if(x_target >= mode_info.XResolution || y_target >= mode_info.YResolution) return 0;

    unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;
    unsigned int index = (mode_info.XResolution * y_target + x_target) * BytesPerPixel;
}





#endif

