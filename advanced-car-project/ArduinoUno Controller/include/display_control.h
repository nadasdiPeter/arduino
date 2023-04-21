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
    */
   extern void display_main();

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
    */
   extern void update_1st_line_command();

   /**
    * Updates the LCD display according the current satus and request
    * 
    * @param command ID of the command from which the details needs to be printed.
    */
   extern void update_2nd_line_command(serial_command_t command);

   /**
    * Updates the LCD display according the current satus and request
    * 
    * @param command_id ID of the command from which the details needs to be printed. Default value: 0
    */
   extern void update_lcd_display_text(int command_id = 0);

   /**
    * Cyclic lcd update task which is called by the display timer (display_update_cycle) according to the DISPLAY_REFRESH_RATE.
    * DISPLAY_REFRESH_RATE: Refresh cycle of the LCD display in ms defined in the config file.
    */
   extern void cyclic_display_update_handler();

#endif /* DISPLAY_CONTROL_H */