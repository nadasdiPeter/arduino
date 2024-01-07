/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Main functions of the COMMAND HANDLER.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef COMMAND_HANDLER_H
   #define COMMAND_HANDLER_H

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
   #include "message_handler.h"

   /**
    * Interprets the received commands and initiate the needed actions.
    */
   extern bool command_interpreter(telegramMessage msg);

#endif /* COMMAND_HANDLER_H */