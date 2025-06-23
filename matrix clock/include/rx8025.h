#ifndef RX8025_H
#define RX8025_H

#include <Wire.h>
#include <Arduino.h>
#include "global_variables.h"
#include "rx8025.h"
#include "NTP.h"
#include "wifi_config.h"
#define RTC_ADDRESS 0x32 // RX-8025T 默认I2C地址

void setRTC(byte second, byte minute, byte hour, byte weekDay, byte day, byte month, byte year);
void readRTC_time(int8 *now_hour, int8 *now_minute, int8 *now_second); // 读取并打印 RTC 时间
void readRTC_date(int8 *now_year, int8 *now_month, int8 *now_day, int8 *now_week);
void RX8025_Init();
#endif
