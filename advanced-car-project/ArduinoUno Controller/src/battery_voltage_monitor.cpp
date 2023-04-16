#include "timer.h"
#include "config_definition_uno.h"
#include "battery_voltage_monitor.h"

Timer battery_voltage_update_timer;
float source_volatge = 0.0;    /* Unit: Volt, Range: 0.0 .. 10.0 (V) */
int raw_value = 0;             /* Unit: raw,  Range: 0 .. 1024       */

float get_last_measured_voltage()
{
   return source_volatge;
}

int get_last_measured_voltage_raw()
{
   return raw_value;
}

void cyclic_voltage_update_handler()
{
   raw_value = analogRead(BATTERY_VOLTAGE);

   /* Basic of voltage divider circuits:
    * 
    * A voltage divider circuit is a very common circuit that takes a higher voltage and converts it to a lower one
    * by using a pair of resistors. The formula for calculating the output voltage is based on Ohms Law and is shown below.
    * 
    * V(out) = ( V(s) x R2 ) / ( R1 + R2 )
    * 
    * where:
    *    - V(s) is the source voltage, measured in volts (V),
    *    - R1 is the resistance of the 1st resistor, measured in Ohms (Ω).
    *    - R2 is the resistance of the 2nd resistor, measured in Ohms (Ω).
    *    - V(out) is the output voltage, measured in volts (V),
    * 
    *    - VOLTAGE_DIVIDER__Vout   = 5        (V)
    *    - VOLTAGE_DIVIDER__R1     = 46100.0  (Ω)
    *    - VOLTAGE_DIVIDER__R2     = 46300.0  (Ω)
    */

   source_volatge = raw_value * (VOLTAGE_DIVIDER__Vout / 680)*((VOLTAGE_DIVIDER__R1 + VOLTAGE_DIVIDER__R2)/VOLTAGE_DIVIDER__R2);
}

void battery_voltage_main()
{
   battery_voltage_update_timer.update();
}

void initialize_battery_voltage()
{
  pinMode(BATTERY_VOLTAGE,INPUT);
  battery_voltage_update_timer.setInterval(BATTERY_VOLTAGE_READ_CYCLE);
  battery_voltage_update_timer.setCallback(cyclic_voltage_update_handler);
  battery_voltage_update_timer.start(); 
}