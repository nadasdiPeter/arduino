/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Controller class of the LCD display.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef DISPLAY_CONTROL_H
   #define DISPLAY_CONTROL_H

   /**
    *  Cyclic main function of the display controller
    * 
    * @param connection contains the info whether the esp has any client connected or not
    */
   extern void display_main(connection_status_t connection);

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
    *  Taking care of the initialization of the LCD display.
    */
   extern void initialize_lcd_display();

   /**
    *  Toggles the LCD display background light
    */
   extern void toggle_lcd_backlight();

   /**
    *  In case the client disconnects the function will be called and lcd will be updated to show
    *  the wifi name and password.
    */
   extern void write_unconnected_display_message();

   /**
    *  Updates the first line of the LCD display if the connection status: connected
    * 
    * @param connection contains the info whether the esp has any client connected or not
    */
   extern void update_1st_line_command(connection_status_t connection);

   /**
    * Updates the LCD display according the current satus and request
    * 
    * @param command ID of the command from which the details needs to be printed.
    * @param msg_dir contains the info which node sending the message (esp: rx, uno: tx) Default value: RX
    * @return the id of the command
    */
   extern serial_command_t update_2nd_line_command(serial_command_t command, msg_direction_t msg_dir = rx);

   /**
    * Updates the LCD display according the current satus and request
    * 
    * @param connection contains the info whether the esp has any client connected or not
    * @param command_id ID of the command from which the details needs to be printed. Default value: 0
    */
   extern void update_lcd_display_text(connection_status_t connection, int command_id = 0);

   /**
    * Returns a the name of the mode which is activated by the user.
    * The mode name used on the display  instead of the INFO command to specify the command in a more detiled way.
    * 
    * @return The name of the activ mode ip-port / clock / distance ...
    */
   extern String get_display_info_mode_text();

   /**
    * Cyclic lcd update task which is called by the display timer (display_update_cycle) according to the DISPLAY_REFRESH_RATE.
    * DISPLAY_REFRESH_RATE: Refresh cycle of the LCD display in ms defined in the config file.
    */
   extern void cyclic_display_update_handler();

#endif /* DISPLAY_CONTROL_H */