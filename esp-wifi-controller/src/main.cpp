/*********
  
  Author:  Peter Horvath
  Date:    2021.07.28
  Version: 1.0
  Complete project details on TBD.

*********/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Enables or disables DEBUG options like serial communication with the PC - 0 -> OFF / 1 -> ON */
#define DEVELOPER_MODE                  0

/* Network credentials */
#define ssid                            "ArduinoCAR"
#define password                        "letmejoin"
#define port                            8080

/* Commands used on SERIAL communication between UNO and NodeMCU */
#define STOP_CMD                        0x53 /* Asci code: S */
#define FORWARD_CMD                     0x46 /* Asci code: F */
#define BACKWARD_CMD                    0x42 /* Asci code: B */
#define RIGHT_CMD                       0x52 /* Asci code: R */
#define LEFT_CMD                        0x4c /* Asci code: L */
#define LED_CMD                         0x45 /* Asci code: E */
#define CTRL_MODE_CMD                   0x43 /* Asci code: C */

/* Keywords used in sourcecode for better understanding */
#define FORWARD                         0
#define LEFT                            1
#define RIGHT                           2
#define BACKWARD                        3
#define STOP                            4
#define LED                             5
#define CTRL_MODE                       6

/* Setting up Wi-Fi Access point */
IPAddress ip(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);
ESP8266WebServer server(port);

/* serialCom_Interpreter(int) function receive a command as a parameter and based on that it will trigger the Serial communication.  */
void serialCom_Interpreter(int command)
{
  switch (command)
  {
  case FORWARD:
    Serial1.write(FORWARD_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("Forward");
    #endif
    break;
  case LEFT:
    Serial1.write(LEFT_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("Left");
    #endif
    break;
  case RIGHT:
    Serial1.write(RIGHT_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("Right");
    #endif
    break;
  case BACKWARD:
    Serial1.write(BACKWARD_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("Backward");
    #endif
    break;
  case STOP:
    Serial1.write(STOP_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("Stop");
    #endif
    break;
  case LED:
    Serial1.write(LED_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("Led");
    #endif
    break;
  case CTRL_MODE:
    Serial1.write(CTRL_MODE_CMD);
    #if(DEVELOPER_MODE)
    Serial.println("ControlMode");
    #endif
    break;
  default:
    /*not possible*/
    break;
  }
}

/* This function handles the HTTP GET "move" requests. */
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
    serialCom_Interpreter(FORWARD);
    server.send(200, "text / plain", "Move: forward");
  }
  else if (direction.equals("B")) 
  {
    serialCom_Interpreter(BACKWARD);
    server.send(200, "text / plain", "Move: backward");
  }
  else if (direction.equals("S")) 
  {
    serialCom_Interpreter(STOP);
    server.send(200, "text / plain", "Move: stop");
  }
  else if (direction.equals("L")) 
  {
    serialCom_Interpreter(LEFT);
    server.send(200, "text / plain", "Turn: left");
  }
  else if (direction.equals("R")) 
  {
    serialCom_Interpreter(RIGHT);
    server.send(200, "text / plain", "Turn: right");
  }
  else 
  {
    serialCom_Interpreter(STOP);
    server.send(404, "text / plain", "Move: undefined");
  }
}

/* This function handles the HTTP GET "action" requests. */
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
    serialCom_Interpreter(LED);
    server.send(200, "text / plain", "Action: led");
  }
  else if (type.equals("2")) 
  {
    serialCom_Interpreter(CTRL_MODE);
    server.send(200, "text / plain", "Action: control_change");
  }
  else 
  {
    serialCom_Interpreter(STOP);
    server.send(404, "text / plain", "Action: undefined");
  }
}

/* This function handles the unknown HTTP GET requests. */
void handleNotFound() 
{
  server.send(404, "text / plain", "404: Not found");
}


void setup() 
{
  /* Open Serial port(s) 
   * Serial is used to communicate with the PC during development
   * Serial1 is used to communicate with the UNO */

  #if(DEVELOPER_MODE)
  Serial.begin(115200); /* Communication with PC */
  #endif
  Serial1.begin(115200);

  /* Start Wifi-Acess-Point
   * SSID:     ArduinoCar
   * Password: letmejoin
   * IP        192.168.4.1
   * Port      8080 */

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, netmask);
  WiFi.softAP(ssid, password);

  /* Define HTTP GET request handler functions and start the server */
  server.on("/move", HTTP_GET, handleMoveRequest);
  server.on("/action", HTTP_GET, handleActionRequest);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() 
{
  server.handleClient();
}