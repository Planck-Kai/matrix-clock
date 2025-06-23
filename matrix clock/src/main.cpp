#include "max7219.h"
#include "rx8025.h"
#include "Ticker.h"
#include "global_variables.h"
#include "pages.h"
#include "button.h"
#include "wifi_config.h"
Ticker myTimer;
Ticker myTimer2;
void callback_1()
{
    my_time++;
    if (my_time > 100)
    {
        my_time = 0;
    }
}
void callback_2()
{

    if (dog_posx == 15)
    {
        dog_posx = 0;
    }
    dog_posx++;
}

void setup()
{
    Serial.begin(115200);
    myTimer.attach_ms(10, callback_1);
    myTimer2.attach_ms(500, callback_2);
    RX8025_Init();
    max7219_init();
    clear_Display();
    wifi_init();
    get_time();
    for (int y = 9; y >= 0; y--)
    {
        switch (clock_style)
        {
        case 1:
            clock_page_style_1(3, y);
            break;
        case 2:
            clock_page_style_2(1, y);
            break;
        case 3:
            clock_page_style_3(2, y);
            break;
        case 4:
            clock_page_style_4(0, y);
            break;
        case 5:
            clock_page_style_5(0, y);
            break;
        }
        clear_display_memory();
        delay(30);
    }
    button_init();
}

void loop()
{
    switch (page)
    {
    case 1:
        get_time();
        switch (clock_style)
        {
        case 1:
            clock_page_style_1(3, 0);
            break;
        case 2:
            clock_page_style_2(1, 0);
            break;
        case 3:
            clock_page_style_3(2, 0);
            break;
        case 4:
            clock_page_style_4(0, 0);
            break;
        case 5:
            clock_page_style_5(0, 0);
            break;
        }
        clear_display_memory();
        break;
    case 2:
        get_date();
        switch (date_style)
        {
        case 1:
            date_page_week(4, 0);
            break;
        case 2:
            date_page_month(0, 0);
            break;
        case 3:
            date_page_year(1, 0);
            break;
        }
        clear_display_memory();
        break;
    case 3:
        set_brightness_page(4, 0);
        clear_display_memory();
        break;
    case 4:
        synchronize_time_page(0, 0);
        clear_display_memory();
        break;
    }
    button_run();
    server.handleClient();
}
