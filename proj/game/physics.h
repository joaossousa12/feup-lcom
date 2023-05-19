#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <math.h>
#include <lcom/lcf.h>
/*
Falta testar todas as  funcionalidades
Falta fazer uma funçao de atrito
*/
// funcao para colisao talvez seja necessaria, ou entao voltar a chamar a displacent com o valor de power e de angulo ajustado na direcao da reflexao

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

