
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "buttons.h"
// define the pins
#define BUTTON_HIGH PB0
#define BUTTON_LOW PB1
// check if the button is being pressed
uint8_t button_pressed(uint8_t pin)
{

    if (!(PINB & (1 << pin)))
    {
        _delay_ms(25);

        if (!(PINB & (1 << pin)))
        {
            // Wait for button release
            while (!(PINB & (1 << pin)))
            {
            }

            _delay_ms(25);

            return 1;
        }
    }

    return 0;
}

void buttons_init(void)
{
    // make the buttons as inputs
    DDRB &= ~((1 << BUTTON_HIGH) |
              (1 << BUTTON_LOW));

    // Enable internal pull-up resistors
    PORTB |= (1 << BUTTON_HIGH) |
             (1 << BUTTON_LOW);
}

uint8_t button_high_pressed(void)
{
    return button_pressed(BUTTON_HIGH);
}

uint8_t button_low_pressed(void)
{
    return button_pressed(BUTTON_LOW);
}
