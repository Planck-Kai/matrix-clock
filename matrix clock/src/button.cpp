#include <button.h>

// 创建一个 OneButton 实例，参数为按键引脚号和是否为低电平有效
OneButton button1(12, true);
OneButton button2(0, true);
OneButton button3(2, true);

void button_init()
{
    pinMode(12, INPUT_PULLUP);
    button1.attachClick(button1_click);
    button2.attachClick(button2_click);
    button3.attachClick(button3_click);
    button2.attachLongPressStart(button2_longpress);
}
void button_run()
{
    button1.tick();
    button2.tick();
    button3.tick();
}
// 单击回调
void button1_click()
{
    page++;
    if (page == 2)
    {
        for (int8 x = 0; x <= 32; x++)
        {
            get_time();
            get_date();
            switch (clock_style)
            {
            case 1:
                clock_page_style_1(3 + x, 0);
                break;
            case 2:
                clock_page_style_2(1 + x, 0);
                break;
            case 3:
                clock_page_style_3(2 + x, 0);
                break;
            case 4:
                clock_page_style_4(0 + x, 0);
                break;
            case 5:
                clock_page_style_5(0 + x, 0);
                break;
            }
            switch (date_style)
            {
            case 1:
                date_page_week(4 + x - 32, 0);
                break;
            case 2:
                date_page_month(0 + x - 32, 0);
                break;
            case 3:
                date_page_year(1 + x - 32, 0);
                break;
            }
            delay(12);
            clear_display_memory();
        }
    }
    if (page == 3)
    {
        for (int8 x = 0; x <= 32; x++)
        {
            get_time();
            get_date();
            switch (date_style)
            {
            case 1:
                date_page_week(4 + x, 0);
                break;
            case 2:
                date_page_month(0 + x, 0);
                break;
            case 3:
                date_page_year(1 + x, 0);
                break;
            }
            set_brightness_page(4 + x - 32, 0);
            delay(12);
            clear_display_memory();
        }
    }
    if (page == 4)
    {
        for (int8 x = 0; x <= 32; x++)
        {
            set_brightness_page(4 + x, 0);
            synchronize_time_page(0 + x - 32, 0);
            delay(12);
            clear_display_memory();
        }
    }
    if (page == 5)
    {
        page = 1;
        for (int8 x = 0; x <= 32; x++)
        {
            synchronize_time_page(0 + x, 0);
            get_time();
            switch (clock_style)
            {
            case 1:
                clock_page_style_1(3 + x - 32, 0);
                break;
            case 2:
                clock_page_style_2(1 + x - 32, 0);
                break;
            case 3:
                clock_page_style_3(2 + x - 32, 0);
                break;
            case 4:
                clock_page_style_4(0 + x - 32, 0);
                break;
            case 5:
                clock_page_style_5(0 + x - 32, 0);
            }
            delay(12);
            clear_display_memory();
        }
    }
}

void button2_click()
{
    if (page == 1)
    {
        clock_style++;
        if (clock_style == 2)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                get_time();
                clock_page_style_1(3, y);
                clock_page_style_2(1, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        if (clock_style == 3)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                get_time();
                clock_page_style_2(1, y);
                clock_page_style_3(2, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        if (clock_style == 4)
        {

            for (int8 y = 0; y >= -8; y--)
            {
                get_time();
                clock_page_style_3(2, y);
                clock_page_style_4(0, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        if (clock_style == 5)
        {

            for (int8 y = 0; y >= -8; y--)
            {
                get_time();
                clock_page_style_4(0, y);
                clock_page_style_5(0, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        if (clock_style == 6)
        {
            clock_style = 1;
            for (int8 y = 0; y >= -8; y--)
            {
                get_time();
                clock_page_style_5(0, y);
                clock_page_style_1(3, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        writeEEPROM(clock_style_addr, String(clock_style));
    }
    if (page == 2)
    {
        date_style++;
        if (date_style == 2)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                get_date();
                date_page_week(4, y);
                date_page_month(0, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        if (date_style == 3)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                get_date();
                date_page_month(0, y);
                date_page_year(1, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
        if (date_style == 4)
        {
            date_style = 1;
            for (int8 y = 0; y >= -8; y--)
            {
                get_date();
                date_page_year(1, y);
                date_page_week(4, y + 8);
                delay(30);
                clear_display_memory();
            }
        }
    }
    if (page == 3)
    {
        brightness++;
        if (brightness == 1)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                int8 x = 4;
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 48, x + 18, y);
                display_refresh();
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 1 + 48, x + 18, y + 8);
                display_refresh();
                delay(30);
                clear_display_memory();
            }
        }
        if (brightness == 2)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                int8 x = 4;
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 48, x + 18, y);
                display_refresh();
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 1 + 48, x + 18, y + 8);
                display_refresh();
                delay(30);
                clear_display_memory();
            }
        }
        if (brightness == 3)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                int8 x = 4;
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 48, x + 18, y);
                display_refresh();
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 1 + 48, x + 18, y + 8);
                display_refresh();
                delay(30);
                clear_display_memory();
            }
        }
        if (brightness == 4)
        {
            for (int8 y = 0; y >= -8; y--)
            {
                int8 x = 4;
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 48, x + 18, y);
                display_refresh();
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 1 + 48, x + 18, y + 8);
                display_refresh();
                delay(30);
                clear_display_memory();
            }
        }
        if (brightness == 5)
        {
            brightness = 0;
            for (int8 y = 0; y >= -8; y--)
            {
                int8 x = 4;
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 5 + 48, x + 18, y);
                display_refresh();
                char2display_memory_font3(11, x, 0);
                char2display_memory_font3(12, x + 8, 0);
                char2display_memory_font1(59, x + 15, 0); // ：
                char2display_memory_font2(brightness + 1 + 48, x + 18, y + 8);
                display_refresh();
                delay(30);
                clear_display_memory();
            }
        }
        max7219_set_brightness(brightness);
        writeEEPROM(brightness_addr, String(brightness));
    }
    if (page == 4)
    {
        ntp_adjust_time();
    }
}
void button3_click()
{
    page--;
    if (page == 1)
    {
        for (int8 x = 0; x >= -32; x--)
        {
            get_time();
            get_date();
            switch (clock_style)
            {
            case 1:
                clock_page_style_1(3 + x + 32, 0);
                break;
            case 2:
                clock_page_style_2(1 + x + 32, 0);
                break;
            case 3:
                clock_page_style_3(2 + x + 32, 0);
                break;
            case 4:
                clock_page_style_4(0 + x + 32, 0);
                break;
            case 5:
                clock_page_style_5(0 + x + 32, 0);
                break;
            }
            switch (date_style)
            {
            case 1:
                date_page_week(4 + x, 0);
                break;
            case 2:
                date_page_month(0 + x, 0);
                break;
            case 3:
                date_page_year(1 + x, 0);
                break;
            }
            delay(12);
            clear_display_memory();
        }
    }
    if (page == 2)
    {
        for (int8 x = 0; x >= -32; x--)
        {
            get_date();
            switch (date_style)
            {
            case 1:
                date_page_week(4 + x + 32, 0);
                break;
            case 2:
                date_page_month(0 + x + 32, 0);
                break;
            case 3:
                date_page_year(1 + x + 32, 0);
                break;
            }
            set_brightness_page(4 + x, 0);
            delay(12);
            clear_display_memory();
        }
    }
    if (page == 3)
    {
        for (int8 x = 0; x >= -32; x--)
        {
            synchronize_time_page(0 + x, 0);
            set_brightness_page(4 + x + 32, 0);
            delay(12);
            clear_display_memory();
        }
    }
    if (page == 0)
    {
        page = 4;
        for (int8 x = 0; x >= -32; x--)
        {
            get_time();
            switch (clock_style)
            {
            case 1:
                clock_page_style_1(3 + x, 0);
                break;
            case 2:
                clock_page_style_2(1 + x, 0);
                break;
            case 3:
                clock_page_style_3(2 + x, 0);
                break;
            case 4:
                clock_page_style_4(0 + x, 0);
                break;
            case 5:
                clock_page_style_5(0 + x, 0);
                break;
            }
            synchronize_time_page(0 + x + 32, 0);

            delay(12);
            clear_display_memory();
        }
    }
}
void button2_longpress()
{
    if (page == 4)
    {
        for (int y = 8; y >= 0; y--)
        {
            initial_page(4, y);
            clear_display_memory();
            delay(30);
        }
        initial_page(4, 0);
        delay(1000);
        for (int y = 8; y >= 0; y--)
        {
            initial_page(4, y-8);
            success_page(8, y);
            clear_display_memory();
            delay(30);
        }
        success_page(8, 0);
        delay(1000);
        EEPROM.begin(EEPROM_SIZE);
        for (int i = 0; i < EEPROM_SIZE; i++)
        {
            EEPROM.write(i, 0);
        }
        EEPROM.commit(); // 提交更改
        ESP.restart();   // 安全重启设备
    }
    else
    {
        display_state = !display_state;
        if (display_state == 1)
        {
            max7219_display_on();
        }
        else
        {
            max7219_display_off();
        }
    }
}
