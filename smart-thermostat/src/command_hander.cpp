#include "command_handler.h"

extern void display_state_change(oled_status_t status);
extern void Get_sensor_value(sensor_t sensor);
extern void Get_runtime();
extern void command__update_commands();
extern void Set_target(String s);
extern void Set_maximum_difference(String s);
extern void Set_minimum_difference(String s);

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

bool command_interpreter(telegramMessage msg) 
{
   String chat_id = msg.chat_id;
   String text = msg.text;
   text.toLowerCase();

   if (!is_verified_user(msg.chat_id))
   {
      send_message(msg.chat_id, "You are an unauthorized user.", "HTML");
   }
   else
   {
      String command = getValue(text, ' ',0);
      if (command == "/display_on") display_state_change(oled_on);
      else if (command == "/display_off") display_state_change(oled_off);
      else if (command == "/update") command__update_commands();
      else if (command == "/temperature") Get_sensor_value(sensor_temperature);
      else if (command == "/humidity") Get_sensor_value(sensor_humidity);
      else if (command == "/set_target") Set_target(getValue(text, ' ',1));
      else if (command == "/set_minimum") Set_minimum_difference(getValue(text, ' ',1));
      else if (command == "/set_maximum") Set_maximum_difference(getValue(text, ' ',1));
      else if (command == "/connection_status") send_message_forced(Get_connection_status_string());
      else if (command == "/runtime") Get_runtime();
      else if (command == "/version") send_message_forced("Software version", VERSION);
      else if (command == "/ip") send_message_forced("IP address", GetIP());
      else if (command == "/mac") send_message_forced("MAC address", GetMAC());

      else if (command == "/hour") send_message_forced("Hour", (String)" " + Get_NTP_hour() + "(h)");
      else if (command == "/minute") send_message_forced("Minute", (String)" " + Get_NTP_minute() + "(min)");

      else send_message_forced("Error", "Unknown command");
   }
   return true;
}

void Set_target(String s)
{
   Set_target_temperature(s.toFloat());
   send_message_forced( "Heating controller", "Target temperature: " + s + " °C" );
}

void Set_maximum_difference(String s)
{
   Set_positive_difference(s.toFloat());
   send_message_forced( "Heating controller", "Positive difference: " + s + " °C" );
}

void Set_minimum_difference(String s)
{
   Set_negative_difference(s.toFloat());
   send_message_forced( "Heating controller", "Negative difference: " + s + " °C" );
}

void command__update_commands()
{
  const String commands = F("["
                            "{\"command\":\"update\", \"description\":\"Update commands\"},"
                            "{\"command\":\"temperature\", \"description\":\"Get temperature\"},"
                            "{\"command\":\"humidity\", \"description\":\"Get humidity\"},"
                            "{\"command\":\"runtime\", \"description\":\"Get runtime\"},"
                            "{\"command\":\"version\", \"description\":\"Get software version\"},"
                            "{\"command\":\"connection_status\", \"description\":\"Connection status\"},"
                            "{\"command\":\"ip\", \"description\":\"Get ip address\"},"
                            "{\"command\":\"mac\", \"description\":\"Get mac address\"},"
                            "{\"command\":\"display_on\", \"description\":\"Display on\"},"
                            "{\"command\":\"display_off\", \"description\":\"Display off\"}"
                            "]");                     
  set_commands(commands);
}

void display_state_change(oled_status_t status)
{
   String msg = ">> <b>Display</b>\nDisplay turned ";
   msg += (status == oled_on) ? "on" : "off";
   send_message_forced(msg);

   display_setPowerSaveMode(status);
}

void Get_sensor_value(sensor_t sensor)
{
   String sensor_val  = "";
   String sensor_name = "";

   switch(sensor)
   {
   case sensor_temperature: 
      sensor_val += Get_AHT10_last_measured_temperature_string() + " C";
      sensor_name = "Temperature sensor";
      break;

   case sensor_humidity: 
      sensor_val += Get_AHT10_actual_humidity_string() + " %";
      sensor_name = "Humidity sensor";
      break;
   }

   send_message_forced(">> <b>" + sensor_name + "</b>\n" + sensor_val);
}

void Get_runtime()
{
  unsigned long ms = millis();
  unsigned long sec = ms/1000;
  unsigned long min = sec/60;
  unsigned long h = min/60;

  min = min - (h*60);
  sec = sec - ((h*3600)+(min*60));

  String reply = ">> <b>Runtime</b>\n";
  reply += h;
  reply += "<i>(h)</i>  ";
  reply += min;
  reply += "<i>(min)</i>  ";
  reply += sec;
  reply += "<i>(sec)</i>";
  send_message_forced(reply);
}
