/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions which are responsible for the low level sheduling of the MCU / car.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef ESP_MAIN_H
  #define ESP_MAIN_H

   /**
    * A wrapper function which maps the commands to the corresponding function-controller and initiates its execution.
    * 
    * @param command the id of the command received on the WIFI or on the SERIAL BUS channel.
    */
   extern void interpreter(int command);

   /**
    * The main function fo starting the initialization of the MCU.
    */
   extern void setup();

   /**
    * The main task for sheduling the normal operation.
    */
   extern void loop();

#endif /* ESP_MAIN_H */