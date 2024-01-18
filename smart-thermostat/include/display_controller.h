/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Main functions of the OLED display controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef OLED_CONTROLLER_H
   #define OLED_CONTROLLER_H

   #include "config.h"
   #include <U8g2lib.h>
   #ifdef U8X8_HAVE_HW_SPI
   #include <SPI.h> 
   #endif
   #ifdef U8X8_HAVE_HW_I2C 
   #include <Wire.h> 
   #endif
   #include "timer.h"
   #include "aht10_controller.h"
   #include "wifi_controller.h"
   #include "heating_controller.h"
   
   /**
    * Initializes all  resources which are needed for the OLED display.
    */
   extern void initialize_display_controller();

   /**
    * Main function of the OLED controller
    */
   extern void display_controller_main();

   /**
    * Enables or disables the OLED display.
    * 
    * @param state OLED to be turned On or Off
    */
   extern void display_setPowerSaveMode(oled_status_t state);

   /**
    * Displays the main view on the OLED screen.
    */
   extern void display_main_window();

   /**
    * Callback function of the display_timer.
    */
   extern void display_callback();

#endif /* OLED_CONTROLLER_H */