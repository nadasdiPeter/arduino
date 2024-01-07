#include "wifi_controller.h"

#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif
WiFiClientSecure client;


void initialize_wifi_controller()
{
   #ifdef ESP8266
   configTime(0, 0, "pool.ntp.org");      // Get UTC time via NTP
   client.setTrustAnchors(&cert);         // Add root certificate for api.telegram.org
   #endif

   /* WiFi set to station mode
   * The ESP8266 is operating like a WiFi client and is able to connect to a WiFi access point */
   message(wifi_connecting);
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
   message(wifi_connected);
}

void wifi_controller_main()
{
   // TODO!!!
   // újracsatlakozás ha a wifi kapcsolat megszakad...
}

String GetIP()
{
   if(WiFi.status() == WL_CONNECTED)
      return WiFi.localIP().toString();
   else return "No wifi connection!";
}

String GetMAC()
{
   if(WiFi.status() == WL_CONNECTED)
      return WiFi.macAddress();
   else return "No wifi connection!";
}