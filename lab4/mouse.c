#include "mouse.h"


int hook_id_mouse = 3;
struct packet mouse_packet;
uint8_t byte_index = 0;
uint8_t mouse_bytes[3];
uint8_t current_byte;

int (mouse_subscribe_int)(uint8_t *bit_no){
  if(bit_no == NULL) return 1
  *bit_no = BIT(hook_id_mouse);
  return sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse);
}

int (mouse_unsubscribe_int)(){
  return sys_irqrmpolicy(&hook_id_mouse);
}

void mouse_ih(){
  read_KBC_output(KBC_WRITE_CMD, &current_byte, 1);
}

void (mouse_sync_bytes)(){
  if(byte_index == 0 && (current_byte & FIRST_BYTE)){
    mouse_bytes[byte_index] = current_byte;
    byte_index++;
  }
  else if(byte_index > 0){
    mouse_bytes[byte_index] = current_byte;
    byte_index++;
  }
}

void (mouse_bytes_to_packet)(){
  for(int i = 0; i < 3; i++){
    mouse_packet.bytes[i] = mouse_bytes[i];
  }
  mouse_packet.lb = 
}

