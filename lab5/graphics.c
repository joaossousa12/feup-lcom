#include <lcom/lcf.h>
#include "graphics.h"
#include <math.h>

int (set_graphic_mode)(uint16_t submode){
  reg86_t reg86;
  memset(&reg86,0,sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ax = 0x4F02;
  reg86.bx = submode | BIT(14);
  if(sys_int86(&reg86) != 0) return 1;
  return 0;
}

int(set_text_mode)(){
  reg86_t reg86;
  memset(&reg86,0,sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ax = 0x0003;
  reg86.bx = 0x0000;
  if(sys_int86(&reg86) != 0) return 1;
  return 0;
}

int(set_frame_buffer)(uint16_t mode){
  memset(&mode_info, 0, sizeof(mode_info));
  if(vbe_get_mode_info(mode, &mode_info) != 0) return 1;
  int bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
  int frame_size = mode_info.XResolution * mode_info.YResolution * bytes_per_pixel;

  struct minix_mem_range physic_address;
  physic_address.mr_base = mode_info.PhysBasePtr;
  physic_address.mr_limit = mode_info.PhysBasePtr + frame_size;

  if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physic_address)) return 1;

  frame_buffer = vm_map_phys(SELF, (void*) physic_address.mr_base, frame_size);
  if(frame_buffer == NULL) return 1;

  return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
  if(x >= mode_info.XResolution | y >= mode_info.YResolution) return 1;

  uint8_t bits_to_bytes = (mode_info.BitsPerPixel + 7 ) / 8;

  int index = (mode_info.XResolution * y + x) * bits_to_bytes;

  if(memcpy(&frame_buffer[index], &color, bits_to_bytes) == NULL) return 1;

  return 0;
}

