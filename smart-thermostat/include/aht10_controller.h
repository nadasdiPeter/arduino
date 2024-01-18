/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of the AHT10 controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef AHT10_CONTROLLER_H
   #define AHT10_CONTROLLER_H
   
   #include <Arduino.h>
   #include "timer.h"
   #include "config.h"
   #include <AHTxx.h>

   /**
   * Initializes all  resources which are needed for the AHT10 temperature and humidity sensor.
   */
   extern void initialize_aht10_controller();

   /**
   * Main function of the AHT10 controller
   */  
   extern void aht10_controller_main();

   /**
   * Triggers a humidity reading and provides the humidity value in float type.
   */  
   extern float Get_AHT10_actual_humidity_float();

   /**
   * Triggers a humidity reading and provides the humidity value in string format.
   */  
   extern String Get_AHT10_actual_humidity_string();

   /**
   * Triggers a temperature reading and provides the temperature value in celsius, in float format.
   */  
   extern float Get_AHT10_actual_temperature_float();

   /**
   * Triggers a temperature reading and provides the temperature value in celsius, in string format.
   */ 
   extern String Get_AHT10_actual_temperature_string();

   /**
   * Provides the AHT10 sensor status.
   */
   extern aht10_status_t Get_AHT10_status();

   /**
   * Does not triggers a temperature reading just provides the most recent available temperature value in celsius, in float format.
   */ 
   extern float Get_AHT10_last_measured_temperature_float();
   
   /**
   * Does not triggers a temperature reading just provides the most recent available temperature value in celsius, in string format.
   */ 
   extern String Get_AHT10_last_measured_temperature_string();

#endif /* AHT10_CONTROLLER_H */