#include "config.h"
#include "serial_controller.h"
#include "hardware_controller.h"
#include <dht11.h>
#include <AHTxx.h>

dht11 DHT11;
AHTxx aht10(AHTXX_ADDRESS_X38, AHT1x_SENSOR);

void initialize_hardware_controller()
{
   pinMode(INBUILT_LED_PIN, OUTPUT);
   pinMode(WIFI_LED, OUTPUT);

   BuiltInLED_ON();
   WifiLED_ON();

  while (aht10.begin() != true) //for ESP-01 use aht10.begin(0, 2);
  {
    Serial.println(F("AHT1x not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
    delay(5000);
  }
}

void hardware_controller_main()
{
}

void BuiltInLED_ON()
{
   digitalWrite(INBUILT_LED_PIN, LOW);
}

void BuiltInLED_OFF()
{
   digitalWrite(INBUILT_LED_PIN, HIGH);
}

void WifiLED_ON()
{
   digitalWrite(WIFI_LED, HIGH);
}

void WifiLED_OFF()
{
   digitalWrite(WIFI_LED, LOW);
}

int Get_DHT11_temperature()
{
   DHT11.read(D8);
   return DHT11.temperature;
}

int Get_DHT11_humidity()
{
   DHT11.read(D8);
   return DHT11.humidity;
}

float Get_AHT10_humidity()
{
  float ahtValue = aht10.readHumidity(); //read 6-bytes via I2C, takes 80 millisecond
  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    return ahtValue;
  }
  return 0.0f;
}

float Get_AHT10_temperature()
{
  float ahtValue = aht10.readTemperature(); //read 6-bytes via I2C, takes 80 millisecond
  if (ahtValue != AHTXX_ERROR) //AHTXX_ERROR = 255, library returns 255 if error occurs
  {
    return ahtValue;
  }
  return 0.0f;
}