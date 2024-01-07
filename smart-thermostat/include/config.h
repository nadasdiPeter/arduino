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

   #define TELEGRAM_BOT_CYCLE_TIME           1000
   
   #define OLED_SDA_PIN                      D5
   #define OLED_SCL_PIN                      D6

   #define AHT10_SDA_PIN                     D5
   #define AHT10_SCL_PIN                     D6
   #define AHT10_INITIALIZATION_DELAY_TIME   5000
   #define AHT10_TEMPERATURE_ARRAY_SIZE      100
   #define AHT10_TEMPERATURE_SAMPLING_TIME   2500
   
   #define WIFI_INITIALIZATION_DELAY_TIME    100

   enum aht10_status_t
   {
      aht10_uninitialized,
      aht10_initialized,
      aht10_unknown,
   };

   enum oled_status_t
   {
      oled_on,
      oled_off,
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

#if(AHT10_TEMPERATURE_SAMPLING_TIME < 2000)
#error Measurement with high frequency leads to heating of the sensor, must be at least 2 seconds apart to keep self-heating below 0.1C
#endif

#endif /* CONFIG_H */