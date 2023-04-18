#include "timer.h"
#include "config_definition_uno.h"
#include "battery_voltage_monitor.h"

Timer battery_voltage_update_timer;
Timer unervoltage_monitor_timer;

boolean undervoltage_state = false;
boolean overvoltage_state  = false;

float source_volatge = 0.0;    /* Unit: Volt, Range: 0.0 .. 10.0 (V) */
int raw_value = 0;             /* Unit: raw,  Range: 0 .. 1024       */

voltage_sate_t get_voltage_state()
{
   if(undervoltage_state) return undervoltage;
   if(overvoltage_state) return overvoltage;
   return normal_voltage;
}

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

   raw_value = analogRead(BATTERY_VOLTAGE);
   source_volatge = raw_value * (VOLTAGE_DIVIDER__Vout / ANALOG_READ_MAX_VALUE)*((VOLTAGE_DIVIDER__R1 + VOLTAGE_DIVIDER__R2)/VOLTAGE_DIVIDER__R2);
   source_volatge = source_volatge * VOLTAGE_DIVIDER_FACTOR;

   /* Voltage monitoring
    * 
    * Undervoltage : is defined as a condition where the applied voltage drops to 90% of rated voltage, or less, for at least 1 minute.
    * Overvoltage  : is defined as a condition where the applied voltage excess of the normal operating voltage of the device or the circuit.
    * Normal       : is defined as a condition where the applied voltage is in the expected range.
    */

   if( source_volatge <= UNDERVOLTAGE )
   {
      if(!unervoltage_monitor_timer.isRunning()) unervoltage_monitor_timer.start(); // start the timer if it was already not running.
   }
   else  // else case means no undervoltage situation, flag can be cleared timer can be stopped.
   {
      unervoltage_monitor_timer.stop();
      undervoltage_state = false;
      overvoltage_state = (source_volatge >= OVERVOLTAGE) ? true : false; // checking for overvoltage situation. -> overvoltage immediatly triggers the warning lamp.
   }
}

void undervoltage_handler()
{
   /* Undervoltage is defined as a condition where the applied voltage drops to ~90% of rated voltage, or less, for at least 3 seconds. */
   if( source_volatge <= UNDERVOLTAGE ) undervoltage_state = true;
}

void battery_voltage_main()
{
   battery_voltage_update_timer.update();
   if(unervoltage_monitor_timer.isRunning()) unervoltage_monitor_timer.update();
}

void initialize_battery_voltage()
{
   /* initialize the analog PIN which will be used for the voltage measurements. */
   pinMode(BATTERY_VOLTAGE,INPUT);

   /* initialize a timer for the cyclic voltage measures. */
   battery_voltage_update_timer.setInterval(BATTERY_VOLTAGE_READ_CYCLE);
   battery_voltage_update_timer.setCallback(cyclic_voltage_update_handler);
   battery_voltage_update_timer.start(); 

   /* initialize a timer for undervoltage monitoring  */
   unervoltage_monitor_timer.setInterval(UNDERVOLTAGE_MONITORING_TIME);
   unervoltage_monitor_timer.setCallback(undervoltage_handler);
}