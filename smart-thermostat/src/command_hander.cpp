#include "command_handler.h"

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
      if (text == "/display_on") {display_setPowerSaveMode(oled_on);message(oled_setOn);}
      else if (text == "/display_off") {display_setPowerSaveMode(oled_off);message(oled_setOff);}
      else if (text == "/temperature") message(get_temperature);
      else if (text == "/humidity") message(get_humidity);
      else if (text == "/runtime");
      else if (text == "/version");
      else send_message(chat_id, "<b>>> Error</b>\nUnknown command.","HTML");
   }
   return true;
}