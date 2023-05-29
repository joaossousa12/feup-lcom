#include "physics.h"

double findSqrt(double x)
{
    printf("\nsqrt");
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

    printf("\nEnd of sqrt");
    return z;
}




void trajectory_builder(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, double slope, double b, uint32_t wall_color, double init_ball_velocity){  //como estou a passar por parametro nao sei se vão atualiazar aas variaveis talvez passar por referencia para corrigir o problema se bem que a devia a alterar a estrutura d a funçao inteira dado que deveria estar ao contrario ou entao em separado
    printf("\nEnter traject_builder");
    int i = 1;
    unsigned int index;
    double temp_slope = slope;

    int y = temp_slope * (current_x_ball + i) + b;// tenho que ajustar a posiçao do Y senao quando colidir nao vai trocar o declive e vai estar a recalcular


    if(delta_x > 0){
        printf("\nPositive delta");
        // sentido positivo
        for(; i <= init_ball_velocity; i++){
            y = temp_slope * (current_x_ball + i) + b;
            index = (mode_info.XResolution * y + (current_x_ball + i)) * sizeof(char);

            
            if(frame_buffer[index] == wall_color){ 
                printf("\n No error");  //NOT SURE IF THIS WORKS gotta chek by hand.
                unsigned int index_up, index_down, index_right, index_left;

                index_up = (mode_info.XResolution * (y - 1) + (current_x_ball + i)) * sizeof(char);
                index_down = (mode_info.XResolution * (y + 1) + (current_x_ball + i)) * sizeof(char);
                index_left = (mode_info.XResolution * y + (current_x_ball + i - 1)) * sizeof(char);
                index_right = (mode_info.XResolution * y + (current_x_ball + i + 1)) * sizeof(char);

                if((frame_buffer[index] == wall_color) && (frame_buffer[index] == wall_color)){
                    //aqui tornar o y negativo
                    y *= -1;
                }
                if((frame_buffer[index] == wall_color) && (frame_buffer[index] == wall_color)){
                    //aqui tornar o x negativo (o y continua a incrementar o x muda de direçao e volta para tras e vice versa em cima)
                    temp_slope *= -1;
                }
            }
            printf("End kof loop");

            trajectory_indexes[i - 1] = index;  //this will be adding the next index including the one that colides might want to correct this later as ball will appear on top of wall
            trajectory_x[i-1] = current_x_ball + i;
            trajectory_y[i-1] = y;
        }
    }else if(delta_x < 0){
        //sentido negativo
        for(; i <= init_ball_velocity; i++){
            y = temp_slope * (current_x_ball + i) + b; //added
            index = (mode_info.XResolution * y + (current_x_ball - i)) * sizeof(char); //do i need to check bounds?

            if(frame_buffer[index] == wall_color){   //NOT SURE IF THIS WORKS gotta chek by hand.
                unsigned int index_up, index_down, index_right, index_left;

                index_up = (mode_info.XResolution * (y - 1) + (current_x_ball - i)) * sizeof(char);
                index_down = (mode_info.XResolution * (y + 1) + (current_x_ball - i)) * sizeof(char);
                index_left = (mode_info.XResolution * y + (current_x_ball - i - 1)) * sizeof(char);
                index_right = (mode_info.XResolution * y + (current_x_ball - i + 1)) * sizeof(char);

                if((frame_buffer[index] == wall_color) && (frame_buffer[index] == wall_color)){
                    //aqui tornar o y negativo
                    y *= -1;
                }
                if((frame_buffer[index] == wall_color) && (frame_buffer[index] == wall_color)){
                    //aqui tornar o x negativo (o y continua a incrementar o x muda de direçao e volta para tras e vice versa em cima)
                    temp_slope *= -1;
                }
            }

            trajectory_indexes[i - 1] = index;  //this will be adding the next index including the one that colides might want to correct this later as ball will appear on top of wall
            trajectory_x[i-1] = current_x_ball - i;
            trajectory_y[i-1] = y;
        }
    }
    printf("\nEnter traject_builder");

}

double slope_funtion(uint16_t current_x_ball, uint16_t current_y_ball, uint16_t delta_x, uint16_t delta_y, double *b){ //will i have issues with this cause of uint16_t and double
    printf("\nEnter slope function!");
    double slope = delta_y / delta_x;
    *b = current_y_ball - current_x_ball * slope;

    trajectory_builder(current_x_ball, current_y_ball, delta_x, slope, *b, 0x00008B, init_ball_velocity);
    printf("\nExit slope function!");
    return slope;
}




int set_initial_ball_state(uint16_t delta_x, uint16_t delta_y){ //ou ang
    printf("\nset_inicial_ball_state");
    double b;
    unsigned int index;

    init_ball_velocity = findSqrt((delta_x * delta_x) + (delta_y * delta_y));

    if(init_ball_velocity > 150)
        init_ball_velocity = 150;

    if(delta_x == 0){                       ///// FALTA TRATAR DE COLICOES
        //altera so o y mantem o x
        //talvez fazer uma funcao direction select para saber se é para a esquerda ou direita ou alterar funçoes existentes
        for(int i = 1; i <= init_ball_velocity; i++){
            if(delta_y < 0){
                index = (mode_info.XResolution * (y_ball + i) + x_ball) * sizeof(char); //do i need to check bounds? need to add bytes per pix
            } else if(delta_y > 0){
                index = (mode_info.XResolution * (y_ball - i) + x_ball) * sizeof(char); //do i need to check bounds?

            }
            trajectory_indexes[i - 1] = index;
        }
    }
    if(delta_y == 0){                 ///// FALTA TRATAR DE COLICOES
        //altera so o x mantem o y
        //talvez fazer uma funcao direction select para saber se é para a esquerda ou direita ou alterar funcoes existentes
        for(int i = 1; i <= init_ball_velocity; i++){
            if(delta_x < 0){
                index = (mode_info.XResolution * y_ball + (x_ball + i)) * sizeof(char); //do i need to check bounds?
            } else if(delta_x > 0){
                index = (mode_info.XResolution * y_ball - (x_ball - i)) * sizeof(char); //do i need to check bounds?

            }
            trajectory_indexes[i - 1] = index;
        }

    }
    if((delta_y != 0) && (delta_x != 0)){
        slope_funtion(x_ball, y_ball, delta_x, delta_y, &b); // já vai popular o array
    }

        return 0;

}
