#include <lcom/lcf.h>

//funções para decorar para o teste
#include <stdint.h>

int counter_KBC=0;
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if (*lsb=='\0') return 1;
  *lsb=val&0xFF;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (*msb=='\0') return 1;
  *msb = val>>8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) //importante esta função
{
    counter_KBC++;
    if (*value=='\0') return 1;
    uint32_t aux;
    if(sys_inb(port, &aux)!=0) return 1;
    *value = port & 0xFF;
    return 0;
}
