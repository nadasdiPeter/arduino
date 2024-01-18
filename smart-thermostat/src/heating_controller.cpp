#include "heating_controller.h"
#include "aht10_controller.h"
#include "telegram_bot.h"

float target_value;
float negative_difference;
float positive_difference;
bool heating_in_progress = false;
Shedule sheduling;


extern void calculate_heating_state();

sheduling_time_t day_night_calculation()
{
   if( Get_NTP_hour() < sheduling.daytime_start_hrs || Get_NTP_hour() > sheduling.nighttime_start_hrs )
   {
      return night_time;
   }

   if((Get_NTP_hour() == sheduling.daytime_start_hrs) && (Get_NTP_minute() <= sheduling.daytime_start_min))
   {
      return night_time;
   }

   if((Get_NTP_hour() == sheduling.nighttime_start_hrs) && (Get_NTP_minute() >= sheduling.nighttime_start_min))
   {
      return night_time;
   }

   return day_time;
}

void heating_controller_main()
{
   calculate_heating_state();
   digitalWrite(LED_PIN,(heating_in_progress == true) ? HIGH : LOW);
}

void calculate_heating_state()
{
   /* Hysteresis implementation: */
   if((heating_in_progress == false) && (Get_AHT10_last_measured_temperature_float() < Get_HeatingNegativeLimit_float()))
   {
      heating_in_progress = true; /* state change required: NO HEATING -> HEATING */
      send_message_forced(">> <b>Heating controller</b>\nHeating turned ON");
   }

   if((heating_in_progress == true) && (Get_AHT10_last_measured_temperature_float() > Get_HeatingPositiveLimit_float()))
   {
      heating_in_progress = false; /* state change required: HEATING -> NO HEATING */
      send_message_forced(">> <b>Heating controller</b>\nHeating turned OFF");
   }
}

void initialize_heating_controller()
{
   target_value = 22.5f;
   negative_difference = 0.1f;
   positive_difference = 0.2f;

   sheduling.daytime_start_hrs = 5;
   sheduling.daytime_start_min = 40;
   sheduling.nighttime_start_hrs = 19;
   sheduling.nighttime_start_min = 30;

   pinMode(LED_PIN,OUTPUT);
   digitalWrite(LED_PIN, LOW);
}

float Get_HeatingTarget_float()
{
   return target_value;
}

String Get_HeatingTarget_string()
{
   return (String)Get_HeatingTarget_float();
}

float Get_HeatingNegativeLimit_float()
{
   return target_value-negative_difference;
}

String Get_HeatingNegativeLimit_string()
{
   return (String)Get_HeatingNegativeLimit_float();
}

float Get_HeatingPositiveLimit_float()
{
   return target_value+positive_difference;
}

String Get_HeatingPositiveLimit_string()
{
   return (String)Get_HeatingPositiveLimit_float();
}

bool Heating_is_in_progress()
{
   return heating_in_progress;
}

void Set_target_temperature(float target)
{
   target_value = target;
}

void Set_negative_difference(float negative_diff)
{
   negative_difference = negative_diff;
}

void Set_positive_difference(float positive_diff)
{
   positive_difference = positive_diff;
}