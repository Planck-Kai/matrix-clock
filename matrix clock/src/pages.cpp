#include "pages.h"

int8 now_hour, now_minute, now_second;
int8 hour_h, hour_l, minute_h, minute_l, second_h, second_l;
int8 year, month, day, week;
int8 year_h, year_l, month_h, month_l, day_h, day_l, weekday;
int8 i = 0;
void clock_page_style_1(int8 x, int8 y)
{

    char2display_memory_font2(hour_h + 48, x, y);
    char2display_memory_font2(hour_l + 48, x + 6, y);
    char2display_memory_font2(minute_h + 48, x + 16, y);
    char2display_memory_font2(minute_l + 48, x + 22, y);
    if (my_time < 50)
    {
        char2display_memory_font1(60, x + 12, y); // 空白
    }
    if (my_time > 50)
    {
        char2display_memory_font1(59, x + 12, y); // ：
    }
    display_refresh();
}

void clock_page_style_2(int8 x, int8 y)
{
    if ((now_hour > 19 && now_hour <= 23) || (now_hour >= 0 && now_hour <= 6))
    {
        char2display_memory_font3(20, x, y); // 月亮
    }
    if (now_hour > 6 && now_hour <= 8)
    {
        char2display_memory_font3(22, x, y); // 日出
    }
    if (now_hour > 8 && now_hour <= 17)
    {
        char2display_memory_font3(21, x, y); // 太阳
    }
    if (now_hour > 17 && now_hour <= 19)
    {
        char2display_memory_font3(22, x, y); // 日出(日落)
    }
    char2display_memory_font1(hour_h + 48, x + 8, y);
    char2display_memory_font1(hour_l + 48, x + 5 + 8, y);
    char2display_memory_font1(minute_h + 48, x + 12 + 8, y);
    char2display_memory_font1(minute_l + 48, x + 17 + 8, y);
    if (my_time < 50)
    {
        char2display_memory_font1(60, x + 9 + 8, y); // 空白
    }
    if (my_time > 50)
    {
        char2display_memory_font1(59, x + 9 + 8, y); // ：
    }
    display_refresh();
}

void clock_page_style_3(int8 x, int8 y)
{
    char2display_memory_font4(hour_h + 48, 0 + x, y);
    char2display_memory_font4(hour_l + 48, 4 + x, y);

    char2display_memory_font4(minute_h + 48, 10 + x, y);
    char2display_memory_font4(minute_l + 48, 14 + x, y);

    char2display_memory_font4(second_h + 48, 20 + x, y);
    char2display_memory_font4(second_l + 48, 24 + x, y);
    if (my_time < 50)
    {
        char2display_memory_font4(59, 7 + x, y);
        char2display_memory_font4(59, 17 + x, y);
    }
    if (my_time > 50)
    {
        char2display_memory_font4(58, 7 + x, y);  //:
        char2display_memory_font4(58, 17 + x, y); //:
    }
    display_refresh();
}

void clock_page_style_4(int8 x, int8 y)
{
    char2display_memory_font5(hour_h + 48, 1 + x, y);
    char2display_memory_font5(hour_l + 48, 8 + x, y);
    char2display_memory_font5(minute_h + 48, 18 + x, y);
    char2display_memory_font5(minute_l + 48, 25 + x, y);
    if (my_time < 50)
    {
        char2display_memory_font1(60, 14 + x, y);
    }
    if (my_time > 50)
    {
        char2display_memory_font1(58, 14 + x, y); //:
    }
    display_refresh();
}

void clock_page_style_5(int8 x, int8 y)
{
    if (dog_posx < 7)
        if (dog_posx % 2 == 0)
            char2display_memory_font3(28, dog_posx + x, y);
        else
            char2display_memory_font3(29, dog_posx + x, y);
    if (dog_posx >= 7)
        if (dog_posx % 2 == 0)
            char2display_memory_font3(30, 15 - dog_posx + x, y);
        else
            char2display_memory_font3(31, 15 - dog_posx + x, y);
    char2display_memory_font4(hour_h + 48, 15 + x, y);
    char2display_memory_font4(hour_l + 48, 19 + x, y);
    char2display_memory_font4(minute_h + 48, 25 + x, y);
    char2display_memory_font4(minute_l + 48, 29 + x, y);
    if (my_time < 50)
    {
        char2display_memory_font4(59, 22 + x, y);
    }
    if (my_time > 50)
    {
        char2display_memory_font4(58, 22 + x, y); //:
    }
    display_refresh();
}

void date_page_week(int8 x, int8 y)
{
    char2display_memory_font3(8, x, y);
    char2display_memory_font3(9, x + 8, y);
    char2display_memory_font3(week, x + 16, y);
    display_refresh();
}

void date_page_month(int8 x, int8 y)
{
    char2display_memory_font4(month_h + 48, x, y);
    char2display_memory_font4(month_l + 48, x + 4, y);
    char2display_memory_font3(10, x + 8, y);
    char2display_memory_font4(day_h + 48, x + 16, y);
    char2display_memory_font4(day_l + 48, x + 16 + 4, y);
    char2display_memory_font3(0, x + 16 + 4 + 4, y);
    display_refresh();
}

void date_page_year(int8 x, int8 y)
{
    char2display_memory_font2('2', x, y);
    char2display_memory_font2('0', x + 6, y);
    char2display_memory_font2(year_h + 48, x + 12, y);
    char2display_memory_font2(year_l + 48, x + 18, y);
    char2display_memory_font3(7, x + 24, y);
    display_refresh();
}

void set_brightness_page(int8 x, int8 y)
{
    char2display_memory_font3(11, x, y);
    char2display_memory_font3(12, x + 8, y);
    char2display_memory_font1(59, x + 15, y); // ：
    char2display_memory_font2(brightness + 48 + 1, x + 18, y);
    display_refresh();
}

void synchronize_time_page(int8 x, int8 y)
{
    char2display_memory_font3(13, x, y);
    char2display_memory_font3(14, x + 8, y);
    if (WiFi.status() == WL_CONNECTED)
    {
        char2display_memory_font3(23, x + 8 + 8, y);
        char2display_memory_font3(24, x + 8 + 8 + 8, y);
    }
    else
    {
        char2display_memory_font3(25, x + 8 + 8, y);
        char2display_memory_font3(24, x + 8 + 8 + 8, y);
    }
    display_refresh();
}

void connect_page(int8 x, int8 y)
{
    char2display_memory_font3(15, x, y);
    char2display_memory_font3(16, x + 8, y);
    char2display_memory_font3(17, x + 8 + 8, y);
    display_refresh();
}

void connect_success_page(int8 x, int8 y)
{
    char2display_memory_font3(15, x, y);
    char2display_memory_font3(16, x + 8, y);
    char2display_memory_font3(18, x + 16, y);
    char2display_memory_font3(19, x + 24, y);
    display_refresh();
}

void connect_failed_page(int8 x, int8 y)
{
    char2display_memory_font3(15, x, y);
    char2display_memory_font3(16, x + 8, y);
    char2display_memory_font3(26, x + 16, y);
    char2display_memory_font3(27, x + 24, y);
    display_refresh();
}

void wifi_config_page(int8 x, int8 y)
{
    char2display_memory_font3(32, x, y);
    char2display_memory_font3(33, x + 8, y);
    char2display_memory_font3(34, x + 16, y);
    char2display_memory_font3(35, x + 24, y);
    display_refresh();
}

void initial_page(int8 x, int8 y)
{
    char2display_memory_font3(36, x, y);
    char2display_memory_font3(37, x + 8, y);
    char2display_memory_font3(38, x + 16, y);
    display_refresh();
}

void success_page(int8 x, int8 y)
{
    char2display_memory_font3(18, x, y);
    char2display_memory_font3(19, x + 8, y);
    display_refresh();
}
void get_time()
{

    readRTC_time(&now_hour, &now_minute, &now_second);
    if (now_hour < 10)
    {
        hour_h = 0;
        hour_l = now_hour;
    }
    if (now_hour >= 10)
    {
        hour_h = now_hour / 10;
        hour_l = now_hour % 10;
    }
    if (now_minute < 10)
    {
        minute_h = 0;
        minute_l = now_minute;
    }
    if (now_minute >= 10)
    {
        minute_h = now_minute / 10;
        minute_l = now_minute % 10;
    }
    if (now_second < 10)
    {
        second_h = 0;
        second_l = now_second;
    }
    if (now_second >= 10)
    {
        second_h = now_second / 10;
        second_l = now_second % 10;
    }
}

void get_date()
{
    readRTC_date(&year, &month, &day, &week);
    year_h = year / 10;
    year_l = year % 10;
    if (month < 10)
    {
        month_h = 0;
        month_l = month;
    }
    if (month >= 10)
    {
        month_h = month / 10;
        month_l = month % 10;
    }
    if (day < 10)
    {
        day_h = 0;
        day_l = day;
    }
    if (day >= 10)
    {
        day_h = day / 10;
        day_l = day % 10;
    }
}