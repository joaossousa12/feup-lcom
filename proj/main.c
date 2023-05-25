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
                        mouse_sync();
                        if(gameMode == GAME_MODE) {
                            if(mouse_packet.lb)
                                process_tacada_MOUSE ( x , y );
                        }
                    }
            }
        }
    }
    return 0;
}

int(proj_main_loop)(int argc, char *argv[]){
    if(process_interruptions()) return 1;
    return 0;
}

