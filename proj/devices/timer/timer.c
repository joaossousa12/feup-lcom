#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <utils.c>

#include <stdint.h>
#include "i8254.h"

#define BIT(N)  (1<<N)

int timer=0;
int counter=0;

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
    *bit_no = BIT(timer);
    if(sys_irqsetpolicy(0,IRQ_REENABLE,&timer)) return 1;
    return 0;
}

int (timer_unsubscribe_int)() {
    if(sys_irqrmpolicy(&timer)) return 1;
    return 0;
}

void (timer_int_handler)() {
    counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *configuration) { //para ler alguma coisa do timer, é necessário primeiro escrever("avisar") para o controller(neste caso o 0x43);
    if(timer<0 || timer>2) return 1;
    uint8_t controlWord = BIT(7) | BIT(6) | BIT(5) | BIT(timer+1);
    if(sys_outb(0x43, controlWord)) return 1;
    if(util_sys_inb(0x40+timer, configuration)) return 1;
    return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
    union timer_status_field_val data;

    switch (field) {

        case tsf_all:
            data.byte = st;
            break;

        case tsf_initial:
            st = (st >> 4) & 0x03;

            if (st == 1) data.in_mode = LSB_only;
            else if (st == 2) data.in_mode = MSB_only;
            else if (st == 3) data.in_mode = MSB_after_LSB;
            else data.in_mode = INVAL_val;

            break;

        case tsf_mode:
            st = (st >> 1) & 0x07;

            if(st == 6) data.count_mode = 2;
            else if(st == 7) data.count_mode = 3;
            else data.count_mode = st;

            break;

        case tsf_base:
            data.bcd = st & TIMER_BCD;
            break;

        default:
            return 1;
    }

    if (timer_print_config(timer, field, data) != 0) return 1;
    return 0;

  return 1;
}
