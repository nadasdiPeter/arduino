#include "config_definition_esp.h"
#include "buzzer_controller.h"
#include <Arduino.h>
#include "timer.h"

Timer buzzer_timer;

void buzzer_main()
{
   if(buzzer_timer.isRunning()) buzzer_timer.update();
}

void buzzer_timer_Callback()
{
   noTone(BUZZER);
}

void request_beep(int hertz)
{
   tone(BUZZER, hertz);
   buzzer_timer.setTimeout(BEEP_TIME); 
   buzzer_timer.setCallback(buzzer_timer_Callback);
   buzzer_timer.start();
}

void initialize_buzzer()
{
   pinMode(BUZZER,OUTPUT);
   noTone(BUZZER);
}