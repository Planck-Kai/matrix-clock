#include "wifi_config.h"

const char *default_ap_ssid = "ESP8266_Config";
const char *default_ap_password = "12345678";
ESP8266WebServer server(80);

// 启动热点模式
void startHotspot()
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(default_ap_ssid, default_ap_password);
    Serial.print("热点模式启动，IP地址: ");
    Serial.println(WiFi.softAPIP());
}

// 读取EEPROM中的Wi-Fi信息
String readEEPROM(int start, int len)
{
    String data = "";
    for (int i = start; i < start + len; i++)
    {
        char c = char(EEPROM.read(i));
        if (c == '\0')
            break;
        data += c;
    }
    return data;
}

// 写入EEPROM
void writeEEPROM(int start, String data)
{
    for (int i = 0; i < data.length(); i++)
    {
        EEPROM.write(start + i, data[i]);
    }
    EEPROM.write(start + data.length(), '\0'); // 写入结束符
    EEPROM.commit();
}

void handleRoot()
{
    if (server.method() == HTTP_POST)
    {
        String ssid = server.arg("ssid");
        String password = server.arg("password");

        Serial.println("收到的SSID: " + ssid);
        Serial.println("收到的密码: " + password);

        // 保存到EEPROM
        writeEEPROM(SSID_ADDR, ssid);
        writeEEPROM(PASS_ADDR, password);
        Serial.println("Wi-Fi信息已保存到EEPROM");

        // 尝试连接到指定Wi-Fi
        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(), password.c_str());
        for (int y = 8; y >= 0; y--)
        {
            connect_page(4, y);
            clear_display_memory();
            delay(30);
        }
        int retryCount = 0;
        while (WiFi.status() != WL_CONNECTED && retryCount < 20)
        {
            delay(500);
            Serial.print(".");
            retryCount++;
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\nWi-Fi连接成功！");
            Serial.print("设备IP地址: ");
            Serial.println(WiFi.localIP());
            for (int y = 8; y >= 0; y--)
            {
                connect_success_page(0, y);
                clear_display_memory();
                delay(30);
            }
            connect_success_page(0, 0);
            delay(2000);
            timeClient.begin();
            ntp_adjust_time();
            ntp_adjust_time();
            server.send(200, "text/html", "连接成功！设备已连接到Wi-Fi，刷新页面查看状态。");
        }
        else
        {
            Serial.println("\nWi-Fi连接失败，回到热点模式...");
            for (int y = 8; y >= 0; y--)
            {
                connect_failed_page(0, y);
                clear_display_memory();
                delay(30);
            }
            connect_failed_page(0, 0);
            delay(2000);
        }
    }
    else
    {
        // GET请求时返回配网页面
        String html = "<!DOCTYPE html><html>";
        html += "<head><meta charset=\"UTF-8\">";
        html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
        html += "<title>ESP8266 配网</title>";
        html += "<style>";
        html += "body { font-family: Arial, sans-serif; background-color: #f2f2f2; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
        html += ".container { background: white; padding: 20px; border-radius: 10px; box-shadow: 0 0 10px rgba(0,0,0,0.1); width: 90%; max-width: 400px; }";
        html += "h1 { text-align: center; font-size: 1.5em; margin-bottom: 20px; }";
        html += "input[type='text'], input[type='password'] { width: 100%; padding: 10px; margin: 8px 0; box-sizing: border-box; border: 1px solid #ccc; border-radius: 5px; }";
        html += "input[type='submit'] { width: 100%; background-color: #4CAF50; color: white; padding: 10px; border: none; border-radius: 5px; cursor: pointer; font-size: 1em; }";
        html += "input[type='submit']:hover { background-color: #45a049; }";
        html += "</style></head>";
        html += "<body><div class='container'>";
        html += "<h1>ESP8266 Wi-Fi 配网</h1>";
        html += "<form action='/' method='POST'>"; // 重点：action为'/'
        html += "<label>WiFi名称:</label><input type='text' name='ssid' required>";
        html += "<label>密码:</label><input type='password' name='password'>";
        html += "<input type='submit' value='连接'>";
        html += "</form></div></body></html>";

        server.send(200, "text/html", html);
    }
}

void wifi_init()
{
    Serial.println("Wi-Fi初始化...");
    String saved_ssid = readEEPROM(SSID_ADDR, 32);     // 读取保存的SSID
    String saved_password = readEEPROM(PASS_ADDR, 32); // 读取保存的密码
    if (saved_ssid.length() > 0 && saved_password.length() > 0)
    {
        Serial.println("尝试连接保存的Wi-Fi...");
        for (int y = 8; y >= 0; y--)
        {
            connect_page(4, y);
            clear_display_memory();
            delay(30);
        }
        WiFi.begin(saved_ssid.c_str(), saved_password.c_str());
        int retryCount = 0;
        while (WiFi.status() != WL_CONNECTED && retryCount < 20)
        {
            delay(500);
            Serial.print(".");
            retryCount++;
        }
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\nWi-Fi连接成功！");
            Serial.print("设备IP地址: ");
            for (int y = 8; y >= 0; y--)
            {
                connect_page(4, y - 8);
                connect_success_page(0, y);
                clear_display_memory();
                delay(30);
            }
            connect_success_page(0, 0);
            delay(100);
            Serial.println(WiFi.localIP());
            timeClient.begin();
            ntp_adjust_time();
            ntp_adjust_time();
        }
        else
        {
            Serial.println("\nWi-Fi连接失败，启动热点模式...");
            // startHotspot();
            for (int y = 8; y >= 0; y--)
            {
                connect_page(4, y - 8);
                connect_failed_page(0, y);
                clear_display_memory();
                delay(30);
            }
            connect_failed_page(0, 0);
            delay(2000);
        }
    }
    else
    {
        Serial.println("无保存的Wi-Fi信息，启动热点模式...");
        startHotspot();
        for (int y = 8; y >= 0; y--)
        {
            wifi_config_page(0, y);
            clear_display_memory();
            delay(30);
        }
        wifi_config_page(0, 0);
        for (int a = 0; a <= 8; a++)
        {
            if (a % 2 == 0)
                max7219_set_brightness(brightness + 1);
            else
                max7219_set_brightness(brightness);
            delay(800);
        }
    }
    server.on("/", handleRoot); // 配网页面
    server.begin();
    clear_Display();
}
