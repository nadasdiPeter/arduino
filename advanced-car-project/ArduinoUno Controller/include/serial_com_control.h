/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Controller class of the Serial BUS communication.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef SERIAL_CONTROL_H
   #define SERIAL_CONTROL_H

   #include <Arduino.h>

   /**
    * Initialize the Serial port and connection
    */
   extern void initialize_serial_com();

   /**
    * Checks the rx serial buffer and if there is any unprocessed data the first byte will copied into the message parameter.
    * 
    * @param message the first unprocessed byte of the serial rx buffer
    * @returns TRUE if there is unprocessed data in the que or otherwise FALSE.
    */
   extern bool get_serial_message(byte * message);
   
   /**
    * Write the message into the tx serial buffer which will be forwarded on the serial com channel.
    * 
    * @param message 1 byte long message (an ASCII charachter) which will be forwarded on te serial BUS.
    */
   extern void serial_write(char message);

#endif /* SERIAL_CONTROL_H */