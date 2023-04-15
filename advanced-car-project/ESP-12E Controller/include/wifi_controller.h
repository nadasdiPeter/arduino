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

   /**
    * This function handles the HTTP GET "move" requests.
    * Example: /move?dir=F
    */
   extern void handleMoveRequest();

   /**
    * This function handles the HTTP GET "action" requests.
    * Example: /action?type=1
    */
   extern void handleActionRequest();

   /**
    * This function handles the unknown HTTP GET requests.
    */
   extern void handleNotFound();

   /**
    * Initializes all the resources which are needed for the WIFI communication.
    * Define HTTP GET request handler functions and start the server
    */
   extern void initialize_wifi_controller();

   /**
    * main function of the wifi controller
    * listen for HTTP requests from clients
    * If it detects a new requests, it will automatically execute the right functions that we specified in the setup.
    */  
   extern void wifi_controller_main();

   /**
    * Checks for cennected devices.
    * 
    * @returns Returns SERIAL_COM_COMMAND__connected status if at least 1 connected device found, otherwise FALSE.
    */
   extern char get_connection_status();

#endif /* WIFI_CONTROLLER_H */