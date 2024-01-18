/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of the WIFI controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef HEATING_CONTROLLER_H
   #define HEATING_CONTROLLER_H

   #include <Arduino.h>
   #include "config.h"

   /**
    * Initializes all the resources which are needed for the WIFI communication.
    */
   extern void initialize_heating_controller();

   /**
    * Main function of the heating controller
    */
   extern void heating_controller_main();

   extern float Get_HeatingTarget_float();

   extern String Get_HeatingTarget_string();

   extern float Get_HeatingNegativeLimit_float();

   extern String Get_HeatingNegativeLimit_string();

   extern float Get_HeatingPositiveLimit_float();

   extern String Get_HeatingPositiveLimit_string();

   extern bool Heating_is_in_progress();

   extern void Set_target_temperature(float target);
   
   extern void Set_negative_difference(float negative_diff);

   extern void Set_positive_difference(float positive_diff);

   extern sheduling_time_t day_night_calculation();

#endif /* HEATING_CONTROLLER_H */