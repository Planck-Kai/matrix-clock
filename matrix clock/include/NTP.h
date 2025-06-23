#ifndef NTP_H
#define NTP_H

#include <ESP8266WiFi.h>
#include <time.h>
#include "rx8025.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
bool ntp_adjust_time();
#endif