#include <Arduino.h>
#include <Wire.h>

#include "config_definition_uno.h"
#include "display_control.h"
#include "serial_com_control.h"
#include "led_control.h"
#include "sonar_control.h"
#include "forward_collision_avoidance_assist.h"

zone_mode_t zone_status = unsafe_zone;
boolean fca_active = true;

boolean is_fca_active()
{
   return fca_active;
}

zone_mode_t Get_zone()
{
   return zone_status;
}

void disable_fca()
{
   fca_active = false;
}

void enable_fca()
{
   fca_active = true;
}

void fca_main(connection_status_t connection_status)
{
   if( fca_active )
   {
      unsigned int distance = Get_last_measured_distance();
      if( distance < EMERGENCY_STOP_DISTANCE && distance != 0u )
      {
         serial_write(SERIAL_COM_COMMAND__unsafe_distance);
         if(zone_status == safe_zone)
         {
            zone_status = unsafe_zone;
            update_lcd_display_text(connection_status, SERIAL_COM_COMMAND__unsafe_distance);
         }
      }
      else
      {
         serial_write(SERIAL_COM_COMMAND__safe_distance);
         if(zone_status == unsafe_zone)
         {
            zone_status = safe_zone;
            update_lcd_display_text(connection_status, SERIAL_COM_COMMAND__safe_distance);
         }
      }
   }
   else
   {
      serial_write(SERIAL_COM_COMMAND__safe_distance);
   }
}