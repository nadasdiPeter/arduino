/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  BASIC configuration of the project.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef CONFIG_H
   #define CONFIG_H

   #include <Arduino.h> 

   #define VERSION                           "v1.0.0.0"
   #define TELEGRAM_BOT_CYCLE_TIME           1000

   #define LED_PIN                           D8   
   #define OLED_SDA_PIN                      D5
   #define OLED_SCL_PIN                      D6

   #define AHT10_SDA_PIN                     D5
   #define AHT10_SCL_PIN                     D6
   #define AHT10_INITIALIZATION_DELAY_TIME   5000
   #define AHT10_TEMPERATURE_ARRAY_SIZE      100
   #define AHT10_TEMPERATURE_SAMPLING_TIME   3000

   #define DISPLAY_REFRESH_RATE              1000
   
   #define WIFI_INITIALIZATION_DELAY_TIME    100

   enum aht10_status_t
   {
      aht10_uninitialized,
      aht10_initialized,
      aht10_unknown,
   };

   enum sensor_t
   {
      sensor_temperature,
      sensor_humidity,
   };

   enum oled_status_t
   {
      oled_off,
      oled_on,
   };

   enum sheduling_time_t
   {
      day_time,
      night_time,
   };

   enum message_t
   {
      wifi_connecting,
      wifi_connected,
      aht10_init,
      aht10_ready,
      get_temperature,
      get_humidity,
      oled_setOn,
      oled_setOff
   };

   struct Shedule 
   {
      int daytime_start_hrs;
      int daytime_start_min;
      int nighttime_start_hrs;
      int nighttime_start_min;
   };

#if(AHT10_TEMPERATURE_SAMPLING_TIME < 2000)
#error Measurement with high frequency leads to heating of the sensor, must be at least 2 seconds apart to keep self-heating below 0.1C
#endif

#endif /* CONFIG_H */