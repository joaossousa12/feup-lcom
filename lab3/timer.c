#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>
#include "i8254.h"



int hook_id=0;
int timer_global=0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) { //importante não esquecer dos ifs em todas as funções
    if(timer<0 || timer>2) return 1;
    if(freq<19 || freq>TIMER_FREQ) return 1;
    uint16_t counter = TIMER_FREQ/freq;
    uint8_t conf;
    if(timer_get_conf(timer,&conf)) return 1;
    conf= conf & 0x0F;
    switch (timer) {
        case 0:
            break;
        case 1:
            conf = conf|BIT(6);
        case 2:
            conf = conf|BIT(7);
    }
    conf = conf| BIT(5) | BIT(4);
    if(sys_outb(0x43,conf)) return 1;
    uint8_t MSB,LSB;
    if(util_get_LSB(counter,&LSB)) return 1;
    if(util_get_MSB(counter,&MSB)) return 1;
    if(sys_outb(0x40 + timer,LSB)) return 1;
    if(sys_outb(0x40 + timer,MSB)) return 1;
    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    if(bit_no==NULL) return 1;
    *bit_no = BIT(hook_id);
    if(sys_irqsetpolicy(0,IRQ_REENABLE,&hook_id)) return 1;
    return 0;
}

int (timer_unsubscribe_int)() {
    if(sys_irqrmpolicy(&hook_id)) return 1;
    return 0;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *configuration) { //para ler alguma coisa do timer, é necessário primeiro escrever("avisar") para o controller(neste caso o 0x43);
    if(timer<0 || timer>2) return 1;
    uint8_t x=timer+1;
    uint8_t controlWord = BIT(7) | BIT(6) | BIT(5) | BIT(x);
    if(sys_outb(0x43, controlWord)) return 1;
    if(util_sys_inb(0x40+timer, configuration)) return 1;
    return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
