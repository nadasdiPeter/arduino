/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Class for vehicle related informations which are not matching for the other models.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef STATE_REGISTER_H
   #define STATE_REGISTER_H

   /**
    * SETs the connection_status according the received parameter 
    * 
    * @param status connected or unconnected
    */
   extern void set_connection_status(connection_status_t status);

   /**
    * GETs the connection_status - if any USER connected to teh ESP wifi network.
    * 
    * @returns connection_status_t / connected or unconnected
    */
   extern connection_status_t get_connection_status();

   /**
    * SETs the vehicle motion status according to the received parameter.
    * Status can be forward, backward, left, right and stop.
    * 
    * @param status vehicle motion status info
    */
   extern void set_vehicle_status(direction_t status);

   /**
    * SETs the vehicle motion status according to the received parameter.
    * Status can expecting the same values which are used for SERIAL communication. 
    * 
    * @param status vehicle motion status info SERIAL_COM_COMMAND__*
    */
   extern void set_vehicle_status(byte status);

   /**
    * GETs the vehicle motion status.
    * Status can be forward, backward, left, right and stop. 
    * 
    * @returns status direction_t info 
    */
   extern direction_t get_vehicle_status();

#endif /* STATE_REGISTER_H */