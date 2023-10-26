/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of the serial controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef SERIAL_CONTROLLER_H
  #define SERIAL_CONTROLLER_H

  #include <Arduino.h>

   /**
    * Initialize all the resources used to control the serial BUS communication.
    */
   extern void initialize_serial_controller();

   /**
    * Interface for the other controllers to send messages via serial BUS port
    * 
    * @param message The message 
    */
   extern void serial_write(String message);

#endif /* SERIAL_CONTROLLER_H */