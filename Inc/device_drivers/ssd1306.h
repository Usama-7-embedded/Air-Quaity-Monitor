#ifndef DEVICE_DRIVERS_SSD1306_H_
#define DEVICE_DRIVERS_SSD1306_H_


#include <stdint.h>
#include "device_headers/stm32l432xx.h"

extern uint8_t ssd1306_buffer[128 * 8];

#define SSD1306_ADDR 0x3C
#define SSD1306_CMD  0x00
#define SSD1306_DATA 0x40

void i2c_write(uint8_t addr, uint8_t control_byte, uint8_t data);
void ssd1306_cmd(uint8_t cmd);
void ssd1306_data(uint8_t data);
void ssd1306_init(void);
void ssd1306_clear(void);

void ssd1306_clear_buffer(void);
void ssd1306_update(void);
void ssd1306_draw_pixel(int x, int y);
void ssd1306_draw_circle(int cx, int cy, int r);
void ssd1306_draw_line(int x0, int y0, int x1, int y1);
void ssd1306_draw_rect(int x, int y, int w, int h);

void ssd1306_draw_char(int x, int y, char c);
void ssd1306_print(int x, int y, const char *str);


#endif /* DEVICE_DRIVERS_SSD1306_H_ */
