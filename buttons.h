#ifndef BUTTONS_H
#define BUTTONS_H
#include <stdint.h>
void buttons_init(void);
uint8_t button_high_pressed(void);
uint8_t button_low_pressed(void);
#endif
