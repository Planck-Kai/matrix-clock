#include "max7219.h"

const unsigned short InitArr[7][2] = {
    {0x0C, 0x00}, // display off
    {0x00, 0xFF}, // no LEDtest
    {0x09, 0x00}, // BCD off
    {0x0F, 0x00}, // normal operation
    {0x0B, 0x07}, // start display
    {0x0A, 0x04}, // brightness
    {0x0C, 0x01}  // display on
};

int8 display_memory[8][32] = {0};

//**************************************************************************************************
void max7219_init() // all MAX7219 init
{
    pinMode(CS, OUTPUT);
    digitalWrite(CS, HIGH);
    SPI.begin();

    unsigned short i, j;
    for (i = 0; i < 7; i++)
    {
        digitalWrite(CS, LOW);
        delayMicroseconds(1);
        for (j = 0; j < anzMAX; j++)
        {
            SPI.write(InitArr[i][0]); // register
            SPI.write(InitArr[i][1]); // value
        }
        digitalWrite(CS, HIGH);
    }
    EEPROM.begin(EEPROM_SIZE); // 初始化EEPROM
    int8 read_brightness = (int8)(readEEPROM(brightness_addr, 3).toInt());
    if (read_brightness >= 0 && 5 > read_brightness)
    {
        brightness = read_brightness;
        max7219_set_brightness(brightness);
    }
    else
    {
        max7219_set_brightness(0);
    }
    int8 read_clock_style = (int8)(readEEPROM(clock_style_addr, 3).toInt());
    if (read_clock_style >= 1 && 5 >= read_clock_style)
    {
        clock_style = read_clock_style;
    }
    else
    {
        clock_style = 1;
    }
}
//**************************************************************************************************
void max7219_display_off()
{
    unsigned short j;
    digitalWrite(CS, LOW);
    delayMicroseconds(1);
    for (j = 0; j < anzMAX; j++)
    {
        SPI.write(0x0C); // register
        SPI.write(0x00); // value
    }
    digitalWrite(CS, HIGH);
}
//**************************************************************************************************
void max7219_display_on()
{
    unsigned short j;
    digitalWrite(CS, LOW);
    delayMicroseconds(1);
    for (j = 0; j < anzMAX; j++)
    {
        SPI.write(0x0C); // register
        SPI.write(0x01); // value
    }
    digitalWrite(CS, HIGH);
}
//**************************************************************************************************
void max7219_set_brightness(unsigned short br) // brightness MAX7219
{
    unsigned short j;
    if (br < 16)
    {
        digitalWrite(CS, LOW);
        delayMicroseconds(1);
        for (j = 0; j < anzMAX; j++)
        {
            SPI.write(0x0A); // register
            SPI.write(br);   // value
        }
        digitalWrite(CS, HIGH);
    }
}
//**************************************************************************************************
void clear_Display() // clear all
{

    for (int j = 1; j <= 8; j++)
    {
        digitalWrite(CS, LOW);
        delayMicroseconds(1);
        for (int i = 1; i <= anzMAX; i++)
        {

            SPI.write(j);
            SPI.write(0x00);
        }
        digitalWrite(CS, HIGH);
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            display_memory[i][j] = 0;
        }
    }
}
//**************************************************************************************************
void full_Display() // light all
{
    for (int j = 1; j <= 8; j++)
    {
        digitalWrite(CS, LOW);
        delayMicroseconds(1);
        for (int i = 1; i <= anzMAX; i++)
        {

            SPI.write(j);
            SPI.write(0xff);
        }
        digitalWrite(CS, HIGH);
    }
}
//**************************************************************************************************
void clear_display_memory() //  clear display memory
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            display_memory[i][j] = 0;
        }
    }
}
//**************************************************************************************************
void display_refresh()
{
    for (int j = 1; j <= 8; j++)
    {
        digitalWrite(CS, LOW);
        delayMicroseconds(1);

        unsigned char binarynumber = 0;
        for (int a = 0; a < 8; a++)
        {
            binarynumber = (binarynumber << 1) | (display_memory[a][j - 1] & 1);
        }
        unsigned char lowestbit = (binarynumber & 0b00000001); // 修复硬件连接错误
        binarynumber = (binarynumber >> 1) | (lowestbit << 7);
        SPI.write(j);
        SPI.write(binarynumber);
        for (int a = 0; a < 8; a++)
        {
            binarynumber = (binarynumber << 1) | (display_memory[a][j + 8 - 1] & 1);
        }
        lowestbit = (binarynumber & 0b00000001); // 修复硬件连接错误
        binarynumber = (binarynumber >> 1) | (lowestbit << 7);
        SPI.write(j);
        SPI.write(binarynumber);
        for (int a = 0; a < 8; a++)
        {
            binarynumber = (binarynumber << 1) | (display_memory[a][j + 16 - 1] & 1);
        }
        lowestbit = (binarynumber & 0b00000001); // 修复硬件连接错误
        binarynumber = (binarynumber >> 1) | (lowestbit << 7);
        SPI.write(j);
        SPI.write(binarynumber);
        for (int a = 0; a < 8; a++)
        {
            binarynumber = (binarynumber << 1) | (display_memory[a][j + 24 - 1] & 1);
        }
        lowestbit = (binarynumber & 0b00000001); // 修复硬件连接错误
        binarynumber = (binarynumber >> 1) | (lowestbit << 7);
        SPI.write(j);
        SPI.write(binarynumber);

        digitalWrite(CS, HIGH);
    }
}
//**************************************************************************************************
void char2display_memory_font1(unsigned short ch, int PosX, int PosY)
{

    unsigned short k = ch - 48; // 字符在 font1 中的索引

    // 计算字体列起点、显示列起点和写入列数
    int font_col_start = 0;
    int disp_col_start = PosX;
    int write_cols = 4;

    if (PosX < 0)
    {
        font_col_start = -PosX;
        disp_col_start = 0;
        write_cols = 4 + PosX; // PosX为负时
    }
    else if (PosX > 28)
    {
        write_cols = 4 - (PosX - 28);
    }

    // 边界检查
    if (write_cols <= 0 || font_col_start >= 4 || disp_col_start >= 32)
        return;

    for (int i = 0; i < write_cols; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (PosY >= 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font1[k][font_col_start + i] >> PosY) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
            if (PosY < 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font1[k][font_col_start + i] << abs(PosY)) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
        }
    }
}

//**************************************************************************************************
void char2display_memory_font2(unsigned short ch, int PosX, int PosY)
{
    unsigned short k = ch - 48; // ASCII 在 font2 里的索引

    int font_col_start = 0; // 计算写入的起始字体列和起始显示列
    int disp_col_start = PosX;
    int write_cols = 5;
    if (PosX < 0)
    {
        font_col_start = -PosX; // 字体起始列向右偏移
        disp_col_start = 0;     // 显示从最左侧开始
        write_cols = 5 + PosX;  // 可写入的列数减少
    }
    else if (PosX > 27)
    {
        write_cols = 5 - (PosX - 27); // 可写入的列数减少
    }
    // 边界检查
    if (write_cols <= 0 || font_col_start >= 5 || disp_col_start >= 32)
        return;

    // 写入像素
    for (int i = 0; i < write_cols; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (PosY >= 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font2[k][font_col_start + i] >> PosY) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
            if (PosY < 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font2[k][font_col_start + i] << abs(PosY)) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
        }
    }
}
//**************************************************************************************************
void char2display_memory_font3(unsigned short ch, int PosX, int PosY)
{
    unsigned short k;
    k = ch;
    int font_col_start = 0; // 计算写入的起始字体列和起始显示列
    int disp_col_start = PosX;
    int write_cols = 8;
    if (PosX < 0)
    {
        font_col_start = -PosX; // 字体起始列向右偏移
        disp_col_start = 0;     // 显示从最左侧开始
        write_cols = 8 + PosX;  // 可写入的列数减少
    }
    else if (PosX > 24)
    {
        write_cols = 8 - (PosX - 24); // 可写入的列数减少
    }
    // 边界检查
    if (write_cols <= 0 || font_col_start >= 8 || disp_col_start >= 32)
        return;
    // 写入像素
    for (int i = 0; i < write_cols; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (PosY >= 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font3[k][font_col_start + i] >> PosY) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
            if (PosY < 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font3[k][font_col_start + i] << abs(PosY)) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
        }
    }
}

void char2display_memory_font4(unsigned short ch, int PosX, int PosY)
{
    unsigned short k;
    k = ch - 48; // ASCII position in font

    int font_col_start = 0; // 计算写入的起始字体列和起始显示列
    int disp_col_start = PosX;
    int write_cols = 3;
    if (PosX < 0)
    {
        font_col_start = -PosX; // 字体起始列向右偏移
        disp_col_start = 0;     // 显示从最左侧开始
        write_cols = 3 + PosX;  // 可写入的列数减少
    }
    else if (PosX > 29)
    {
        write_cols = 3 - (PosX - 29); // 可写入的列数减少
    }
    // 边界检查
    if (write_cols <= 0 || font_col_start >= 3 || disp_col_start >= 32)
        return;

    // 写入像素
    for (int i = 0; i < write_cols; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (PosY >= 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font4[k][font_col_start + i] >> PosY) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
            if (PosY < 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font4[k][font_col_start + i] << abs(PosY)) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
        }
    }
}

void char2display_memory_font5(unsigned short ch, int PosX, int PosY)
{
    unsigned short k;
    k = ch - 48; // ASCII position in font

    int font_col_start = 0; // 计算写入的起始字体列和起始显示列
    int disp_col_start = PosX;
    int write_cols = 6;
    if (PosX < 0)
    {
        font_col_start = -PosX; // 字体起始列向右偏移
        disp_col_start = 0;     // 显示从最左侧开始
        write_cols = 6 + PosX;  // 可写入的列数减少
    }
    else if (PosX > 26)
    {
        write_cols = 6 - (PosX - 26); // 可写入的列数减少
    }
    // 边界检查
    if (write_cols <= 0 || font_col_start >= 6 || disp_col_start >= 32)
        return;

    // 写入像素
    for (int i = 0; i < write_cols; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (PosY >= 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font5[k][font_col_start + i] >> PosY) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
            if (PosY < 0)
            {
                display_memory[j][disp_col_start + i] =
                    (((font5[k][font_col_start + i] << abs(PosY)) >> (7 - j)) & 1) | (display_memory[j][disp_col_start + i]);
            }
        }
    }
}