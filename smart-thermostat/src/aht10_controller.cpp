#include "aht10_controller.h"

extern void measure_temperature(int init);
extern void aht10_callback();

AHTxx aht10(AHTXX_ADDRESS_X38, AHT1x_SENSOR);
aht10_status_t aht10_sensor_status = aht10_unknown;
Timer aht10_timer;
float temperature_array[AHT10_TEMPERATURE_ARRAY_SIZE];
int temperature_array_pointer = 0;

void initialize_aht10_controller()
{
   aht10_sensor_status = aht10_uninitialized;
   while (aht10.begin(AHT10_SDA_PIN, AHT10_SCL_PIN) != true)
   {
      delay(AHT10_INITIALIZATION_DELAY_TIME);
   }
   aht10_sensor_status = aht10_initialized;

   measure_temperature(1);

   aht10_timer.setInterval(AHT10_TEMPERATURE_SAMPLING_TIME);
   aht10_timer.setCallback(aht10_callback);
   aht10_timer.start();
}

void aht10_controller_main()
{
   aht10_timer.update();
}

aht10_status_t Get_AHT10_status()
{
   return aht10_sensor_status;
}

void aht10_callback()
{
   aht10_timer.stop();
   measure_temperature(0);
   aht10_timer.start();
}

/* HUMIDITY DATA */

float Get_AHT10_actual_humidity_float()
{
   float ahtValue = aht10.readHumidity(); //read 6-bytes via I2C, takes 80 millisecond
   if (ahtValue != AHTXX_ERROR)
   {
      return ahtValue;
   }
   return 0.0f;
}

String Get_AHT10_actual_humidity_string()
{
   String humidity = "";
   humidity += Get_AHT10_actual_humidity_float();
   return humidity;
}

/* TEMPERATURE DATA */

void measure_temperature(int init)
{
   if(init == 1)
   {
      float t = Get_AHT10_actual_temperature_float();
      for(int i=0; i < AHT10_TEMPERATURE_ARRAY_SIZE; i++)
      {
         temperature_array[i] = t;
      }
   }
   else
   {
      temperature_array_pointer = (temperature_array_pointer + 1 >= AHT10_TEMPERATURE_ARRAY_SIZE) ? 0 : temperature_array_pointer+1;
      temperature_array[temperature_array_pointer] = Get_AHT10_actual_temperature_float();
   }
}

float Get_AHT10_actual_temperature_float()
{
   float ahtValue = aht10.readTemperature(); //read 6-bytes via I2C, takes 80 millisecond
   if (ahtValue != AHTXX_ERROR)
   {
      return ahtValue;
   }
   return 0.0f;
}

String Get_AHT10_actual_temperature_string()
{
   String temperature = "";
   temperature += Get_AHT10_actual_temperature_float();
   return temperature;
}

String Get_AHT10_last_measured_temperature_string()
{
   String temperature = "";
   temperature += temperature_array[temperature_array_pointer];
   return temperature;
}

float Get_AHT10_last_measured_temperature_float()
{
   return temperature_array[temperature_array_pointer];
}