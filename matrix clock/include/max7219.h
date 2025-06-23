#ifndef MAX7219_H
#define MAX7219_H

#define CS 15 // Pin cs  (SPI)
#define anzMAX 4
#include <Arduino.h>
#include <SPI.h>
#include "font.h"
#include "wifi_config.h"

void max7219_init();
void max7219_set_brightness(unsigned short br);
void max7219_display_on();
void max7219_display_off();
void clear_Display();
void clear_display_memory();
void full_Display();
void display_refresh();
void char2display_memory_font1(unsigned short ch, int PosX, int PosY);
void char2display_memory_font2(unsigned short ch, int PosX, int PosY);
void char2display_memory_font3(unsigned short ch, int PosX, int PosY);
void char2display_memory_font4(unsigned short ch, int PosX, int PosY);
void char2display_memory_font5(unsigned short ch, int PosX, int PosY);
#endif