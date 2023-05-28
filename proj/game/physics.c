#include "physics.h"

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




void trajectory_builder(int current_x_ball, int current_y_ball, int delta_x, double slope, double b, int wall_color, double init_ball_velocity){  //como estou a passar por parametro nao sei se vão atualiazar aas variaveis talvez passar por referencia para corrigir o problema se bem que a devia a alterar a estrutura d a funçao inteira dado que deveria estar ao contrario ou entao em separado
    int temp;
    int i = 1;
    unsigned int index;
    double temp_slope = slope;

    int y = temp_slope * (current_x_ball + i) + b;// tenho que ajustar a posiçao do Y senao quando colidir nao vai trocar o declive e vai estar a recalcular


    if(delta_x > 0){
        // sentido positivo
        for(i; i <= init_ball_velocity; i++){
            y = temp_slope * (current_x_ball + i) + b;
            index = (mode_info.XResolution * y + (current_x_ball + i)) * sizeof(char);


            if(framebuffer[y][current_x_ball + i] == wall_color){   //NOT SURE IF THIS WORKS gotta chek by hand.
                unsigned int index_up, index_down, index_right, index_left;

                index_up = (mode_info.XResolution * (y - 1) + (current_x_ball + i)) * sizeof(char);
                index_down = (mode_info.XResolution * (y + 1) + (current_x_ball + i)) * sizeof(char);
                index_left = (mode_info.XResolution * y + (current_x_ball + i - 1)) * sizeof(char);
                index_right = (mode_info.XResolution * y + (current_x_ball + i + 1)) * sizeof(char);

                if((framebuffer[y][current_x_ball + i - 1] == wall_color) && (framebuffer[y][current_x_ball + i + 1] == wall_color)){
                    //aqui tornar o y negativo
                    y *= -1;
                }
                if((framebuffer[y - 1][current_x_ball + i] == wall_color) && (framebuffer[y + 1][current_x_ball + i] == wall_color)){
                    //aqui tornar o x negativo (o y continua a incrementar o x muda de direçao e volta para tras e vice versa em cima)
                    temp_slope *= -1;
                }
            }

            trajectory_indexes[i - 1] = index;  //this will be adding the next index including the one that colides might want to correct this later as ball will appear on top of wall
        }
    }else if(delta_x < 0){
        //sentido negativo
        for(i; i <= init_ball_velocity; i++){
            y = temp_slope * (current_x_ball + i) + b; //added
            index = (mode_info.XResolution * y + (current_x_ball - i)) * sizeof(char); //do i need to check bounds?

            if(framebuffer[y][current_x_ball - i] == wall_color){   //NOT SURE IF THIS WORKS gotta chek by hand.
                unsigned int index_up, index_down, index_right, index_left;

                index_up = (mode_info.XResolution * (y - 1) + (current_x_ball - i)) * sizeof(char);
                index_down = (mode_info.XResolution * (y + 1) + (current_x_ball - i)) * sizeof(char);
                index_left = (mode_info.XResolution * y + (current_x_ball - i - 1)) * sizeof(char);
                index_right = (mode_info.XResolution * y + (current_x_ball - i + 1)) * sizeof(char);

                if((framebuffer[y][current_x_ball -i -1] == wall_color) && (framebuffer[y][current_x_ball -i + 1] == wall_color)){
                    //aqui tornar o y negativo
                    y *= -1;
                }
                if((framebuffer[y - 1][current_x_ball - i] == wall_color) && (framebuffer[y + 1][current_x_ball - i] == wall_color)){
                    //aqui tornar o x negativo (o y continua a incrementar o x muda de direçao e volta para tras e vice versa em cima)
                    temp_slope *= -1;
                }
            }

            trajectory_indexes[i - 1] = index;  //this will be adding the next index including the one that colides might want to correct this later as ball will appear on top of wall
        }
    }
}

double slope_funtion(int current_x_ball, int current_y_ball, int delta_x, int delta_y, double *b){ //will i have issues with this cause of uint16_t and double

    double slope = delta_y / delta_x;
    *b = current_y_ball - current_x_ball * slope;

    trajectory_builder(current_x_ball, current_y_ball, delta_x, slope, *b, wall_color, init_ball_velocity);

    return slope;
}




int set_initial_ball_state(int delta_x, int delta_y, int XResolution){ //ou ang
    double slope;
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
                index = (mode_info.XResolution * (ball_pos_y + i) + ball_pos_X);// * sizeof(char); //do i need to check bounds? need to add bytes per pix
            } else if(delta_y > 0){
                index = (mode_info.XResolution * (ball_pos_y - i) + ball_pos_X); //* sizeof(char); //do i need to check bounds?

            }
            trajectory_indexes[i - 1] = index;
        }
    }
    if(delta_y == 0){                 ///// FALTA TRATAR DE COLICOES
        //altera so o x mantem o y
        //talvez fazer uma funcao direction select para saber se é para a esquerda ou direita ou alterar funcoes existentes
        for(int i = 1; i <= init_ball_velocity; i++){
            if(delta_x < 0){
                index = (mode_info.XResolution * ball_pos_y + (ball_pos_X + i)); //* sizeof(char); //do i need to check bounds?
            } else if(delta_x > 0){
                index = (mode_info.XResolution * ball_pos_y - (ball_pos_X - i)); //* sizeof(char); //do i need to check bounds?

            }
            trajectory_indexes[i - 1] = index;
        }

    }
    if((delta_y != 0) && (delta_x != 0)){
        slope_funtion(ball_pos_X, ball_pos_y, delta_x, delta_y, &b); // já vai popular o array
    }

        return 0;

}

