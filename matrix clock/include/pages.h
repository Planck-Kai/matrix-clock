#ifndef PAGES_H
#define PAGES_H

#include <Arduino.h>
#include "max7219.h"
#include "global_variables.h"
#include "rx8025.h"
#include "NTP.h"
void clock_page_style_1(int8 x, int8 y);
void clock_page_style_2(int8 x, int8 y);
void clock_page_style_3(int8 x, int8 y);
void clock_page_style_4(int8 x, int8 y);
void clock_page_style_5(int8 x, int8 y);
void date_page_week(int8 x, int8 y);
void date_page_month(int8 x, int8 y);
void date_page_year(int8 x, int8 y);
void set_brightness_page(int8 x, int8 y);
void synchronize_time_page(int8 x, int8 y);
void connect_page(int8 x, int8 y);
void connect_success_page(int8 x, int8 y);
void connect_failed_page(int8 x, int8 y);
void wifi_config_page(int8 x, int8 y);
void initial_page(int8 x, int8 y);
void success_page(int8 x, int8 y);
void get_time();
void get_date();
#endif