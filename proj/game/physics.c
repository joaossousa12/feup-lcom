#include "physics.h"

int velocity(double distance){
    int velocity;
    //To Implement
    return velocity;
}

int set_initial_ball_state(uint16_t delta_x, uint16_t delta_y, bool can_move){ //ou ang
    if(!can_move) return 1;

    double slope;
    double b;
    unsigned int index;

    init_ball_velocity = findSqrt((delta_x * delta_x) + (delta_y * delta_y));
    ball_velocity = init_ball_velocity;

    if(delta_x == 0){                       ///// FALTA TRATAR DE COLICOES
        //altera so o y mantem o x
        //talvez fazer uma funcao direction select para saber se é para a esquerda ou direita ou alterar funçoes existentes
        for(int i = 1; i <= init_ball_velocity; i++){
            if(delta_y < 0){
                index = (mode_info.XResolution * (ball_pos_y + i) + ball_pos_X * BytesPerPixel); //do i need to check bounds? need to add bytes per pix
            } else if(delta_y > 0){
                index = (mode_info.XResolution * (ball_pos_y - i) + ball_pos_X * BytesPerPixel); //do i need to check bounds?

            }
            trajectory_indexes[i - 1] = index;
        }
    }else if(delta_y == 0){                 ///// FALTA TRATAR DE COLICOES
        //altera so o x mantem o y
        //talvez fazer uma funcao direction select para saber se é para a esquerda ou direita ou alterar funcoes existentes
        for(int i = 1; i <= init_ball_velocity; i++){
            if(delta_x < 0){
                index = (mode_info.XResolution * ball_pos_y + (ball_pos_X + i) * BytesPerPixel); //do i need to check bounds?
            } else if(delta_y > 0){
                index = (mode_info.XResolution * ball_pos_y - (ball_pos_X - i) * BytesPerPixel); //do i need to check bounds?

            }
            trajectory_indexes[i - 1] = index;
        }

    }else{
        slope = slope_funtion(ball_pos_X, ball_pos_y, delta_x, delta_y, &b); // já vai popular o array
    }


    if(init_ball_velocity > 150)
   

    for(int i = 0;)



        /*if mouse is pressed and ball can move
            i have to make or calculate ratios from position of the the first click and when its unclicked
            given that the ball and the click are diff

            solution make the person click the ball and calculate the distance to the upressed
        */
        return 0;

}


int ball_in_motion(double time, bool can_move){
    
    
    
    
    
    
    
    /*
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
    */
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

double findSqrt(double x)
{
    if (x < 2)
        return x;

    double y = x;
    double z = (y + (x / y)) / 2;

    // as we want to get upto 5 decimal digits, the absolute
    // difference should not exceed 0.00001
    double absolute_assert = y - z;
    if((absolute_assert) < 0){
        absolute_assert = absolute_assert * (-1);
    }

    while (absolute_assert >= 0.00001) {
        if((absolute_assert) < 0){
            absolute_assert = absolute_assert * (-1);
        }
        y = z;
        z = (y + (x / y)) / 2;
        absolute_assert = y - z;
    }
    return z;
}

double slope_funtion(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, uint16_t delta_y, double *b){ //will i have issues with this cause of uint16_t and double

    double slope = delta_y / delta_x;
    *b = current_y_ball - current_x_ball * slope;

    trajectory_builder(current_x_ball, current_y_ball, delta_x, slope, *b);

    return slope;
}


int trajectory_builder(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, double slope, double b, uint32_t wall_color, double init_ball_velocity, uint8_t *frame_buffer){  //como estou a passar por parametro nao sei se vão atualiazar aas variaveis talvez passar por referencia para corrigir o problema se bem que a devia a alterar a estrutura d a funçao inteira dado que deveria estar ao contrario ou entao em separado
    uint8_t temp;
    //memset(&trajectory_indexes, 0, sizeof(temp)); dont know if i need this
    int i = 1;

    unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8; // algo esta estranho aqui

    unsigned int index;

    uint16_t y = slope * (current_x_ball + i) + b;// tenho que ajustar a posiçao do Y senao quando colidir nao vai trocar o declive e vai estar a recalcular


    if(delta_x < 0){
        // sentido positivo
        for(i; i <= init_ball_velocity; i++){
            index = (mode_info.XResolution * y + (current_x_ball + i)) * BytesPerPixel; //sera que aualiza o valor de y?
            if(frame_buffer[index] == wall_color){   //NOT SURE IF THIS WORKS gotta chek by hand.
                unsigned int index_up, index_down, index_right, index_left;
                
                index_up = (mode_info.XResolution * (y - 1) + (current_x_ball + i)) * BytesPerPixel;
                index_down = (mode_info.XResolution * (y + 1) + (current_x_ball + i)) * BytesPerPixel;
                index_left = (mode_info.XResolution * y + (current_x_ball + i - 1)) * BytesPerPixel;
                index_right = (mode_info.XResolution * y + (current_x_ball + i + 1)) * BytesPerPixel;

                if((frame_buffer[index_left] == wall_color) && (frame_buffer[index_right] == wall_color)){
                    //aqui tornar o y negativo
                    y *= -1;
                }
                if((frame_buffer[index_down] == wall_color) && (frame_buffer[index_up] == wall_color)){
                    //aqui tornar o x negativo (o y continua a incrementar o x muda de direçao e volta para tras e vice versa em cima)
                    slope *= -1;
                }
            }
            trajectory_indexes[i - 1] = index;  //this will be adding the next index including the one that colides might want to correct this later as ball will appear on top of wall
        }
    }else if(delta_x > 0){
        //sentido negativo
        for(i; i <= init_ball_velocity; i++){
            
            index = (mode_info.XResolution * y + (current_x_ball - i)) * BytesPerPixel; //do i need to check bounds?
            if(frame_buffer[index] == wall_color){   //NOT SURE IF THIS WORKS gotta chek by hand.
                unsigned int index_up, index_down, index_right, index_left;
                
                index_up = (mode_info.XResolution * (y - 1) + (current_x_ball - i)) * BytesPerPixel;
                index_down = (mode_info.XResolution * (y + 1) + (current_x_ball - i)) * BytesPerPixel;
                index_left = (mode_info.XResolution * y + (current_x_ball - i - 1)) * BytesPerPixel;
                index_right = (mode_info.XResolution * y + (current_x_ball - i + 1)) * BytesPerPixel;

                if((frame_buffer[index_left] == wall_color) && (frame_buffer[index_right] == wall_color)){
                    //aqui tornar o y negativo
                    y *= -1;
                }
                if((frame_buffer[index_down] == wall_color) && (frame_buffer[index_up] == wall_color)){
                    //aqui tornar o x negativo (o y continua a incrementar o x muda de direçao e volta para tras e vice versa em cima)
                    slope *= -1;
                }
            }
            trajectory_indexes[i - 1] = index;  //this will be adding the next index including the one that colides might want to correct this later as ball will appear on top of wall
        }
        
    }
    return 0;
}