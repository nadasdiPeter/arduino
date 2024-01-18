#include <Arduino.h>
#include "display_controller.h"
#include "wifi_controller.h"
#include "telegram_bot.h"
#include "aht10_controller.h"

/* Initialize all needed resource. */
void setup() 
{
   initialize_display_controller();
   initialize_wifi_controller();
   initialize_telegram_bot();
   initialize_aht10_controller();
   initialize_heating_controller();
}

/* main loop */
void loop() 
{
   wifi_controller_main();
   display_controller_main();
   aht10_controller_main();
   telegram_bot_main();
   heating_controller_main();
}