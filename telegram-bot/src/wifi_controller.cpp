#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "timer.h"
#include "config.h"
#include "serial_controller.h"
#include "command_controller.h"
#include "wifi_controller.h"
#include "hardware_controller.h"


#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
Timer bot_callback_timer;


void handle_NewMessages(int number_of_NewMessages) 
{
  for (int i=0; i<number_of_NewMessages; i++) 
  {
    message_interpreter(bot.messages[i]);
  }
}


void bot_callback() 
{
  bot_callback_timer.stop();
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages)
  {
    handle_NewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
  bot_callback_timer.start();
}


bool send_message(String chat_id, String message, String mode) 
{
  /* mode refers for text formatting, can be HTML, Markdown, MarkdownV2. */
  return bot.sendMessage(chat_id, message, mode);
}


void set_commands(String commands) 
{
  /* mode refers for text formatting, can be HTML, Markdown, MarkdownV2. */
  bot.setMyCommands(commands);
}


void initialize_wifi_controller()
{
  #ifdef ESP8266
  configTime(0, 0, "pool.ntp.org");      // Get UTC time via NTP
  client.setTrustAnchors(&cert);         // Add root certificate for api.telegram.org
  #endif

  /* WiFi set to station mode
  * The ESP8266 is operating like a WiFi client and is able to connect to a WiFi access point */
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  
  #ifdef ESP32
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
  WifiLED_OFF();
  
  // Print ESP32 Local IP Address
  serial_write("Connected!\n");
  client.setInsecure(); // insecure..., but the most simple way to handle https-POST on ESP8266
  BuiltInLED_OFF();

  //bot_setup();
  while (send_message(CHAT_ID, ">> <b>Restart</b>\nHello, I'm online!", "HTML") != true){};

  bot_callback_timer.setInterval(1000);
  bot_callback_timer.setCallback(bot_callback);
  bot_callback_timer.start(); 
}


void wifi_controller_main()
{
  bot_callback_timer.update();
}