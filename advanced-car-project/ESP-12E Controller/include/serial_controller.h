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
    * Checks the serial RX buffer if there is any unprocessed message in the que and if it is, than returns the first 1 byte of it.
    * 
    * @param message 1 byte long message (An ASCII charather read from serial RX buffer)
    * @returns Returns TRUE if there was any unprocessed message found in the RX que othirwise FALSE.
    */
   extern bool get_serial_message(byte * message);

   /**
    * Cyclic callback function of the serial controller for triggering the sending of the shared data between esp and uno.
    */
   extern void serial_com_timer_callback();

   /**
    * Cyclic main function of the serial controller
    */
   extern void serial_controller_main();

   /**
    * Interface for the other controllers to request the sending of a command to the UNO.
    * 
    * @param c The message which used to be a command ID (It most to have always 1 byte long ehich means only ASCII charaters are allowed.)
    */
   extern void serial_write(char c);

#endif /* SERIAL_CONTROLLER_H */