#include "NTP.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 8 * 3600, 100);

bool ntp_adjust_time()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        struct tm *timeinfo;
        timeClient.update();
        time_t time_1 = timeClient.getEpochTime();
        time_t time_2 = time_1;
        unsigned long start = millis();
        do
        {
            timeClient.update();
            time_2 = timeClient.getEpochTime();
            if (millis() - start > 2000)
                return false; // 超时退出
        } while (time_1 == time_2);
        timeinfo = localtime(&time_2);
        setRTC(timeinfo->tm_sec, timeinfo->tm_min, timeinfo->tm_hour, timeinfo->tm_wday, timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900 - 2000);
        return 1;
    }
    return 0;
}
