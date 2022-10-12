
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define DHTTYPE                 DHT11

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <WiFiUdp.h>
#include <ESPAsyncWebServer.h>
#include <NTPClient.h>
#include <FastLED.h>
#include <DHT.h>
#include <DHT_U.h>

// ESP8266 PIN LAYOUT
#define POWER_INDICATION_PIN        D4
#define LED_DATA_PIN                D3
#define DHT_PIN                     D5
#define BUZZER_PIN                  D6
#define LIGHT_SENSOR                A0

// FastLED Library
#define NUMBER_OF_LEDS              30

// Credentials
#define ssid                        "DPNetwork-2GHz"
#define password                    "821Ay8ve8TTzt"

// URI parameters
#define PARAM_INPUT_ELEMENT         "element"
#define PARAM_INPUT_STATE           "state"

// Web IDs
#define STATE_RDB_OFF               "on_off_auto__off"
#define STATE_RDB_ON                "on_off_auto__on"
#define STATE_RDB_AUTO              "on_off_auto__auto"
#define BRIGHTNESS_RANGE_BTN        "brightness_range_btn"
#define COLOR_PICKER                "color_picker"
#define ANIMATION_PICKER            "animation_picker"
#define BEEP_BUTTON                 "mute_unmute"

// ELEMNT IDENTIFIERS
#define STATE_RADIOBUTTON_ON        1
#define STATE_RADIOBUTTON_OFF       2
#define STATE_RADIOBUTTON_AUTO      3
#define COLOR_0                     0
#define COLOR_1                     1
#define COLOR_2                     2
#define COLOR_3                     3
#define COLOR_4                     4
#define COLOR_5                     5
#define ANIMATION_0                 0
#define ANIMATION_1                 1
#define ANIMATION_2                 2
#define ANIMATION_3                 3
#define ANIMATION_4                 4
#define ANIMATION_5                 5

// LIGHT SENSOR DEFINITIONS
#define LIGHT_SENSOR_MIN            180 // ABSOLULT DARKNESS
#define LIGHT_SENSOR_MAX            930 // ABSOLULT BRIGHTNESS

// Enum definitions
typedef enum{ On, Off, Auto } state_radiobutton_e;
typedef enum{ White_rb, Green_rb, DarkGreen_rb, LightGreen_rb, Yellow_rb, Red_rb } color_rb_e;
typedef enum{ anim_0_rb, anim_1_rb, anim_2_rb, anim_3_rb, anim_4_rb, anim_5_rb } animation_rb_e;

// Global variables
state_radiobutton_e STATE_BUTTON          = Auto;
color_rb_e COLOR_RADIO_BUTTONS            = White_rb;
animation_rb_e ANIMATION_RADIO_BUTTONS    = anim_0_rb;
int BRIGHTNESS_RANGE_BUTTON               = 128;

// Store current time
const long utcOffsetInSeconds = 7200; // UTC +2 (due to sommer-time)
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// DHT temperature sensor
float TEMPERATURE_DATA;
float HUMIDITY_DATA; 
DHT_Unified dht(DHT_PIN, DHTTYPE);
uint32_t delayMS = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//FastLed Ledstrip driver
CRGB leds[NUMBER_OF_LEDS];

bool BEEP_BUTTON_STATE = true;
bool TONE_REQ = false;

int LIGHT = 0;

// HTML skeleton
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
   <head>
      <title>NodeMCU</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <meta http-equiv="refresh" content="10">
      <link rel="icon" href="data:,">
      <style>
         html {font-family: Arial; font-size: 1rem; display: inline-block; text-align: center;}
         h2 {font-family: verdana;font-size: 2.0rem;margin-bottom:10px;}
         h3 {margin-bottom:3px; margin-top: 10px; margin-right:10px; margin-left: 20px }
         h4 {margin-bottom:5px; margin-top: 5px }
         h5 {margin-bottom:5px; margin-top: 5px }
         p {font-size: 1.0rem;}
         hr {width: 60vw; height:2px;border-width:0;color:gray;background-color:gray; margin-bottom:20px}
         body {width: 100vw; height: 100vh; margin:0px auto; padding-bottom: 25px;}
         span.small {font-size: smaller;font-family: Consolas,monaco,monospace; margin-top: 10px;}
         .row {--bs-gutter-x: 1.5rem; --bs-gutter-y: 0; display: flex; flex-wrap: wrap; margin-top: calc(var(--bs-gutter-y) * -1); margin-right: calc(var(--bs-gutter-x) / -2); margin-left: calc(var(--bs-gutter-x) / -2);}
         .col { flex: 1 0 0%; width: 50%;}
         .switch {position: relative; display: inline-block; width: 120px; height: 50px} 
         .switch input {display: none}
         .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
         .slider:before {position: absolute; content: ""; height: 34px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
         input:checked+.slider {background-color: #007d00}
         input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
      </style>
   </head>
   <body>
      <section><div><h2>Peter's NodeMCU</h2><p>LEDStrip controller & Home assistant server.</p><hr></div></section>
      <center>
         <table>
            <tr>
               <td><h4>Time:</h4></td>
               <td><h4>%TIME_PLACEHOLDER%</h4></td>
            </tr>
            <tr>
               <td><h4>Temperature:</h4></td>
               <td><h4>%TEMPERATURE_PLACEHOLDER% (&#8451)</h4></td>
            </tr>
            <tr>
               <td><h4>Humidity:</h4></td>
               <td><h4>%HUMIDITY_PLACEHOLDER% (&#37)</h4></td>
            </tr>
            <tr>
               <td><h4>Illuminance:</h4></td>
               <td><h4>%ILLUMINANCE_PLACEHOLDER% (&#37)</h4></td>
            </tr>
            <tr>
         </table>
      </center>
      <br>
      <hr>
      <center>
         <table>
            <tr>
               <td>
                  <center>
                     <h5>Main Settings:</h5>
                     <form>
                        %STATE_RADIO_BUTTON_PLACEHOLDER%
                        <br><br>
						      %BEEP_SWITCH_PLACEHOLDER%
                     </form>
                  </center>
               <td>
            </tr>
            <tr>
               <td>
                  <center>
                     <br>
                     <h5>Brightness:</h5>
                     <div>
                        %BRIGHTNESS_PLACEHOLDER%
                     </div>
                  </center>
               </td>
            </tr>
            <tr>
               <td>
                  <center>
                     <br>
                     <h5>Color:</h5>
                     <form>
                        %COLOR_BUTTONS_PLACEHOLDER%
                     </form>
                  </center>
               </td>
            </tr>
            <tr>
               <td>
                  <center>
                     <h5>Custom color:</h5>
                     <form>
                        <input type="color" id="colorpicker" value="#00ff00">
                        <input type="submit" value="Submit">
                     </form>
                  </center>
               </td>
            </tr>
            <tr>
               <td>
                  <center>
                     <br>
                     <h5>Animation:</h5>
                     <form>
                        %ANIMATION_PLACEHOLDER%
                     </form>
                  </center>
               </td>
            </tr>            
         </table>
      </center>
      <br>      
      <hr>
      <script>
         function toggleCheckbox(element) 
         {
            var xhr = new XMLHttpRequest();
            if(element.checked)
            { 
               xhr.open("GET", "/update?element="+element.id+"&state=1", true);
            }
            else 
            { 
               xhr.open("GET", "/update?element="+element.id+"&state=0", true); 
            }
            xhr.send();
         }

         function sendBrighness(element) 
         {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/update?element="+element.id+"&state="+element.value, true); 
            xhr.send();
         }

         function sendColor(element) 
         {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/update?element="+element.name+"&state="+element.value, true); 
            xhr.send();
         }

         function sendAnimation(element) 
         {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/update?element="+element.name+"&state="+element.value, true); 
            xhr.send();
         }
      </script>

   </body>
</html>
)rawliteral";


void update_LEDStrip()
{
   FastLED.setBrightness(BRIGHTNESS_RANGE_BUTTON);

   if((STATE_BUTTON == On) || (STATE_BUTTON == Auto))
   {
      switch (COLOR_RADIO_BUTTONS)
      {
      case COLOR_0:
         FastLED.showColor(CRGB::White);
         break;
      case COLOR_1:
         FastLED.showColor(CRGB::Green);
         break;
      case COLOR_2:
         FastLED.showColor(CRGB::DarkGreen);
         break;
      case COLOR_3:
         FastLED.showColor(CRGB::LightGreen);
         break;
      case COLOR_4:
         FastLED.showColor(CRGB::Yellow);
         break;
      case COLOR_5:
         FastLED.showColor(CRGB::Red);
         break;
      default:
         break;
      }
   }

   if(STATE_BUTTON == Off)
   {
      FastLED.showColor(CRGB::Black);
   }
}

String output_state_radiobutton(int id)
{ 
   if((id == STATE_RADIOBUTTON_ON) && (STATE_BUTTON == On))       return "checked";
   if((id == STATE_RADIOBUTTON_OFF) && (STATE_BUTTON == Off))     return "checked";
   if((id == STATE_RADIOBUTTON_AUTO) && (STATE_BUTTON == Auto))   return "checked";
   return "";
}

String output_beep_checkboxstate()
{ 
   if(BEEP_BUTTON_STATE == true) return "checked";
   return "";
}

String animation_radiobuttons(int id)
{ 
   if((id == ANIMATION_0) && (ANIMATION_RADIO_BUTTONS == anim_0_rb))       return "checked";
   if((id == ANIMATION_1) && (ANIMATION_RADIO_BUTTONS == anim_1_rb))       return "checked";
   if((id == ANIMATION_2) && (ANIMATION_RADIO_BUTTONS == anim_2_rb))       return "checked";
   if((id == ANIMATION_3) && (ANIMATION_RADIO_BUTTONS == anim_3_rb))       return "checked";
   if((id == ANIMATION_4) && (ANIMATION_RADIO_BUTTONS == anim_4_rb))       return "checked";
   if((id == ANIMATION_5) && (ANIMATION_RADIO_BUTTONS == anim_5_rb))       return "checked";
   return "";
}

String colors_radiobuttons(int id)
{ 
   if((id == COLOR_0) && (COLOR_RADIO_BUTTONS == White_rb))       return "checked";
   if((id == COLOR_1) && (COLOR_RADIO_BUTTONS == Green_rb))       return "checked";
   if((id == COLOR_2) && (COLOR_RADIO_BUTTONS == DarkGreen_rb))   return "checked";
   if((id == COLOR_3) && (COLOR_RADIO_BUTTONS == LightGreen_rb))  return "checked";
   if((id == COLOR_4) && (COLOR_RADIO_BUTTONS == Yellow_rb))      return "checked";
   if((id == COLOR_5) && (COLOR_RADIO_BUTTONS == Red_rb))         return "checked";
   return "";
}

void request_processing(String elm, String sts)
{ 
   if((elm == STATE_RDB_ON) && sts == "1")
   {
      STATE_BUTTON = On;
      digitalWrite(POWER_INDICATION_PIN, LOW);  // PowerLED ON
      Serial.print(">> PowerMode SET to ON\n");
   } 

   if((elm == STATE_RDB_OFF) && sts == "1")
   {
      STATE_BUTTON = Off;
      digitalWrite(POWER_INDICATION_PIN, HIGH); // PowerLED Off
      Serial.print(">> PowerMode SET to OFF\n");
   }

   if((elm == STATE_RDB_AUTO) && sts == "1")
   {
      STATE_BUTTON = Auto;
      digitalWrite(POWER_INDICATION_PIN, LOW); // PowerLED ON
      Serial.print(">> PowerMode SET to AUTO\n");
   }

   if(elm == BEEP_BUTTON)
   {
      if(sts == "1")
      {
         BEEP_BUTTON_STATE = true;
         Serial.print(">> Beeping sound SET to ON\n");
      }
      if(sts == "0")
      {
         BEEP_BUTTON_STATE = false;
         Serial.print(">> Beeping sound SET to OFF\n");
      }
   }

   if((elm == BRIGHTNESS_RANGE_BTN))
   {
      BRIGHTNESS_RANGE_BUTTON = sts.toInt();
      Serial.print(">> Brigthness level SET to: " + String(BRIGHTNESS_RANGE_BUTTON) + "\n");
   } 

   if(elm == COLOR_PICKER)
   {
      Serial.print(">> Color SET to: (" + sts + ") - ");
      switch (sts.toInt())
      {
      case 0:
         Serial.print(" White\n");
         COLOR_RADIO_BUTTONS = White_rb;
         break;
      case 1:
         Serial.print(" Green\n");
         COLOR_RADIO_BUTTONS = Green_rb;
         break;
      case 2:
         Serial.print(" DarkGreen\n");
         COLOR_RADIO_BUTTONS = DarkGreen_rb;
         break;
      case 3:
         Serial.print(" LightGreen\n");
         COLOR_RADIO_BUTTONS = LightGreen_rb;
         break;
      case 4:
         Serial.print(" Yellow\n");
         COLOR_RADIO_BUTTONS = Yellow_rb;
         break;
      case 5:
         Serial.print(" Red\n");
         COLOR_RADIO_BUTTONS = Red_rb;
         break;
      default:
         break;
      }
   }

   if(elm == ANIMATION_PICKER)
   {
      Serial.print(">> Animation SET to: (" + sts + ") - ");
      switch (sts.toInt())
      {
      case 0:
         Serial.print(" Animation 01\n");
         ANIMATION_RADIO_BUTTONS = anim_0_rb;
         break;
      case 1:
         Serial.print(" Animation 02\n");
         ANIMATION_RADIO_BUTTONS = anim_1_rb;
         break;
      case 2:
         Serial.print(" Animation 03\n");
         ANIMATION_RADIO_BUTTONS = anim_2_rb;
         break;
      case 3:
         Serial.print(" Animation 04\n");
         ANIMATION_RADIO_BUTTONS = anim_3_rb;
         break;
      case 4:
         Serial.print(" Animation 05\n");
         ANIMATION_RADIO_BUTTONS = anim_4_rb;
         break;
      case 5:
         Serial.print(" Animation 06\n");
         ANIMATION_RADIO_BUTTONS = anim_5_rb;
         break;
      default:
         break;
      }
   }
   update_LEDStrip();
}

// Replaces placeholder with button section in your web page
String processor(const String& var)
{
   if(var == "STATE_RADIO_BUTTON_PLACEHOLDER")
   {
      String buttons = "";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"on_off_auto__off\" name=\"on_off_auto\" value=\"0\" onchange=\"toggleCheckbox(this)\" "  + output_state_radiobutton(STATE_RADIOBUTTON_OFF) + ">OFF</label>";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"on_off_auto__auto\" name=\"on_off_auto\" value=\"1\" onchange=\"toggleCheckbox(this)\" " + output_state_radiobutton(STATE_RADIOBUTTON_AUTO) + ">AUTO</label>";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"on_off_auto__on\" name=\"on_off_auto\" value=\"2\" onchange=\"toggleCheckbox(this)\" "   + output_state_radiobutton(STATE_RADIOBUTTON_ON) + ">ON</label>";
      return buttons;
   }

   if(var == "BEEP_SWITCH_PLACEHOLDER")
   {
      String buttons = "<label class=\"toggle\"><input type=\"checkbox\" id=\"mute_unmute\" name=\"mute_unmute\" onchange=\"toggleCheckbox(this)\" " + output_beep_checkboxstate() + ">Beep On/Off</label>";
      return buttons;
   }

   if(var == "BRIGHTNESS_PLACEHOLDER")
   {
      String buttons = "<input type=\"range\" id=\"brightness_range_btn\" name=\"brightness\" min=\"0\" max=\"255\" value=\"" + String(BRIGHTNESS_RANGE_BUTTON) + "\" onchange=\"sendBrighness(this)\">";
      return buttons;
   }

   if(var == "COLOR_BUTTONS_PLACEHOLDER")
   {
      String buttons = "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_0\" name=\"color_picker\" value=\"0\" onchange=\"sendColor(this)\" " + colors_radiobuttons(0) + ">White</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_1\" name=\"color_picker\" value=\"1\" onchange=\"sendColor(this)\" "       + colors_radiobuttons(1) + ">Green</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_2\" name=\"color_picker\" value=\"2\" onchange=\"sendColor(this)\" "       + colors_radiobuttons(2) + ">DarkGreen</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_3\" name=\"color_picker\" value=\"3\" onchange=\"sendColor(this)\" "       + colors_radiobuttons(3) + ">LightGreen</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_4\" name=\"color_picker\" value=\"4\" onchange=\"sendColor(this)\" "       + colors_radiobuttons(4) + ">Yellow</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_5\" name=\"color_picker\" value=\"5\" onchange=\"sendColor(this)\" "       + colors_radiobuttons(5) + ">Red</label>\n";
      return buttons;
   }

   if(var == "ANIMATION_PLACEHOLDER")
   {
      String buttons  = "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_0\" name=\"animation_picker\" value=\"0\" onchange=\"sendAnimation(this)\" "       + animation_radiobuttons(0) + ">Animation 01</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_1\" name=\"animation_picker\" value=\"1\" onchange=\"sendAnimation(this)\" "       + animation_radiobuttons(1) + ">Animation 02</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_2\" name=\"animation_picker\" value=\"2\" onchange=\"sendAnimation(this)\" "       + animation_radiobuttons(2) + ">Animation 03</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_3\" name=\"animation_picker\" value=\"3\" onchange=\"sendAnimation(this)\" "       + animation_radiobuttons(3) + ">Animation 04</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_4\" name=\"animation_picker\" value=\"4\" onchange=\"sendAnimation(this)\" "       + animation_radiobuttons(4) + ">Animation 05</label>\n";
      buttons += "<label class=\"radio-inline\"><input type=\"radio\" id=\"color_5\" name=\"animation_picker\" value=\"5\" onchange=\"sendAnimation(this)\" "       + animation_radiobuttons(5) + ">Animation 06</label>\n";
      return buttons;
   }


   if(var == "TIME_PLACEHOLDER")
   {
      // Time is updated in the loop function
      String time_string = "";
      time_string += daysOfTheWeek[timeClient.getDay()];
      time_string += ", ";
      time_string += timeClient.getHours();
      time_string += ":";
      time_string += timeClient.getMinutes();
      return time_string;
   }
   if(var == "TEMPERATURE_PLACEHOLDER")
   {
      return String((int)TEMPERATURE_DATA);
   }
   if(var == "HUMIDITY_PLACEHOLDER")
   {
      return String((int)HUMIDITY_DATA);
   }
   if(var == "ILLUMINANCE_PLACEHOLDER")
   {
      return String(LIGHT);
   }
   return String();
}

void setup()
{
   Serial.begin(115200);
   pinMode(POWER_INDICATION_PIN, OUTPUT);
   pinMode(BUZZER_PIN, OUTPUT);
   pinMode(LIGHT_SENSOR, INPUT);
  
   // Connect to Wi-Fi
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(1000);
      Serial.println("Connecting to WiFi..");
   }

   // Print ESP8266 WebServer Local IP Address
   Serial.print("IP-address: ");
   Serial.println(WiFi.localIP());

   // Route for root / web page
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
   {
      request->send_P(200, "text/html", index_html, processor);
   });

   // Handler for /update requests
   server.onNotFound([](AsyncWebServerRequest *request)
   {
      Serial.println(">> UNKNOWN REQUEST RECEIVED\n");
      request->send_P(200, "text/html", index_html, processor);
   });

   // Handler for /update requests
   server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) 
   {
      String input_element;
      String input_state;
      // GET input1 value on <ESP_IP>/update?element=<input_element>&state=<input_state>
      if (request->hasParam(PARAM_INPUT_ELEMENT) && request->hasParam(PARAM_INPUT_STATE))
      {
         input_element = request->getParam(PARAM_INPUT_ELEMENT)->value();
         input_state = request->getParam(PARAM_INPUT_STATE)->value();
         request_processing(input_element, input_state);
         TONE_REQ = true;
      }
      else
      {
         // Something went wrong
      }
      request->send(200, "text/plain", "OK");
   });

   // Start server
   server.begin();
   timeClient.begin();
   FastLED.addLeds<WS2812, LED_DATA_PIN, GRB>(leds, NUMBER_OF_LEDS);

   // Initialize DHT device.
   dht.begin();
   // Print temperature sensor details.
   sensor_t sensor;
   dht.temperature().getSensor(&sensor);
   Serial.println(F("------------------------------------------"));
   Serial.println(F(">> Temperature Sensor"));
   Serial.print  (F("   >> Sensor Type: ")); Serial.println(sensor.name);
   Serial.print  (F("   >> Driver Ver:  ")); Serial.println(sensor.version);
   Serial.print  (F("   >> Unique ID:   ")); Serial.println(sensor.sensor_id);
   Serial.print  (F("   >> Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
   Serial.print  (F("   >> Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
   Serial.print  (F("   >> Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
   Serial.println(F("------------------------------------------"));
   // Print humidity sensor details.
   dht.humidity().getSensor(&sensor);
   Serial.println(F(">> Humidity Sensor"));
   Serial.print  (F("   >> Sensor Type: ")); Serial.println(sensor.name);
   Serial.print  (F("   >> Driver Ver:  ")); Serial.println(sensor.version);
   Serial.print  (F("   >> Unique ID:   ")); Serial.println(sensor.sensor_id);
   Serial.print  (F("   >> Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
   Serial.print  (F("   >> Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
   Serial.print  (F("   >> Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
   Serial.println(F("------------------------------------------"));

   update_LEDStrip();
}

void loop() 
{  
   if(TONE_REQ == true)
   {
      if(BEEP_BUTTON_STATE == true)
      {
         tone(BUZZER_PIN, 1000);
         delay(200);
         noTone(BUZZER_PIN);
      }
      TONE_REQ = false;
   }

   if(millis() > delayMS)
   {
      delayMS = millis() + 10000; // 10 sec 

      LIGHT = (((analogRead(LIGHT_SENSOR) - LIGHT_SENSOR_MIN) / (float)(LIGHT_SENSOR_MAX - LIGHT_SENSOR_MIN)) * 100 );
      
      if(LIGHT < 0) LIGHT = 0;
      if(LIGHT > 100) LIGHT = 100;
      
      Serial.print(">> Light: ");
      Serial.print(LIGHT);
      Serial.print("\n");

      timeClient.update();

      // Get temperature event and print its value.
      sensors_event_t event;
      dht.temperature().getEvent(&event);
      if (isnan(event.temperature)) 
      {
         Serial.println(F(">> Error reading temperature!"));
      }
      else 
      {
         TEMPERATURE_DATA = event.temperature;
         Serial.print(F(">> Temperature: "));
         Serial.print(event.temperature);
         Serial.println(F("°C"));
      }

      // Get humidity event and print its value.
      dht.humidity().getEvent(&event);
      if (isnan(event.relative_humidity)) 
      {
         Serial.println(F(">> Error reading humidity!"));
      }
      else 
      {
         HUMIDITY_DATA = event.relative_humidity;
         Serial.print(F(">> Humidity: "));
         Serial.print(event.relative_humidity);
         Serial.println(F("%"));
      }
   }

}
