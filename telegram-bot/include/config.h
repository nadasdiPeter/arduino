/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Configuration file. 
 *                 Contains the PIN layout and all the parameters which can be modified.
 *                 It also contains structs, enums and class definitions used by the program.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef CONFIG_H
  #define CONFIG_H

  #include "credentials.h"

  // Network credentials
  #define INBUILT_LED_PIN D4
  #define WIFI_LED        D7

  // Serial monitor configuration
  #define SERIAL_BAUD_RATE 115200

#endif /* CONFIG_H */