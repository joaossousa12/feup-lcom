
#include "../game/game.h"

//define canmove, mousepositionx, mousepositiony, spritebordersx, spritebordersy, spritelen, sprite width
void drawGame(){
    
}


void process_tacada_MOUSE(uint16_t delta_X, uint16_t delta_y, bool can_move, mouse_init_info mouse_state){
    if(can_move){
        if(delta_x == 0 & delta_y == 0){
            //do nothing
        }

        set_initial_ball_state(delta_x, delta_y, can_move);
        
        
        
        
    }
    
}
 