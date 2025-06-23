#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "rx8025.h"
#include "pages.h"
#include "max7219.h"
#include <cstdint>
#define EEPROM_SIZE 110 // 分配EEPROM大小
#define SSID_ADDR 0     // SSID存储的起始地址
#define PASS_ADDR 32    // 密码存储的起始地址
#define clock_style_addr 100
#define brightness_addr 105

extern const char *default_ap_ssid;     // 默认热点SSID
extern const char *default_ap_password; // 默认热点密码
extern ESP8266WebServer server;         // 创建Web服务器实例

void wifi_init();
void writeEEPROM(int start, String data);
String readEEPROM(int start, int len);

#endif