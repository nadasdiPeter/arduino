#include "config_definition_esp.h"
#include "serial_controller.h"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include "timer.h"
#include "wifi_controller.h"
#include "esp_main.h"

// Create timer instance for serial communication
Timer serial_com_timer;

// Callback function for serial_com_timer to handle the Serial communication events.
void serial_com_timer_Callback() 
{
  Serial.print(Get_connection_status());
}

void initialize_serial_controller()
{
  /* Open Serial port to communicate with the UNO */
  Serial.begin(SERIAL_BAUD_RATE);

  serial_com_timer.setInterval(100); // The timer will repeat every 100 ms
  serial_com_timer.setCallback(serial_com_timer_Callback);
  serial_com_timer.start(); 
}

void serial_controller_main()
{
  byte serial_command;
  if (GetD_serial_message(&serial_command)) interpreter(serial_command);
  serial_com_timer.update();
}

void serial_write(char c)
{
   Serial.print(c);
}

bool GetD_serial_message(byte * message)
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