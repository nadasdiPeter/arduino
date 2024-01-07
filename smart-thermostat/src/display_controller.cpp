#include "display_controller.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, OLED_SDA_PIN, OLED_SCL_PIN, U8X8_PIN_NONE); 
Timer display_timer;
bool toogle_state = false;

extern void display_callback();

void initialize_display_controller()
{
   u8g2.begin();
   u8g2.enableUTF8Print();
   display_timer.setInterval(5000);
   display_timer.setCallback(display_callback);
   display_timer.start();
}

void display_controller_main()
{
   display_timer.update();
}

void display_callback()
{
   display_timer.stop();
   if(toogle_state)
   {
      String temperature = Get_AHT10_last_measured_temperature_string() + "";
      display_print_temperature(&temperature[0]);
   }
   else
   {
      String humidity = Get_AHT10_actual_humidity_string() + "";
      display_print_humidity(&humidity[0]);
   }
   toogle_state = !toogle_state;
   display_timer.start();
}

void display_print_5_line(const char* line_0, const char* line_1, const char* line_2, const char* line_3, const char* line_4)
{
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_ncenB08_tf);
   u8g2.drawStr(0,10, line_0);
   u8g2.drawStr(0,25, line_1);
   u8g2.drawStr(0,35, line_2);
   u8g2.drawStr(0,45, line_3);
   u8g2.drawStr(0,55, line_4);
   u8g2.sendBuffer();
}

void display_print_2_line(const char* line_0, const char* line_1)
{
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_ncenB08_tf);
   u8g2.drawStr(0,10, line_0);
   u8g2.setFont(u8g2_font_ncenB18_tf);
   u8g2.drawStr(0,50, line_1);
   u8g2.sendBuffer();
}

void display_print_temperature(const char* temperature)
{
   const char DEGREE_SYMBOL[] = { 0xB0, '\0' };
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_ncenB08_tf);
   u8g2.drawStr(20, 15, "Temperature");
   u8g2.setFont(u8g2_font_ncenB18_tf);
   u8g2.drawStr(0, 55, temperature);
   u8g2.drawUTF8(65, 55, DEGREE_SYMBOL);
   u8g2.drawStr(75, 55, "C");
   u8g2.sendBuffer();
}

void display_print_humidity(const char* humidity)
{
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_ncenB08_tf);
   u8g2.drawStr(20, 15, "Humidity");
   u8g2.setFont(u8g2_font_ncenB18_tf);
   u8g2.drawStr(0, 55, humidity);
   u8g2.drawStr(65, 55, "%");
   u8g2.sendBuffer();
}

void display_setPowerSaveMode(oled_status_t status)
{
   u8g2.setPowerSave((status == oled_on) ? 0 : 1);
}