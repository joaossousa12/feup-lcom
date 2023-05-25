#ifndef _LCOM_KBC_MOUSE_H_
#define _LCOM_KBC_MOUSE_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"

int (read_KBC_status_mouse)(uint8_t* status);

int (read_KBC_output_mouse)(uint8_t port, uint8_t *output, uint8_t mouse);

int (write_KBC_command_mouse)(uint8_t port, uint8_t commandByte);

#endif
