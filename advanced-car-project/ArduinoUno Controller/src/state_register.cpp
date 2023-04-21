#include <Arduino.h>
#include "config_definition_uno.h"

connection_status_t  connection_status    = status_unconnected;
direction_t          vehicle_status       = d_stop;


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
