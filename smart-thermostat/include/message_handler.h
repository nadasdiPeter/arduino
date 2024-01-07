/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Main functions of the MESSAGE HANDLER.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef MESSAGE_HANDLER_H
   #define MESSAGE_HANDLER_H

   #include <ESP8266WiFi.h>
   #include <WiFiClientSecure.h>
   #include <UniversalTelegramBot.h>
   #include <ArduinoJson.h>
   #include "credentials.h"
   #include "wifi_controller.h"
   #include "display_controller.h"
   #include "aht10_controller.h"
   #include "telegram_bot.h"
   #include "config.h"

   /**
    * Responsible for formatting the messages for telegram chat and the text on the OLED display.
    */
   extern bool message(message_t);

#endif /* MESSAGE_HANDLER_H */