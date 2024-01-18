#include "telegram_bot.h"

UniversalTelegramBot bot(BOTtoken, client);
Timer bot_callback_timer;

bool is_verified_user(String chat_id)
{
  return (chat_id == CHAT_ID);
}

bool send_message(String message) 
{
  return bot.sendMessage(CHAT_ID, message, "HTML");
}

bool send_message(String title, String message) 
{
  String msg = ">> <b>" + title + "</b>\n" + message;
  return bot.sendMessage(CHAT_ID, msg, "HTML");
}

bool send_message(String chat_id, String message, String mode) 
{
  /* mode refers for text formatting, can be HTML, Markdown, MarkdownV2. */
  return bot.sendMessage(chat_id, message, mode);
}

bool send_message_forced(String message) 
{
  while (send_message(message) != true){}
  return true;
}

bool send_message_forced(String title, String message) 
{
  while (send_message(title, message) != true){}
  return true;
}

bool send_message_forced(String chat_id, String message, String mode) 
{
  while (send_message(chat_id, message, mode) != true){}
  return true;
}

void handle_NewMessages(int number_of_NewMessages) 
{ 
  for (int i=0; i<number_of_NewMessages; i++) 
  {
    command_interpreter(bot.messages[i]);
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

void set_commands(String commands) 
{
  /* mode refers for text formatting, can be HTML, Markdown, MarkdownV2. */
  bot.setMyCommands(commands);
}

void initialize_telegram_bot() 
{
   bot_callback_timer.setInterval(TELEGRAM_BOT_CYCLE_TIME);
   bot_callback_timer.setCallback(bot_callback);
   bot_callback_timer.start(); 
}

void telegram_bot_main()
{
  bot_callback_timer.update();
}