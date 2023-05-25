//
// Created by Bernardo on 25/05/2023.
//

#ifndef SRC_MOUSE_H
#define SRC_MOUSE_H

#include <lcom/lcf.h>
#include <stdint.h>
#include "KBC.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (mouse_sync)();

void (to_packet) ();

int (mouse_write)(uint8_t command);

#endif //SRC_MOUSE_H
