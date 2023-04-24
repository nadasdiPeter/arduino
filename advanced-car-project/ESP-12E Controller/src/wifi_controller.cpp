#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config_definition_esp.h"
#include "timer.h"
#include "wifi_controller.h"
#include "esp_main.h"


/* Setting up Wi-Fi Access point */
IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);
ESP8266WebServer server(PORT);


void handleMoveRequest() 
{
  if (!server.hasArg("dir")) 
  {
    server.send(404, "text / plain", "Move: undefined");
    return;
  }
  String direction = server.arg("dir");
  if (direction.equals("F")) 
  {
    interpreter(FORWARD);
    server.send(200, "text / plain", "Move: forward");
  }
  else if (direction.equals("B")) 
  {
    interpreter(BACKWARD);
    server.send(200, "text / plain", "Move: backward");
  }
  else if (direction.equals("S")) 
  {
    interpreter(STOP);
    server.send(200, "text / plain", "Move: stop");
  }
  else if (direction.equals("L")) 
  {
    interpreter(LEFT);
    server.send(200, "text / plain", "Turn: left");
  }
  else if (direction.equals("R")) 
  {
    interpreter(RIGHT);
    server.send(200, "text / plain", "Turn: right");
  }
  else 
  {
    interpreter(STOP);  // For unrecognized MOVE command STOP the vehicle
    server.send(404, "text / plain", "Move: undefined");
  }
}

void handleActionRequest() 
{
  if (!server.hasArg("type")) 
  {
    server.send(404, "text / plain", "Action: undefined");
    return;
  }
  String type = server.arg("type");
  if (type.equals("1")) 
  {
    interpreter(LED);
    server.send(200, "text / plain", "Action: led-mode");
  }
  else if (type.equals("2")) 
  {
    interpreter(LCD);
    server.send(200, "text / plain", "Action: lcd-mode");
  }
  else if (type.equals("3")) 
  {
    interpreter(INFO);
    server.send(200, "text / plain", "Action: info-mode");
  }
  else if (type.equals("4")) 
  {
    interpreter(TURNING_MODE);
    server.send(200, "text / plain", "Action: turning-mode");
  }
  else if (type.equals("5")) 
  {
    interpreter(FCA);
    server.send(200, "text / plain", "Action: fca-mode");
  }
  else 
  {
    interpreter(STOP);
    server.send(404, "text / plain", "Action: undefined");
  }
}

void handleNotFound() 
{
  server.send(404, "text / plain", "404: Not found");
}

void initialize_wifi_controller()
{
  /* Start Wifi-Acess-Point
   * SSID:     ArduinoCar
   * Password: letmejoin
   * IP        192.168.4.1
   * Port      8080        */

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(SSID, PASSWORD);

  /* Define HTTP GET request handler functions and start the server */
  server.on("/move",   HTTP_GET, handleMoveRequest);
  server.on("/action", HTTP_GET, handleActionRequest);
  server.onNotFound(handleNotFound);
  server.begin();
}

void wifi_controller_main()
{
   // handleClient() listen for HTTP requests from clients
   // If handleClient detects a new requests, it will automatically execute the right functions that we specified in the setup.
   server.handleClient();
}

char get_connection_status()
{
  // WiFi.softAPgetStationNum() returns the number of the connected devices.
  return ((WiFi.softAPgetStationNum()) ? SERIAL_COM_COMMAND__connected : SERIAL_COM_COMMAND__disconnected);
}