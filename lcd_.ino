#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"

// LCD wired pins
#define LCD_PORT PORTD
#define LCD_DDR DDRD

#define LCD_RS PD2
#define LCD_EN PD3

void lcd_enable_pulse(void)
{
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);

    LCD_PORT &= ~(1 << LCD_EN);
    _delay_us(100);
}

void lcd_write_nibble(uint8_t value)
{
    LCD_PORT = (LCD_PORT & 0x0F) |
               (value & 0xF0);

    lcd_enable_pulse();
}

void lcd_send(uint8_t value, uint8_t is_data)
{
    if (is_data)
        LCD_PORT |= (1 << LCD_RS);
    else
        LCD_PORT &= ~(1 << LCD_RS);

    lcd_write_nibble(value & 0xF0);

    lcd_write_nibble((value << 4) & 0xF0);
}

void lcd_command(uint8_t command)
{
    lcd_send(command, 0);

    if (command == 0x01 || command == 0x02)
        _delay_ms(2);
}

void lcd_data(uint8_t data)
{
    lcd_send(data, 1);
}

void lcd_clear(void)
{
    lcd_command(0x01);
}

void lcd_gotoxy(uint8_t column, uint8_t row)
{
    uint8_t address;

    if (row == 0)
        address = 0x00;
    else
        address = 0x40;

    lcd_command(0x80 | (address + column));
}

void lcd_puts(const char *text)
{
    while (*text)
    {
        lcd_data((uint8_t)*text);
        text++;
    }
}

void lcd_init(void)
{
    // Configure PD2 to PD7 as outputs
    LCD_DDR |= 0xFC;

    _delay_ms(20);

    LCD_PORT &= ~(1 << LCD_RS);
    LCD_PORT &= ~(1 << LCD_EN);

    // Initialize LCD in 4-bit mode
    lcd_write_nibble(0x30);
    _delay_ms(5);

    lcd_write_nibble(0x30);
    _delay_us(150);

    lcd_write_nibble(0x30);
    _delay_us(150);

    lcd_write_nibble(0x20);

    // LCD configuration
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);

    lcd_clear();
}