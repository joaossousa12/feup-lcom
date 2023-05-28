#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include "keyboard.h"
#include "timer.c"
#include "i8042.h"
#include "i8254.h"
#include "KBC.c"

#define ESC 0x81
#define MAKE BIT(7)
#define TWO 0xE0

extern int counter_KBC;
extern uint8_t scancode;
int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab3/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}


int (kbd_test_scan)()
{
     int ipc_status;
     uint8_t irq_set;
     message msg;


     if (keyboard_subscribe_interrupts(&irq_set) != 0)
         return 1;

     while(scancode != BREAK_ESC) {
         if (driver_receive(ANY, &msg, &ipc_status) != 0) {
             printf("Error");
             continue;
         }

         if (is_ipc_notify(ipc_status)) {
             switch (_ENDPOINT_P(msg.m_source)) {
                 case HARDWARE:
                     if (msg.m_notify.interrupts & irq_set) {
                         kbc_ih();
                         kbd_print_scancode(!(scancode & MAKE), (scancode == TWO) ? 2 : 1, &scancode);
                     }
             }
         }
     }
     if (keyboard_unsubscribe_interrupts() != 0)
         return 1;
     if (kbd_print_no_sysinb(counter_KBC) != 0)
         return 1;

     return 0;
}

int(kbd_test_poll)() {
    while(scancode !=ESC){
        if(read_KBC_output(0x60,&scancode)) return 1;
        kbd_print_scancode(!(scancode & MAKE),(scancode==TWO)?2:1,&scancode);
    }
    if(keyboard_restore()) return 1;
    return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
    return 0;
}
