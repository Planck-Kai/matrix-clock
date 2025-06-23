#include "rx8025.h"
//**************************************************************************************************
byte bcdToDecimal(byte bcd)
{
    return ((bcd / 16) * 10) + (bcd % 16); // 将BCD值转换为十进制
}
//**************************************************************************************************
byte decimalToBcd(byte decimal) // 十进制转BCD
{
    return ((decimal / 10) << 4) | (decimal % 10);
}
//**************************************************************************************************
void setRTC(byte second, byte minute, byte hour, byte weekDay, byte day, byte month, byte year) // 设置 RTC 时间 周日为0
{
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(0x00);                 // 起始寄存器
    Wire.write(decimalToBcd(second)); // 秒（BCD）
    Wire.write(decimalToBcd(minute)); // 分（BCD）
    Wire.write(decimalToBcd(hour));   // 时（BCD）
    Wire.write(0x01 << weekDay);      // 周（00000001=周日，00000010=周一）
    Wire.write(decimalToBcd(day));    // 日（BCD）
    Wire.write(decimalToBcd(month));  // 月（BCD）
    Wire.write(decimalToBcd(year));   // 年（BCD，0~99）
    Wire.endTransmission();
    Serial.println("RTC 时间已设置!");
}
//**************************************************************************************************
// 读取并打印 RTC 时间
void readRTC_time(int8 *now_hour, int8 *now_minute, int8 *now_second)
{
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(0x00); // 从时钟的秒寄存器开始读取
    Wire.endTransmission();

    Wire.requestFrom(RTC_ADDRESS, 7); // 读取 7 个字节（秒、分、时、日、月、年、星期）

    if (Wire.available() == 7)
    {
        byte second = Wire.read() & 0x7F; // 取低 7 位
        byte minute = Wire.read();
        byte hour = Wire.read() & 0x3f;
        byte weekDay = Wire.read();
        byte day = Wire.read();
        byte month = Wire.read();
        byte year = Wire.read();
        *now_hour = bcdToDecimal(hour);
        *now_minute = bcdToDecimal(minute);
        *now_second = bcdToDecimal(second);
    }
    else
    {
        Serial.println("无法读取 RTC 时间!");
    }
    if (*now_hour == 3 && *now_minute == 0 && *now_second == 0)
    {
        delay(1000);
        ntp_adjust_time();
        Serial.println("对时");
    }
}

void readRTC_date(int8 *now_year, int8 *now_month, int8 *now_day, int8 *now_week)
{
    Wire.beginTransmission(RTC_ADDRESS);
    Wire.write(0x00); // 从时钟的秒寄存器开始读取
    Wire.endTransmission();

    Wire.requestFrom(RTC_ADDRESS, 7); // 读取 7 个字节（秒、分、时、日、月、年、星期）

    if (Wire.available() == 7)
    {
        byte second = Wire.read() & 0x7F; // 取低 7 位
        byte minute = Wire.read();
        byte hour = Wire.read() & 0x3f;
        byte weekDay = Wire.read();
        byte day = Wire.read();
        byte month = Wire.read();
        byte year = Wire.read();
        *now_year = bcdToDecimal(year);
        *now_month = bcdToDecimal(month);
        *now_day = bcdToDecimal(day);
        switch (weekDay)
        {
        case 1:
            *now_week = 0;
            break;
        case 2:
            *now_week = 1;
            break;
        case 4:
            *now_week = 2;
            break;
        case 8:
            *now_week = 3;
            break;
        case 16:
            *now_week = 4;
            break;
        case 32:
            *now_week = 5;
            break;
        case 64:
            *now_week = 6;
            break;
        }
    }
    else
    {
        Serial.println("无法读取 RTC 时间!");
    }
}
void RX8025_Init()
{
    Wire.begin();
    Wire.beginTransmission(RTC_ADDRESS); // 选择 RTC 地址寄存器
    Wire.write(0x00);
    Wire.endTransmission();
}
