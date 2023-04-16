#include "config_definition_uno.h"
#include "sonar_control.h"
#include "display_control.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "timer.h"
#include "battery_voltage_monitor.h"



Timer display_update_cycle;
LiquidCrystal_I2C lcd_display(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
display_info_mode_t display_info_mode       = ip_mode;
boolean backlight_status                    = true;
serial_command_t last_displayed_command     = serial_command_t("undef",0);
msg_direction_t last_displayed_command_dir  = rx;
connection_status_t last_connection_sts     = status_unconnected;



void display_main(connection_status_t connection)
{
    last_connection_sts = connection;
    display_update_cycle.update();
}

void set_display_info_mode(display_info_mode_t mode)
{
  display_info_mode = mode;
}

String get_display_info_mode_text()
{
  switch(display_info_mode)
  {
    case ip_mode: 
      return "ip-port";
    case clock_mode: 
      return "clock";
    case distance_mode: 
      return "distance";
    case voltage_mode: 
      return "voltage";
    default:
      return "info";
  }
}

void next_display_info_mode()
{
  switch(display_info_mode)
  {
    case ip_mode:
      set_display_info_mode(clock_mode);
      break;
    case clock_mode: 
      set_display_info_mode(distance_mode);
      break;
    case distance_mode: 
      set_display_info_mode(voltage_mode);
      break;
    case voltage_mode: 
      set_display_info_mode(ip_mode);
      break;
    default:
      set_display_info_mode(ip_mode);
      break;
  }
}


void update_1st_line_command(connection_status_t connection)
{
  String connected_symbol = "[" + (String)((connection == status_connected) ? 'c' : 'u') + "] ";
  String distance = "";

  lcd_display.setCursor(0, 0);

  switch( display_info_mode )
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
      lcd_display.print(String(get_last_measured_voltage()) + "(V) " + String(get_last_measured_voltage_raw()) + "(-)" );
      break;
    default:
      /* Not possible. */
      break;
  }
}

serial_command_t update_2nd_line_command(serial_command_t command, msg_direction_t msg_dir)
{
  last_displayed_command_dir = msg_dir;
  String arrows = (msg_dir == rx) ? ">> " : "<< ";
  lcd_display.setCursor(0, 1);
  lcd_display.print(arrows + command.cmd_name + " (" + String(command.cmd_id) + ")");
  return command;
}

void cyclic_display_update_handler() 
{
  if( last_connection_sts == status_connected )
  {
    lcd_display.clear();
    update_1st_line_command(last_connection_sts);
    update_2nd_line_command(last_displayed_command, last_displayed_command_dir);
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


void update_lcd_display_text(connection_status_t connection, int command_id)
{
  last_connection_sts = connection;
  if( connection == status_connected )
  {
    lcd_display.clear();
    update_1st_line_command(connection);
    if( command_id != 0 )
    {
      lcd_display.setCursor(0, 1);
      switch(command_id)
      {
        case SERIAL_COM_COMMAND__stop:
          last_displayed_command = update_2nd_line_command(serial_command_t("stop",command_id));
          break;

        case SERIAL_COM_COMMAND__forward:
          last_displayed_command = update_2nd_line_command(serial_command_t("forward",command_id));
          break;

        case SERIAL_COM_COMMAND__backward:
          last_displayed_command = update_2nd_line_command(serial_command_t("backward",command_id));
          break;

        case SERIAL_COM_COMMAND__right:
          last_displayed_command = update_2nd_line_command(serial_command_t("right",command_id));
          break;

        case SERIAL_COM_COMMAND__left:
          last_displayed_command = update_2nd_line_command(serial_command_t("left",command_id));
          break;

        case SERIAL_COM_COMMAND__connected:
          last_displayed_command = update_2nd_line_command(serial_command_t("connect",command_id));
          break;

        case SERIAL_COM_COMMAND__led:
          last_displayed_command = update_2nd_line_command(serial_command_t("led",command_id));
          break;

        case SERIAL_COM_COMMAND__lcd:
          last_displayed_command = update_2nd_line_command(serial_command_t("lcd",command_id));
          break;

        case SERIAL_COM_COMMAND__info:
          last_displayed_command = update_2nd_line_command(serial_command_t(get_display_info_mode_text(),command_id));
          break;

        case SERIAL_COM_COMMAND__fca:
          last_displayed_command = update_2nd_line_command(serial_command_t("fca",command_id));
          break;

        case SERIAL_COM_COMMAND__unsafe_distance:
          last_displayed_command = update_2nd_line_command(serial_command_t("unsafe",command_id), tx);
          break;

        case SERIAL_COM_COMMAND__safe_distance:
          last_displayed_command = update_2nd_line_command(serial_command_t("safe",command_id), tx);
          break;
          
        default:
          last_displayed_command = update_2nd_line_command(serial_command_t("undef",command_id));
          break;
      }
    }
  }
  else
  {
    write_unconnected_display_message();
  }
}