#include "config.h"
#include <UniversalTelegramBot.h>
#include "serial_controller.h"
#include "command_controller.h"
#include "hardware_controller.h"
#include "wifi_controller.h"


bool is_verified_user(String chat_id)
{
  return (chat_id == CHAT_ID);
}


void command__start(telegramMessage message)
{
  String welcome = "Hello " + message.from_name + ",\n";
  welcome += "Use the following commands to control your outputs.\n\n";
  welcome += "/generate to generate new password \n";
  send_message(message.chat_id, welcome);
}


void command__update_commands(telegramMessage message)
{
  const String commands = F("["
                            "{\"command\":\"update\", \"description\":\"Update command list\"},"
                            "{\"command\":\"temperature\", \"description\":\"Get temperature\"},"
                            "{\"command\":\"humidity\", \"description\":\"Get humidity\"},"
                            "{\"command\":\"runtime\", \"description\":\"Get runtime\"},"
                            "{\"command\":\"version\", \"description\":\"Get software version\"}"
                            "]");                     
  set_commands(commands);
  send_message(message.chat_id, "<b>>> Update</b>\nList updated.", "HTML");
}


void command__version(telegramMessage message)
{
  String reply = "<b>>> Version:</b>\n";
  reply += "TelegramBOT V1.0\n";
  send_message(message.chat_id, reply, "HTML");
}


void command__indoortemp(telegramMessage message)
{
  String reply = "<b>>> Temperature</b>\nAHT10 sensor: ";
  reply += Get_AHT10_temperature();
  reply += "(C)\n";
  reply += "DHT11 sensor: ";
  reply += Get_DHT11_temperature();
  reply += "(C)\n";
  send_message(message.chat_id, reply, "HTML");
}


void command__indoorhumidity(telegramMessage message)
{
  String reply = "<b>>> Humidity</b>\nAHT10 sensor: ";
  reply += Get_AHT10_humidity();
  reply += "(%)\n";
  reply += "DHT11 sensor: ";
  reply += Get_DHT11_humidity();
  reply += "(%)\n";
  send_message(message.chat_id, reply, "HTML");
}


void command__runtime(telegramMessage message)
{
  unsigned long ms = millis();
  unsigned long sec = ms/1000;
  unsigned long min = sec/60;
  unsigned long h = min/60;

  min = min - (h*6);
  sec = sec - ((h*3600)+(min*60));

  String reply = "<b>>> Runtime</b>\n";
  reply += h;
  reply += "<i>(h)</i>  ";
  reply += min;
  reply += "<i>(min)</i>  ";
  reply += sec;
  reply += "<i>(sec)</i>";
  send_message(message.chat_id, reply, "HTML");
}


void message_interpreter(telegramMessage message)
{
  String chat_id = message.chat_id;
  String text = message.text;
  text.toLowerCase();
  
  if (!is_verified_user(message.chat_id))
  {
    send_message(message.chat_id, "You are an unauthorized user.");
  }
  else
  {
    if (text == "/update") command__update_commands(message);
    else if (text == "/temperature") command__indoortemp(message);
    else if (text == "/humidity") command__indoorhumidity(message);
    else if (text == "/runtime") command__runtime(message);
    else if (text == "/version") command__version(message);
    else send_message(chat_id, "<b>>> Error</b>\nUnknown command.","HTML");
  }
}