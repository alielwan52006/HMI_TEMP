
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "adc.h"
#include "lcd.h"
#include "buttons.h"
#include "io.h"

#define INITIAL_LOW_LIMIT  20
#define INITIAL_HIGH_LIMIT 35

int main(void)
{
    uint16_t adc_value;
    uint8_t temperature;
    uint8_t low_limit = INITIAL_LOW_LIMIT;
    uint8_t high_limit = INITIAL_HIGH_LIMIT;
    char line[17];

    // Initialize components
    io_init();
    adc_init();
    lcd_init();
    buttons_init();

    // first message on the lcd
    lcd_clear();
    lcd_gotoxy(0, 0);
    lcd_puts("Temperature HMI");
    lcd_gotoxy(0, 1);
    lcd_puts("System Ready");

    _delay_ms(1500);

    while (1)
    {
        // Increase high limit by one each press
        if (button_high_pressed() && high_limit < 99)
            high_limit++;

        // Increase low limit by one eache press 
        if (button_low_pressed() && low_limit < high_limit)
            low_limit++;

        // Reading  the temperature
        adc_value = adc_read(0);
        temperature = (adc_value * 500UL) / 1024;

        // check weither the reading is within the range
        if (temperature < low_limit || temperature > high_limit)
            buzzer_set(1);
        else
            buzzer_set(0);

        // Display temperature
        lcd_gotoxy(0, 0);
        sprintf(line, "Temp: %u C", temperature);
        lcd_puts(line);

        // Display limits
        lcd_gotoxy(0, 1);
        sprintf(line, "L:%u H:%u", low_limit, high_limit);
        lcd_puts(line);

        _delay_ms(300);
    }
}
