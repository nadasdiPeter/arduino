#include "serial_controller.h"
#include "wifi_controller.h"
#include "hardware_controller.h"
#include "config.h"

/* Initialize all needed resource. */
void setup() 
{
  initialize_hardware_controller();
  initialize_serial_controller();
  initialize_wifi_controller();
}

/* main loop */
void loop() 
{
  wifi_controller_main();
}