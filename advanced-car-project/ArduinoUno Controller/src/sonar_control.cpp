#include <NewPing.h>
#include "timer.h"
#include "sonar_control.h"
#include "config_definition_uno.h"
#include "serial_com_control.h"

NewPing sonar(HCSR04_TRIGGER, HCSR04_ECHO, MAX_DISTANCE); // setup of pins and maximum distance.
Timer distance_update_cycle;
unsigned int distance = 0;

unsigned int get_last_measured_distance()
{
   return distance;
}

void sonar_main()
{
   distance_update_cycle.update();
}

void cyclic_distance_update_handler() 
{
  // Send ping, get distance in cm and print result (0 = outside set distance range)*
  distance = sonar.ping_cm(); 
}

void initialize_sonar()
{
  distance_update_cycle.setInterval(SONAR_REFRESH_CYCLE);
  distance_update_cycle.setCallback(cyclic_distance_update_handler);
  distance_update_cycle.start(); 
}