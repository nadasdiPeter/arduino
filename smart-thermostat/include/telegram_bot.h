/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of the TELEGRAM controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef TELEGRAM_BOT_H
   #define TELEGRAM_BOT_H

   #include <Arduino.h>
   #include <ESP8266WiFi.h>
   #include <WiFiClientSecure.h>
   #include <UniversalTelegramBot.h>
   #include <ArduinoJson.h>
   #include "timer.h"
   #include "credentials.h"
   #include "config.h"
   #include "wifi_controller.h"
   #include "command_handler.h"

   /**
    * Initializes all the resources which are needed for the TELEGRAM communication.
    */
   extern void initialize_telegram_bot();

   /**
    * main function of the TELEGRAM BOT controller
    * listen for telegram messages from the client(s)
    * If it detects a new message, it triggers the message processing done by the command handler.
    */  
   extern void telegram_bot_main();

   /**
    * Sends the specified telegram message
    * 
    * @returns Returns true if the sending was successfull, otherwise false.
    */
   extern bool send_message(String chat_id, String message, String mode);

   /**
    * Sends the specified telegram message
    * 
    * @returns Returns true if the sending was successfull, otherwise false.
    */
   extern bool send_message(String message);

   /**
    * Sends the specified telegram message
    * 
    * @returns Returns true if the sending was successfull, otherwise false.
    */
   extern bool send_message(String title, String message); 

   /**
    * Sends the specified telegram message, keeps trying until successfull sending.
    * 
    * @returns Returns true if the sending was successfull, otherwise false.
    */
   extern bool send_message_forced(String chat_id, String message, String mode);

   /**
    * Sends the specified telegram message, keeps trying until successfull sending.
    * 
    * @returns Returns true if the sending was successfull, otherwise false.
    */
   extern bool send_message_forced(String message); 

   /**
    * Sends the specified telegram message, keeps trying until successfull sending.
    * 
    * @returns Returns true if the sending was successfull, otherwise false.
    */
   extern bool send_message_forced(String title, String message);

   /**
    * Checks if the received message was sent by authorized user.
    * 
    * @returns Returns true if the user authorized, otherwise false.
    */
   extern bool is_verified_user(String chat_id);

   /**
    * Use this method to change the list of the bot's commands.
    */
   extern void set_commands(String commands);

#endif /* TELEGRAM_BOT_H */