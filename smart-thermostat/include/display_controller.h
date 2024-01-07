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
   
   /**
    * Initializes all  resources which are needed for the OLED display.
    */
   extern void initialize_display_controller();

   /**
    * Main function of the OLED controller
    */
   extern void display_controller_main();

   /**
    * Prints 5 lines to the OLED display.
    * 
    * @param line_0 First line
    * @param line_1 Second line
    * @param line_2 Third line
    * @param line_3 Forth line
    * @param line_4 Fift line
    */
   extern void display_print_5_line(const char* line_0 = "", const char* line_1 = "", const char* line_2 = "", const char* line_3 = "", const char* line_4 = "");

   /**
    * Print two lines to the OLED display.
    * 
    * @param line_0 First line
    * @param line_1 Second line
    */
   extern void display_print_2_line(const char* line_0, const char* line_1);

   /**
    * Enables or disables the OLED display.
    * 
    * @param state OLED to be turned On or Off
    */
   extern void display_setPowerSaveMode(oled_status_t state);


   extern void display_print_temperature(const char* temperature);
   extern void display_print_humidity(const char* humidity);

#endif /* OLED_CONTROLLER_H */