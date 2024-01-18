#include "wifi_controller.h"
#include <NTPClient.h>
#include <WiFiUdp.h>


#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif
WiFiClientSecure client;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void initialize_wifi_controller()
{
   #ifdef ESP8266
   configTime(0, 0, "pool.ntp.org");      // Get UTC time via NTP
   client.setTrustAnchors(&cert);         // Add root certificate for api.telegram.org
   #endif

   /* WiFi set to station mode
   * The ESP8266 is operating like a WiFi client and is able to connect to a WiFi access point */
   WiFi.mode(WIFI_STA);
   WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

   #ifdef ESP32
   client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
   #endif

   while (WiFi.status() != WL_CONNECTED)
   {
      delay(WIFI_INITIALIZATION_DELAY_TIME);
   }

   client.setInsecure(); // insecure..., but the most simple way to handle https-POST on ESP8266

   // Initialize a NTPClient to get time
   timeClient.begin();
   // Set offset time in seconds to adjust for your timezone, for example: GMT +1 = 3600, GMT +8 = 28800, GMT -1 = -3600, GMT 0 = 0
   timeClient.setTimeOffset(3600);
}

void wifi_controller_main()
{
   timeClient.update(); // update time
   WiFi.RSSI();
   // TODO!!!
   // újracsatlakozás ha a wifi kapcsolat megszakad...
}

int Get_NTP_hour()
{
   if(timeClient.isTimeSet())
   {
      unsigned long rawTime = timeClient.getEpochTime();
      unsigned long hours = (rawTime % 86400L) / 3600;
      return (int)hours;
   }
   else return 25;
}

int Get_NTP_minute()
{
   if(timeClient.isTimeSet())
   {
      unsigned long rawTime = timeClient.getEpochTime();
      unsigned long minutes = (rawTime % 3600) / 60;
      return (int)minutes;
   }
   else return 61;
}

String Get_NTP_time()
{
   if(timeClient.isTimeSet())
   {
      unsigned long rawTime = timeClient.getEpochTime();
      unsigned long hours = (rawTime % 86400L) / 3600;
      String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

      unsigned long minutes = (rawTime % 3600) / 60;
      String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

      unsigned long seconds = rawTime % 60;
      String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

      return hoursStr + ":" + minuteStr;
   }
   else return "--:--";
}

String Get_NTP_day()
{
   if(timeClient.isTimeSet())
   {
      switch(timeClient.getDay())
      {
         case 0: return "Su";
         case 1: return "Mo";
         case 2: return "Tu";
         case 3: return "We";
         case 4: return "Th";
         case 5: return "Fr";
         case 6: return "Sa";
         default: return "--";
      }
   }
   return "--";
}

String GetIP()
{
   if(Get_connection_status()) return WiFi.localIP().toString();
   else return "No wifi connection!";
}

String GetMAC()
{
   if(Get_connection_status()) return WiFi.macAddress();
   else return "No wifi connection!";
}

bool Get_connection_status()
{
   // WL_CONNECTING is a temporal solution for buggy wifi-library 
   // See further: https://github.com/esp8266/Arduino/issues/7432
   return (WiFi.status() == WL_CONNECTED || WiFi.status() == WL_CONNECTING); 
}

String Get_connection_status_string()
{
   String status = "";
   switch(WiFi.status())
   {
   case WL_NO_SHIELD:
      status = "No shield";
      break;
   case WL_IDLE_STATUS:
      status = "Idle";
      break;
   case WL_NO_SSID_AVAIL:
      status = "No SSID available";
      break;
   case WL_SCAN_COMPLETED:
      status = "Scan completed";
      break;
   case WL_CONNECTED:
      status = "Connected";
      break;
   case WL_CONNECT_FAILED:
      status = "Connection failed";
      break;
   case WL_CONNECTION_LOST:
      status = "Connection lost";
      break;
   case WL_DISCONNECTED:
      status = "Disconnected";
      break;
   case WL_CONNECTING:
      status = "Connecting";
      break;
   default:
      status = "Unknown";
      break;
   }

   return status;
}