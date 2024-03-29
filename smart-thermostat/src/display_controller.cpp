#include "display_controller.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, OLED_SDA_PIN, OLED_SCL_PIN, U8X8_PIN_NONE); 
Timer display_timer;

#define wifi_16_width 16
#define wifi_16_height 16
static unsigned char wifi_16_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x0c, 0x30,
   0xc4, 0x23, 0x30, 0x0c, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x80, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define thermometer_24_width 24
#define thermometer_24_height 24
static unsigned char thermometer_24_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0xe4, 0x00,
   0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0xe4, 0x00, 0x00, 0x24, 0x00,
   0x00, 0x66, 0x00, 0x00, 0xc3, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00,
   0x00, 0x81, 0x00, 0x00, 0xc3, 0x00, 0x00, 0xe7, 0x00, 0x00, 0x3c, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define fire_20_width 20
#define fire_20_height 20
static unsigned char fire_20_bits[] = 
{
   0x00, 0x03, 0x00, 0x00, 0x05, 0x00, 0x00, 0x09, 0x00, 0x80, 0x10, 0x00,
   0x80, 0x20, 0x00, 0x40, 0x40, 0x00, 0x20, 0x84, 0x00, 0x10, 0x0c, 0x01,
   0x10, 0x14, 0x01, 0x08, 0x14, 0x02, 0x04, 0x24, 0x02, 0xc4, 0x24, 0x02,
   0x44, 0x23, 0x00, 0x00, 0x20, 0x00, 0x40, 0x20, 0x02, 0x44, 0x00, 0x02,
   0x84, 0x10, 0x02, 0x08, 0x00, 0x01, 0x10, 0x80, 0x00, 0xe0, 0x40, 0x00 
};

#define day_24_width 24
#define day_24_height 24
static unsigned char day_24_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00,
   0x00, 0x18, 0x00, 0x60, 0x18, 0x06, 0xe0, 0x00, 0x07, 0xc0, 0x7e, 0x03,
   0x00, 0xe7, 0x00, 0x80, 0x81, 0x01, 0x80, 0x81, 0x01, 0xb8, 0x00, 0x1d,
   0xb8, 0x00, 0x1d, 0x80, 0x81, 0x01, 0x80, 0x81, 0x01, 0x00, 0xe7, 0x00,
   0xc0, 0x7e, 0x03, 0xe0, 0x00, 0x07, 0x60, 0x18, 0x06, 0x00, 0x18, 0x00,
   0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};


#define night_24_width 24
#define night_24_height 24
static unsigned char night_24_bits[] = 
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
   0x00, 0x00, 0x1e, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x76, 0x00, 0x3e, 0x66,
   0x00, 0x7f, 0x63, 0x80, 0xff, 0x63, 0xe0, 0xff, 0x71, 0xf8, 0xff, 0x39,
   0xf8, 0xff, 0x1f, 0xfc, 0xff, 0x0f, 0xfc, 0xff, 0x1f, 0xfc, 0xff, 0x1f,
   0xfc, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x0f, 0xe0, 0xff, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};



void initialize_display_controller()
{
   u8g2.begin();
   display_timer.setInterval(DISPLAY_REFRESH_RATE);
   display_timer.setCallback(display_callback);
   display_timer.start();
   display_main_window();
}

void display_controller_main()
{
   display_timer.update();
}

void display_callback()
{
   display_timer.stop();
   display_main_window();
   display_timer.start();
}

void display_main_window()
{
   u8g2.clearBuffer();
   u8g2.setFont(u8g2_font_t0_14_tr);

   if( Get_connection_status() == true )
   {
      // Wifi connected
      u8g2.drawXBM( 1, 1, wifi_16_width, wifi_16_height, wifi_16_bits);
   }
   else
   {
      // Wifi NOT connected
   }

   // Clock
   String time = Get_NTP_time();
   u8g2.drawStr( 23, 15, &time[0]);
   u8g2.setFont(u8g2_font_smallsimple_tr);
   String day = Get_NTP_day();
   u8g2.drawStr( 62, 15, &day[0]);
   

   // Target temperature
   u8g2.setFont(u8g2_font_smallsimple_tr);
   String target = Get_HeatingTarget_string();
   u8g2.drawStr( 105, 10, &target[0]);
   u8g2.setFont(u8g2_font_t0_14_tr);

   // Temperature
   u8g2.drawXBM(  15, 22, thermometer_24_width, thermometer_24_height, thermometer_24_bits);
   
   // Current temperature
   if(Get_AHT10_status() == aht10_initialized)
   {
      String temp = Get_AHT10_last_measured_temperature_string();
      u8g2.drawStr( 37, 39, &temp[0]);
   }
   else
   {
      u8g2.drawStr( 37, 39, "--.--");
   }
   
   
   if( day_night_calculation() == day_time )
      u8g2.drawXBM( 80, 22, day_24_width, day_24_height, day_24_bits);
   else
      u8g2.drawXBM( 80, 22, night_24_width, night_24_height, night_24_bits);
   
   // command
   u8g2.setFont(u8g2_font_smallsimple_tr);
   String min = Get_HeatingNegativeLimit_string();
   String max = Get_HeatingPositiveLimit_string();
   String limits = "ON: " + min + "   OFF: " + max;
   u8g2.drawStr( 1, 62, &limits[0]);

   // heating progress bitmap
   if( Heating_is_in_progress())
   {
      u8g2.drawXBM( 103, 42, fire_20_width, fire_20_height, fire_20_bits);
   }

   u8g2.sendBuffer();
}

void display_setPowerSaveMode(oled_status_t status)
{
   u8g2.clearBuffer();
   u8g2.clearDisplay();
   u8g2.setPowerSave((status == oled_on) ? 0 : 1);
} 