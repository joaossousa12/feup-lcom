#include <lcom/lcf.h>
#include "devices/timer/timer.h"
#include "devices/keyboard/keyboard.h"
#include "devices/mouse/mouse.h"
#include "MACROS.h"
#include "game/menu.h"
#include "game/instructions.h"
#include "game/game.h"
#include "sprites/sprites.h"
#include "game/physics.h"


int gameMode = MENU_MODE;

extern vbe_mode_info_t mode_info;
extern uint8_t x;
extern uint8_t y;
extern struct mouse_init_info mouse_state; //TO DEFINE WHEN SHOWING MOUSE SPRITE

int ball_pos_X;
int ball_pos_y;


extern uint8_t scancode;
extern struct packet mouse_packet;

int (main)(int argc, char *argv[])
{
    lcf_set_language("EN-US");

    lcf_trace_calls("/home/lcom/labs/proj_new/trace.txt");

    lcf_log_output("/home/lcom/labs/proj_new/output.txt");

    if (lcf_start(argc, argv))
        return 1;

    lcf_cleanup();

    return 0;
}

int beforeLoop(){
    if(map_vmem(0x115)) return 1;
    if(set_graphic_mode(0x115)) return 1;
    loadSprites();
    allocateSpaceBuffer();
    return 0;
}

int afterLoop(){
    unloadSprites();
    if(vg_exit()!=0) return 1;
    return 0;
}


int (proj_main_loop)(int argc, char *argv[])
{
    if(beforeLoop()) return 1;
    if (timer_set_frequency(0, 30) != 0)
        return 1;

    if (timer_subscribe_interrupts() != 0)
        return 1;
    if (keyboard_subscribe_interrupts() !=0)
        return 1;
    if (mouse_subscribe_int() !=0)
        return 1;

    int i = 0;

    int ipc_status;
    message msg;

    while (true) {

        if (driver_receive(ANY, &msg, &ipc_status) != 0) {
            printf("Error");
            continue;
        }


        if(gameMode==EXIT_MODE) break;

        if (is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & 1) {
                        if (gameMode == MENU_MODE){
                            if(drawMenu()) return 1;
                        }
                        else if (gameMode == GAME_MODE){
                            if(drawGame()) return 1;
                        }
                        else if (gameMode == INSTRUCTIONS_MODE){
                            if(drawInstructionsPage()) return 1;
                        }
                        videoSet();
                        clearBuffer();
                    }
                    if (msg.m_notify.interrupts & 2){
                        kbc_ih();
                        if(gameMode == MENU_MODE) {process_keyboard_menu(scancode);}
                        else if(gameMode == GAME_MODE) {process_keyboard_game(scancode);}
                        else if(gameMode == INSTRUCTIONS_MODE) {process_keyboard_instructions(scancode);}
                    }
                    if (msg.m_notify.interrupts & 64){
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

    if (timer_unsubscribe_interrupts() != 0)
        return 1;
    if (keyboard_unsubscribe_interrupts()!=0)
        return 1;
    if (mouse_unsubscribe_int()!=0)
        return 1;

    if(afterLoop()) return 1;
    return 0;
}