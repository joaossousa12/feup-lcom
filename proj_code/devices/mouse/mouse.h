//
// Created by Bernardo on 25/05/2023.
//

#ifndef SRC_MOUSE_H
#define SRC_MOUSE_H

#include <lcom/lcf.h>
#include <stdint.h>
#include <minix/sysutil.h>
#include "KBC_mouse.h"
#include "i8042.h"

int (mouse_subscribe_int)();

int (mouse_unsubscribe_int)();

void (mouse_ih)();

void (mouse_sync)();

int (to_packet) ();

int (mouse_write)(uint8_t command);

void (refresh_mouse_location)();

#endif //SRC_MOUSE_H
