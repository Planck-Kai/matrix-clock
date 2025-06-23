#ifndef BUTTON_H
#define BUTTON_H

#include <OneButton.h>
#include "max7219.h"
#include "global_variables.h"
#include "pages.h"
#include "wifi_config.h"
#include "NTP.h"
void button1_click();
void button2_longpress();
void button2_click();
void button3_click();
void button_init();
void button_run();

#endif