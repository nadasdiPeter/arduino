#include "config.h"
#include "serial_controller.h"

void initialize_serial_controller()
{
  /* Open Serial port to communicate via BUS */
  Serial.begin(SERIAL_BAUD_RATE);
}

void serial_write(String message)
{
   Serial.println(message);
}