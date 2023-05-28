    #include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "game/instructions.h"
#include "game/game.h"
#include "game/menu.h"
#include "devices/keyboard/keyboard.h"
#include "devices/keyboard/KBC.h"
#include "devices/timer/timer.h"
#include "devices/mouse/mouse.h"
#include "devices/video/VBE.h"
#include "devices/video/video.h"
#include "MACROS.h"

int gameMode = MENU_MODE;

extern vbe_mode_info_t info;
extern uint16_t xRes;
extern uint16_t yRes;
extern uint8_t x;
extern uint8_t y;
extern unsigned bytesPerPixel;

extern uint8_t scancode;

extern struct packet mouse_packet;

extern struct mouse_init_info mouse_state; //TO DEFINE WHEN SHOWING MOUSE SPRITE

int ball_pos_X;
int ball_pos_y;

extern int counter;
bool running = true;



int main(int argc, char *argv[]){
    lcf_set_language("EN-US");

    lcf_trace_calls("home/lcom/labs/g4/proj/src/output/trace.txt");

    lcf_log_output("/home/lcom/labs/g4/proj/src/output/output.txt");

    if (lcf_start(argc, argv)) return 1;

    lcf_cleanup();

    return 0;
}

int process_interruptions(){

    if(timer_set_frequency(0,30)) return 1;

    //if(mouse_config(0xEA)) return 1; // enable stream mode
    //if(mouse_config(0xF4)) return 1; // enable data report

    int ipc_status;
    uint8_t irq_kb, irq_mouse, irq_timer;
    message msg;

    if(timer_subscribe_int(&irq_timer)) return 1;
    if(keyboard_subscribe_interrupts(&irq_kb)) return 1;
    if(mouse_subscribe_int(&irq_mouse)) return 1;
    while(running){

        if( driver_receive(ANY, &msg, &ipc_status) != 0 ){
            printf("Error");
            continue;
        }
        if(is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)){
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_timer) {
                        counter++;
                        if (gameMode == MENU_MODE){ drawMenu(); }
                        else if (gameMode == GAME_MODE){ drawGame(); }
                        else if (gameMode == INSTRUCTIONS_MODE){ drawInstructionsPage(); }
                    }

                    if (msg.m_notify.interrupts & irq_kb ){
                        kbc_ih();
                        if(gameMode == MENU_MODE) {process_keyboard_menu(scancode);}
                        else if(gameMode == GAME_MODE) {process_keyboard_game(scancode);}
                        else if(gameMode == INSTRUCTIONS_MODE) {process_keyboard_instructions(scancode);}
                    }

                    if(msg.m_notify.interrupts & irq_mouse){
                        mouse_ih();         
                        mouse_sync();               //instruções verificam se o Mouse_button foi pressed
                        mouse_position_update();       //TO BE IMPLEMENTED WHEN DRAWING MOUSE SPRITE
                        if(gameMode == GAME_MODE) {         //VERIFY GAME LOOP cause after processin the shot cant register another one cause there is no loop
                            if(mouse_packet.lb && ball_clicked_verify(ball_pos_X, ball_pos_y, mouse_state)){
                                bool hold_mouse_lb = true;
                                while (hold_mouse_lb)
                                {
                                    mouse_ih();         
                                    mouse_sync();
                                    mouse_position_update();
                                    if(!mouse_packet.lb){
                                        if((delta_x == 0) && (delta_y == 0)) // not finished yet
                                        process_tacada_MOUSE (mouse_packet.delta_x, mouse_packet.delta_y, can_move, mouse_state);
                                        hold_mouse_lb = false;
                                    }  
                                }
                                
                            }
                        }
                    }
            }
        }
    }
    return 0;
}



/*
if(mouse_position >= sprite_borders || mouse_position <= sprite_borders){
            
        }
        else{
            //do nothing cause mouse didnt press on the ball
        }




bool ball_clicked_verify(ball_pos_X, ball_pos_y, mouse_state){
    if((mouse_state.pos_x >= ball_pos_X - ball_radius && mouse_state.pos_x <= ball_pos_X + ball_radius) && (mouse_state.pos_y >= ball_pos_y - ball_radius && mouse_state.pos_y <= ball_pos_y + ball_radius)){
        return true;
    }
    return false;
}

*/


int(proj_main_loop)(int argc, char *argv[]){
    if(process_interruptions()) return 1;
    return 0;
}

