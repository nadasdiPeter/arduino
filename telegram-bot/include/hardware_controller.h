/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of hardware controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef HARDWARE_CONTROLLER_H
   #define HARDWARE_CONTROLLER_H

   /**
    * Initializes all the resources which are needed for the hardware controller.
    */
   extern void initialize_hardware_controller();

   /**
    * ...
    */  
   extern void hardware_controller_main();

   extern void BuiltInLED_ON();
   extern void BuiltInLED_OFF();

   extern void WifiLED_ON();
   extern void WifiLED_OFF();

   extern int Get_DHT11_humidity();
   extern int Get_DHT11_temperature();

   extern float Get_AHT10_humidity();
   extern float Get_AHT10_temperature();

#endif /* HARDWARE_CONTROLLER_H */