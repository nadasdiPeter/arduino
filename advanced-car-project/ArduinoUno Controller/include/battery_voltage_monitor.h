/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Checking the voltage of the battery
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef BATTERY_VOLTAGE_MONITOR_H
   #define BATTERY_VOLTAGE_MONITOR_H

   /**
    * Provides the latest and greatast voltage information in Volt format measured from the voltage divider circuit. 
    * 
    * @returns Returns the latest and greatest measured volatge information in Volt.
    */
   extern float get_last_measured_voltage();

   /**
    * Provides the latest and greatast voltage information in RAW format (0..1024) measured from the voltage divider circuit. 
    * 
    * @returns Returns the latest and greatest measured volatge information in RAW format.
    */
   extern int get_last_measured_voltage_raw();

   /**
    * Cyclic main function of the battery-voltage-controller.
    */
   extern void battery_voltage_main();

   /**
    * Cyclic function to calculate the battery voltage based on the voltage divider circuit.
    */
   extern void cyclic_voltage_update_handler();

   /**
    * Initialize the resources which are use to measure the battery voltage.
    */
   extern void initialize_battery_voltage();

#endif /* BATTERY_VOLTAGE_MONITOR_H */