#include <Arduino.h>
#include "config_definition_uno.h"


connection_status_t  connection_status      = status_unconnected;
direction_t          vehicle_status         = d_stop;
display_info_mode_t  display_info_mode      = ip_mode;
serial_command_t     last_command_details   = serial_command_t("undef", 0, rx);


void set_connection_status(connection_status_t status)
{
   connection_status = status;
}

connection_status_t get_connection_status()
{
   return connection_status;
}

void set_vehicle_status(byte status)
{
   switch (status)
   {
   case SERIAL_COM_COMMAND__stop:
      vehicle_status = d_stop;
      break;
   case SERIAL_COM_COMMAND__forward:
      vehicle_status = d_forward;
      break;
   case SERIAL_COM_COMMAND__backward:
      vehicle_status = d_backward;
      break;
   case SERIAL_COM_COMMAND__right:
      vehicle_status = d_right;
      break;
   case SERIAL_COM_COMMAND__left:
      vehicle_status = d_left;
      break;
   default:
      vehicle_status = d_stop;
      break;
   }
}

void set_vehicle_status(direction_t status)
{
   vehicle_status = status;
}

direction_t get_vehicle_status()
{
   return vehicle_status;
}

void set_display_info_mode(display_info_mode_t mode)
{
  display_info_mode = mode;
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

display_info_mode_t get_display_info_mode()
{
  return display_info_mode;
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

void set_last_command_details(serial_command_t cmd)
{
  last_command_details = cmd;
}

serial_command_t get_last_command_details()
{
  return last_command_details;
}
