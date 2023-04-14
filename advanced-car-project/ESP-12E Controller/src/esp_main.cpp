/*********
  
  Author:  Peter Horvath
  Date:    2023.04.10
  Version: 1.0
  Complete project details on TBD.

*********/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config_definition_esp.h"
#include "motor_controller.h"
#include "serial_controller.h"
#include "wifi_controller.h"
#include "buzzer_controller.h"
#include "esp_main.h"

void interpreter(int command)
{ 
  switch (command)
  {
  case FORWARD: 
    move(FORWARD);
    serial_write(SERIAL_COM_COMMAND__forward);
    break;
  case LEFT:
    move(LEFT);
    serial_write(SERIAL_COM_COMMAND__left);
    break;
  case RIGHT:
    move(RIGHT);
    serial_write(SERIAL_COM_COMMAND__right);
    break;
  case BACKWARD:
    move(BACKWARD);
    serial_write(SERIAL_COM_COMMAND__backward);
    break;
  case STOP:
    move(STOP); 
    serial_write(SERIAL_COM_COMMAND__stop);
    break;
  case LED:
    serial_write(SERIAL_COM_COMMAND__led);
    request_beep(BEEP_500kHz);    
    break;
  case LCD:
    serial_write(SERIAL_COM_COMMAND__lcd);
    request_beep(BEEP_500kHz);
    break;
  case INFO:
    serial_write(SERIAL_COM_COMMAND__info);
    request_beep(BEEP_500kHz);
    break;
  case FCA:
    serial_write(SERIAL_COM_COMMAND__fca);
    request_beep(BEEP_1000kHz);
    break;
  case SERIAL_COM_COMMAND__unsafe_distance:
    move_foward_unsafe();
    break;
  case SERIAL_COM_COMMAND__safe_distance:
    move_foward_safe();
    break;
  default:
    /*not possible*/
    break;
  }
}

void setup() 
{
  initilazize_motor_controller();
  initialize_serial_controller();
  initialize_wifi_controller();
  initialize_buzzer();
}

void loop() 
{
  wifi_controller_main();
  serial_controller_main();
  buzzer_main();
}