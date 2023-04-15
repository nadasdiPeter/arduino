#include "config_definition_uno.h"
#include "serial_com_control.h"
#include <Arduino.h>

void initialize_serial_com()
{
  /* Open serial COM port */
  Serial.begin(SERIAL_BAUD_RATE);
}

bool get_serial_message(byte * message)
{
  // serial.available() checks the rx serial buffer  and return its length, if there is any unprocessed data in the buffer the returned value will be bigger than zero.
  if (Serial.available() > 0) 
  { 
    // serial.read() reaturn the first unprocessed byte of the serial rx buffer
    *message =  Serial.read();
    return true;
  }
  return false;
}

void serial_write(char message)
{
  Serial.print(message);
}
