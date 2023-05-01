#include "KBC.h"

int (read_KBC_status)(uint8_t* status){
  if(status == NULL) return 1;

  if(util_sys_inb(KBC_STATUS_REG, &status) != 0) return 1;
  return 0;
}

int (read_KBC_output)(uint8_t port, uint8_t *output){
  if(port == NULL) return 1;
  if(output == NULL) return 1;

  uint8_t status;
  int attempts = MAX_ATTEMPS;

  while(attempts > 0){
    if(read_KBC_status(&status) != 0) return 1;
    if(status & FULL_OUT_BUFFER != 0){
      if(util_sys_inb(port, output) != 0) return 1;
      if(status & PARITY_ERROR != 0) return 1;
      if(status & TIMEOUT_ERROR != 0) return 1;
      return 0;
    }


    attempts--;
    tickdelay(micros_to_ticks(WAIT_KBC));
  }
  return 1;
}

int (write_KBC_command)(uint8_t port, uint8_t commandByte){
  if(port == NULL) return 1;
  if(commandByte == NULL) return 1;

  uint8_t status;
  int attempts = MAX_ATTEMPS;

  while(attempts > 0){
    if(read_KBC_status(&status) != 0) return 1;
    if (status & FULL_IN_BUFFER == 0){
      if(sys_outb(port, commandByte != 0)) return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(WAIT_KBC));
    attempts--;
  }
  return 1;
}