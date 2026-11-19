#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void lcd_init(void);
void lcd_command(uint8_t command);
void lcd_data(uint8_t data);
void lcd_clear(void);
void lcd_gotoxy(uint8_t column, uint8_t row);
void lcd_puts(const char *text);

#endif