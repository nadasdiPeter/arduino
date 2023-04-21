#include "config_definition_uno.h"
#include "sonar_control.h"
#include "display_control.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "timer.h"
#include "battery_voltage_monitor.h"
#include "state_resister.h"


Timer display_update_cycle;
LiquidCrystal_I2C lcd_display(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
boolean backlight_status                    = true;


void display_main()
{
    display_update_cycle.update();
}

void update_1st_line_command()
{
  String connected_symbol = "[" + (String)((get_connection_status() == status_connected) ? 'c' : 'u') + "] ";
  String distance = "";
  lcd_display.setCursor(0, 0);

  switch( get_display_info_mode())
  {
    case ip_mode:
      lcd_display.print(IP_ADDRESS);
      break;
    case clock_mode:
      lcd_display.print(connected_symbol + String(millis()/1000) + "(s)");
      break;
    case distance_mode:
      distance = (get_last_measured_distance() == 0) ? "- " : String(get_last_measured_distance());
      lcd_display.print(connected_symbol + distance + "(cm)");
      break;
    case voltage_mode:
      lcd_display.print(connected_symbol + String(get_last_measured_voltage()) + "(V)");
      break;
    default:
      /* Not possible. */
      break;
  }
}

void update_2nd_line_command(serial_command_t command)
{
  String arrows = (command.cmd_dir == rx) ? ">> " : "<< ";
  lcd_display.setCursor(0, 1);
  lcd_display.print(arrows + command.cmd_name + " (" + String(command.cmd_id) + ")");
  set_last_command_details(command);
}

void cyclic_display_update_handler() 
{
  if( get_connection_status() == status_connected )
  {
    lcd_display.clear();
    update_1st_line_command();
    update_2nd_line_command(get_last_command_details());
  }
}

void write_unconnected_display_message()
{
  lcd_display.clear();
  lcd_display.setCursor(0, 0);
  lcd_display.print((String)"Wifi: " + (String)WIFI_HOST_NAME);
  lcd_display.setCursor(0, 1);
  lcd_display.print((String)"Pass: " + (String)WIFI_PASSWORD);
}

void initialize_lcd_display()
{
  display_update_cycle.setInterval(DISPLAY_REFRESH_RATE);
  display_update_cycle.setCallback(cyclic_display_update_handler);
  display_update_cycle.start(); 

  lcd_display.init();
  lcd_display.backlight();
  write_unconnected_display_message();
}

void toggle_lcd_backlight()
{
  backlight_status = (backlight_status) ? false : true;
  if(backlight_status == true) lcd_display.backlight();
  else lcd_display.noBacklight();
}


void update_lcd_display_text(int command_id)
{
  if( get_connection_status() == status_connected )
  {
    lcd_display.clear();
    update_1st_line_command();
    if( command_id != 0 )
    {
      lcd_display.setCursor(0, 1);
      switch(command_id)
      {
        case SERIAL_COM_COMMAND__stop:
          update_2nd_line_command(serial_command_t("stop",command_id));
          break;

        case SERIAL_COM_COMMAND__forward:
          update_2nd_line_command(serial_command_t("forward",command_id));
          break;

        case SERIAL_COM_COMMAND__backward:
          update_2nd_line_command(serial_command_t("backward",command_id));
          break;

        case SERIAL_COM_COMMAND__right:
          update_2nd_line_command(serial_command_t("right",command_id));
          break;

        case SERIAL_COM_COMMAND__left:
          update_2nd_line_command(serial_command_t("left",command_id));
          break;

        case SERIAL_COM_COMMAND__connected:
          update_2nd_line_command(serial_command_t("connect",command_id));
          break;

        case SERIAL_COM_COMMAND__led:
          update_2nd_line_command(serial_command_t("led",command_id));
          break;

        case SERIAL_COM_COMMAND__lcd:
          update_2nd_line_command(serial_command_t("lcd",command_id));
          break;

        case SERIAL_COM_COMMAND__info:
          update_2nd_line_command(serial_command_t(get_display_info_mode_text(),command_id));
          break;

        case SERIAL_COM_COMMAND__fca:
          update_2nd_line_command(serial_command_t("fca",command_id));
          break;

        case SERIAL_COM_COMMAND__unsafe_distance:
          update_2nd_line_command(serial_command_t("unsafe",command_id,tx));
          break;

        case SERIAL_COM_COMMAND__safe_distance:
          update_2nd_line_command(serial_command_t("safe",command_id,tx));
          break;

        case SERIAL_COM_COMMAND__turning_mode:
          update_2nd_line_command(serial_command_t("turnmode",command_id));
          break;
          
        default:
          update_2nd_line_command(serial_command_t("undef",command_id));
          break;
      }
    }
  }
  else
  {
    write_unconnected_display_message();
  }
}