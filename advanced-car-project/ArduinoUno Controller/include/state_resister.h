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

   /**
    * Returns a the mode which is activated by the user.
    * 
    * @return Returns the activ mode ip-port / clock / distance ...
    */
   extern display_info_mode_t get_display_info_mode();

   /**
    * Returns a the name of the mode which is activated by the user.
    * The mode name used on the display  instead of the INFO command to specify the command in a more detiled way.
    * 
    * @return The name of the activ mode ip-port / clock / distance ...
    */
   extern String get_display_info_mode_text();

   /**
    *  Updates the displayed text on the LCD, according the received connection status
    * 
    * @param mode contains the requested info mode: ip-port / clock / distance ...
    */
   extern void set_display_info_mode(display_info_mode_t mode);

   /**
    *  Request to show the next option in the info mode menu: ip-port / clock / distance ...
    */
   extern void next_display_info_mode();

   /**
    *  Saves the last displayed command for later use.
    */
   extern void set_last_command_details(serial_command_t cmd);

   /**
    *  Provides the last displayed command for cyclic updates.
    * 
    * @return serial_command_t with the details of the command.
    */
   extern serial_command_t get_last_command_details();

#endif /* STATE_REGISTER_H */