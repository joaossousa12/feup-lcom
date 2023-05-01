#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
int hook_id_timer = 0;
int counter_TIMER = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  if(freq > TIMER_FREQ | freq < 19) return 1;
  if(timer < 0 || timer > 2) return 1;

  uint8_t timerPort, timerSelect = 0;
  if(timer == 0){
    timerPort = TIMER_0;
    timerSelect |= TIMER_SEL0;
  }
  if(timer == 1){
    timerPort = TIMER_1;
    timerSelect |= TIMER_SEL1;
  } 
  if(timer == 2){
    timerPort = TIMER_2;
    timerSelect |= TIMER_SEL2;
  } 

  uint8_t config;
  if(timer_get_conf(timer, &config) == 1) return 1; 

  uint8_t command = config & 0x0F;
  command = command | timerSelect | TIMER_LSB_MSB;
  sys_outb(TIMER_CTRL, command);

  uint16_t count = TIMER_FREQ / freq;
  uint8_t lsb 
  , msb;

  if(util_get_LSB(count, &lsb) == 1) return 1;
  if(util_get_MSB(count, &msb) == 1) return 1;
  if(sys_outb(timerPort, lsb) == 1) return 1;
  if(sys_outb(timerPort, msb) == 1) return 1;


  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  if(bit_no == NULL) return 1;
   *bit_no = BIT(hook_id_timer);

  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer);
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  return sys_irqrmpolicy(&hook_id_timer);
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  counter_TIMER++;
}


int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  if(timer > 2 || timer < 0) return 1;
  if(st == NULL) return 1;

  uint8_t command = (TIMER_RB_CMD| TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));
  if(sys_outb(TIMER_CTRL, command)){
    return 1;
  }
  
  return util_sys_inb(TIMER_0 + timer, st);
}

enum timer_init initMode(uint8_t *st){
  switch (*st & TIMER_LSB_MSB)
    {
    case TIMER_LSB_MSB:      
      return MSB_after_LSB;
      break;
    case TIMER_LSB:
      return LSB_only;
      break;
    case TIMER_MSB:
      return MSB_only;
      break;
    default:
      return INVAL_val;
      break;
    }
}

uint8_t countMode(uint8_t st){
  switch (st)
  {
  case 0x06:
    return 2;
  case 0x07:
    return 3;
  default:
    return st;
  }
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */

  union timer_status_field_val status;
  

  switch (field)
  {
  case tsf_all:
    status.byte = st;
    break;
  case tsf_initial:
    status.in_mode = initMode(&st);
    break;
  case tsf_mode:
    st = st >> 1;
    st = st & 0x07;
    status.count_mode = countMode(st);
    break;
  case tsf_base:
    st = st & 0x01;
    status.bcd = (st == 1);
    break;
  }
  

  return timer_print_config(timer, field, status);
}
