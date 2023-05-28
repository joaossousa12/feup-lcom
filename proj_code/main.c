#include <lcom/lcf.h>
#include "devices/timer/timer.h"
#include "devices/keyboard/keyboard.h"
#include "devices/mouse/mouse.h"
#include "MACROS.h"
#include "game/menu.h"
#include "game/instructions.h"
#include "game/game.h"
#include "sprites/sprites.h"

int gameMode = MENU_MODE;

extern vbe_mode_info_t mode_info;


extern int x;
extern int y;
extern struct packet mouse_packet;
extern uint8_t bytes[3];
extern int current_index;

extern uint8_t scancode;

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
                  copyToAuxiliarBuffer();
              }
              else if (gameMode == INSTRUCTIONS_MODE){
                  if(drawInstructionsPage()) return 1;
              }
              drawMouse();
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
              mouse_sync();
              if(current_index == 3){
                current_index = 0;
                to_packet();
                refresh_mouse_location();
                /*if(gameMode == GAME_MODE){
                  if(mouse_packet.lb){
                    // drag ball
                  }
                }*/
              }
              //printf("Mouse interrupted");
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
