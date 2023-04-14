#include <Arduino.h>
#include <Wire.h>

#include "config_definition_uno.h"
#include "display_control.h"
#include "serial_com_control.h"
#include "led_control.h"
#include "sonar_control.h"
#include "forward_collision_avoidance_assist.h"

connection_status_t connection_status = status_unconnected;

void controller_main()
{
  byte serial_command;
  if (GetD_serial_message(&serial_command))
  { 
    switch (serial_command)
    {
      case SERIAL_COM_COMMAND__stop:
      case SERIAL_COM_COMMAND__forward:
      case SERIAL_COM_COMMAND__backward:
      case SERIAL_COM_COMMAND__right:
      case SERIAL_COM_COMMAND__left:
        update_lcd_display_text(connection_status, serial_command);
        break;
        
      case SERIAL_COM_COMMAND__led:
        toggle_led_headlight();
        update_lcd_display_text(connection_status, SERIAL_COM_COMMAND__led);
        break;

      case SERIAL_COM_COMMAND__disconnected:
      case SERIAL_COM_COMMAND__connected:
        if( connection_status != (connection_status_t)serial_command )
        {
          connection_status = (connection_status_t)serial_command;
          update_lcd_display_text(connection_status, serial_command);
        }
        break;
      
      case SERIAL_COM_COMMAND__lcd:
        toggle_lcd_backlight();
        update_lcd_display_text(connection_status, SERIAL_COM_COMMAND__lcd);
        break;

      case SERIAL_COM_COMMAND__info:
        Next_display_info_mode();
        update_lcd_display_text(connection_status, SERIAL_COM_COMMAND__info);
        break;

      case SERIAL_COM_COMMAND__fca:
        (is_fca_active() == true) ? disable_fca() : enable_fca();
        update_lcd_display_text(connection_status, SERIAL_COM_COMMAND__fca);
        break;
      
      default:
        /* unrecognized command received */
        break;
    }
  }
}

void setup()
{
  initialize_led_controller();
  initialize_lcd_display();
  initialize_serial_com();
  initialize_sonar();
}

void loop()
{
  fca_main(connection_status);
  controller_main();
  display_main(connection_status);
  sonar_main();
  led_main(connection_status);
}