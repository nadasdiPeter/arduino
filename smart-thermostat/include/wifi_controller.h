/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of the WIFI controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef WIFI_CONTROLLER_H
   #define WIFI_CONTROLLER_H

   #include <Arduino.h>
   #include <ESP8266WiFi.h>
   #include <WiFiClientSecure.h>
   #include <UniversalTelegramBot.h>
   #include <ArduinoJson.h>
   #include "credentials.h"
   #include "config.h"

   extern WiFiClientSecure client; /* Provides the wificlient available for the telegram-bot */

   /**
    * Initializes all the resources which are needed for the WIFI communication.
    */
   extern void initialize_wifi_controller();

   /**
    * Main function of the wifi controller
    */
   extern void wifi_controller_main();

   /**
    * Provides the IP address of the board after an established wifi connection.
    */
   extern String GetIP();

   /**
    *  Provides the MAC address of the board after an established wifi connection.
    */
   extern String GetMAC();

   /**
    *  Provides the wi-fi connection status.
    */
   extern bool Get_connection_status();

   /**
    *  Provides the wi-fi connection status in string format.
    */
   extern String Get_connection_status_string();

   /**
    *  Provides the hour
    */
   extern int Get_NTP_hour();
   
   /**
    *  Provides the minute
    */
   extern int Get_NTP_minute();


   /**
    *  Provides the time in hh:mm format
    */
   extern String Get_NTP_time();

   /**
    *  Provides the day name
    */
   extern String Get_NTP_day();

#endif /* WIFI_CONTROLLER_H */