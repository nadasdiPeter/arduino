#include "config_definition_uno.h"
#include "led_controller.h"
#include <FastLED.h>
#include "timer.h"
#include <Arduino.h>
#include "forward_collision_avoidance_assist.h"
#include "battery_voltage_monitor.h"
#include "state_resister.h"

#define WS2812B_Left   leds[WS2812B_LED_LEFT]
#define WS2812B_Middle leds[WS2812B_LED_MIDDLE]
#define WS2812B_Right  leds[WS2812B_LED_RIGHT]


boolean led_headlight_state = false;
Timer unconnected_cycle_timer;
int unconnected_led_animation_counter = 0;
CRGB leds[WS2812B_LEDSTRIP_LEDCOUNT];

void set_warning_lamp( int led, int requested_state)
{
   digitalWrite(led, requested_state);
}

void unconnected_update_handler()
{
   unconnected_led_animation_counter++;
   if(unconnected_led_animation_counter >= 12) unconnected_led_animation_counter = 0;
}

void play_unconnected_led_animation()
{
   switch(unconnected_led_animation_counter % 6)
   {
      case 0:
         digitalWrite(RED_WL, HIGH);
         digitalWrite(YELLOW_WL, LOW);
         digitalWrite(GREEN_WL, LOW);
         break;
      case 1:
         digitalWrite(RED_WL, HIGH);
         digitalWrite(YELLOW_WL, HIGH);
         digitalWrite(GREEN_WL, LOW);
         break;
      case 2:
         digitalWrite(RED_WL, HIGH);
         digitalWrite(YELLOW_WL, HIGH);
         digitalWrite(GREEN_WL, HIGH);
         break;
      case 3:
         digitalWrite(RED_WL, LOW);
         digitalWrite(YELLOW_WL, HIGH);
         digitalWrite(GREEN_WL, HIGH);
         break;
      case 4:
         digitalWrite(RED_WL, LOW);
         digitalWrite(YELLOW_WL, LOW);
         digitalWrite(GREEN_WL, HIGH);
         break;
      case 5:
         digitalWrite(RED_WL, LOW);
         digitalWrite(YELLOW_WL, LOW);
         digitalWrite(GREEN_WL, LOW);
         break;
      default:
         digitalWrite(RED_WL, HIGH);
         digitalWrite(YELLOW_WL, HIGH);
         digitalWrite(GREEN_WL, HIGH);
         break;
   }

   switch(unconnected_led_animation_counter )
   {
      case 0:
         WS2812B_Left   = CRGB::Red;
         WS2812B_Middle = CRGB::Black;  
         WS2812B_Right  = CRGB::Black;
         break;
      case 1:
         WS2812B_Left   = CRGB::Red;
         WS2812B_Middle = CRGB::Yellow;
         WS2812B_Right  = CRGB::Black;
         break;
      case 2:
         WS2812B_Left   = CRGB::Red;
         WS2812B_Middle = CRGB::Yellow;
         WS2812B_Right  = CRGB::Green;
         break;
      case 3:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Yellow; 
         WS2812B_Right  = CRGB::Green;
         break;
      case 4:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Black;  
         WS2812B_Right  = CRGB::Green;
         break;
      case 5:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Black;
         WS2812B_Right  = CRGB::Black;
         break;
      case 6:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Black;  
         WS2812B_Right  = CRGB::Red;
         break;
      case 7:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Yellow;
         WS2812B_Right  = CRGB::Red;
         break;
      case 8:
         WS2812B_Left   = CRGB::Green;
         WS2812B_Middle = CRGB::Yellow;
         WS2812B_Right  = CRGB::Red;
         break;
      case 9:
         WS2812B_Left   = CRGB::Green;
         WS2812B_Middle = CRGB::Yellow; 
         WS2812B_Right  = CRGB::Black;
         break;
      case 10:
         WS2812B_Left   = CRGB::Green;
         WS2812B_Middle = CRGB::Black;  
         WS2812B_Right  = CRGB::Black;
         break;
      case 11:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Black;
         WS2812B_Right  = CRGB::Black;
         break;
      default:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Middle = CRGB::Black; 
         WS2812B_Right  = CRGB::Black;
         break;
   }
}

void initialize_led_controller()
{
   /* Initialize the PIN(s) */
   pinMode(LED_HEADLIGHT, OUTPUT);
   pinMode(RED_WL, OUTPUT);
   pinMode(YELLOW_WL, OUTPUT);
   pinMode(GREEN_WL, OUTPUT);

   /*Initialize WS2812B ledstrip with FastLED library */
   FastLED.addLeds<WS2812B, WS2812B_LEDSTRIP_DATAPIN, GRB>(leds, WS2812B_LEDSTRIP_LEDCOUNT);   // for GRB LEDs on some strips green and red wire are swapped.
   //FastLED.addLeds<WS2812B, WS2812B_LEDSTRIP_DATAPIN, RGB>(leds, WS2812B_LEDSTRIP_LEDCOUNT); // for RGB LEDs
   WS2812B_Left   = CRGB::Black;
   WS2812B_Middle = CRGB::Black;
   WS2812B_Right  = CRGB::Black;
   FastLED.setBrightness(WS2812B_BRIGHTNESS_LOW);
   FastLED.show();

   /* set startup conditions */
   analogWrite(LED_HEADLIGHT, 0);
   digitalWrite(RED_WL, LOW);
   digitalWrite(YELLOW_WL, LOW);
   digitalWrite(GREEN_WL, LOW);

   /* initialize unconnected led animation timer */
   unconnected_cycle_timer.setInterval(UNCONNECTED_LED_ANIMATION_CYCLE);
   unconnected_cycle_timer.setCallback(unconnected_update_handler);
   unconnected_cycle_timer.start(); 
}

void toggle_led_headlight()
{
   led_headlight_state = !led_headlight_state;
   analogWrite(LED_HEADLIGHT, ((led_headlight_state == false) ? 0 : 255));
}

void led_main()
{
   /* executed all the time when the connection status CONNECTED */
   if( get_connection_status() == status_connected )
   {
      if(unconnected_cycle_timer.isRunning() == true) unconnected_cycle_timer.stop();
      
      /* YELLOW warning lamp
       * Turn on and off according the Battery Voltage Monitor
       * Off - If the voltage is in the normal range.
       * On  - If under or overvoltage detected. */
      set_warning_lamp(YELLOW_WL,(get_voltage_state() == normal_voltage) ? LOW : HIGH);

      /* GREEN warning lamp 
       * Turn on and off according the FCA state.
       * Off - If the FCA is disabled
       * On  - If the FCA is enabled */
      set_warning_lamp(GREEN_WL,(is_fca_active()) ? HIGH : LOW);

      /* RED warning lamp 
       * Turn on and off according the zone feedback of the FCA
       * Off - If the FCA disabled or if the FCA active but detecting SAFE zone.
       * On  - If the FCA active and detecting UNSAFE zone */
      if(is_fca_active())
         set_warning_lamp(RED_WL,(get_fca_zone() == unsafe_zone) ? HIGH : LOW);
      else 
         set_warning_lamp(RED_WL,LOW);

      /* WS2812B LEDstrip Backlight control */
      switch (get_vehicle_status())
      {
      case d_stop:
         WS2812B_Left   = CRGB::Red;
         WS2812B_Right  = CRGB::Red;
         WS2812B_Middle = CRGB::Black;
         break;
      case d_left:
         WS2812B_Left   = CRGB::Yellow;
         WS2812B_Right  = CRGB::Black;
         WS2812B_Middle = CRGB::Black;
         break;
      case d_right:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Right  = CRGB::Yellow;
         WS2812B_Middle = CRGB::Black;
         break;
      case d_forward:
         WS2812B_Left   = CRGB::Black;
         WS2812B_Right  = CRGB::Black;
         WS2812B_Middle = CRGB::Black;
         break;
      case d_backward:
         WS2812B_Left   = CRGB::Red;
         WS2812B_Right  = CRGB::Red;
         WS2812B_Middle = CRGB::White;
         break;      
      default:
         WS2812B_Left   = CRGB::Red;
         WS2812B_Right  = CRGB::Red;
         WS2812B_Middle = CRGB::Black;
         break;
      }
   }
   else
   {
      if(unconnected_cycle_timer.isRunning() == false) unconnected_cycle_timer.start();
      unconnected_cycle_timer.update();
      play_unconnected_led_animation();
   }
   FastLED.show();
}

