#include <avr/io.h>
#include <stdint.h>
#include "io.h"
// defining the buzzer pin
#define BUZZER PB2

void io_init(void)
{
    //set pb2 as output
    DDRB |= (1 << BUZZER);
    //making it start off (LOW)
    PORTB &= ~(1 << BUZZER);
}

void buzzer_set(uint8_t state)
{
    // control the buzzer
    if (state)
        PORTB |= (1 << BUZZER);
    else
        PORTB &= ~(1 << BUZZER);
}
