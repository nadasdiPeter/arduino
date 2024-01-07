#include "message_handler.h"

extern void get_temperature_handler();
extern void get_humidity_handler();
extern void oled_handler(oled_status_t status);

bool message(message_t msg) 
{
   switch(msg)
   {
      case wifi_connecting:
         display_print_5_line("Connecting to wifi...");
         break;

      case wifi_connected:
         display_print_5_line("Wifi connected", &GetIP()[0], &GetMAC()[0], "", "");
         send_message_forced(">> <b>Restart</b>\nHello, I'm online!");
         break;

      case get_temperature:
         get_temperature_handler();
         break;

      case get_humidity:
         get_humidity_handler();
         break;

      case oled_setOn:
         oled_handler(oled_on);
         break;

      case oled_setOff:
         oled_handler(oled_off);
         break;

      default:
      break;
   }

   return true;
}

void get_temperature_handler()
{
   String temperature = Get_AHT10_actual_temperature_string() + " C";
   display_print_2_line("Temperature", &temperature[0] );
   send_message_forced(">> <b>Temperature</b>\n" + temperature);
}

void get_humidity_handler()
{
   String humidity = Get_AHT10_actual_humidity_string() + " %";
   display_print_2_line("Humidity:", &humidity[0]);
   send_message_forced(">> <b>Humidity</b>\n" + humidity);
}

void oled_handler(oled_status_t status)
{
   if(status == oled_on)
   {
      send_message_forced(">> <b>Display</b>\nDisplay turned on.");
   }
   else
   {
      send_message_forced(">> <b>Display</b>\nDisplay turned off.");
   }
}