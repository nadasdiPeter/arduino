#include "config_definition_uno.h"
#include "led_control.h"
#include "timer.h"
#include <Arduino.h>
#include "forward_collision_avoidance_assist.h"

#define TURN_GREEN_WL_ON   digitalWrite(GREEN_WL, HIGH)
#define TURN_GREEN_WL_OFF  digitalWrite(GREEN_WL, LOW)
#define TURN_YELLOW_WL_ON  digitalWrite(YELLOW_WL, HIGH)
#define TURN_YELLOW_WL_OFF digitalWrite(YELLOW_WL, LOW)
#define TURN_RED_WL_ON     digitalWrite(RED_WL, HIGH)
#define TURN_RED_WL_OFF    digitalWrite(RED_WL, LOW)

boolean led_headlight_state = false;
connection_status_t last_connection_state = status_unconnected;
Timer unconnected_cycle_timer;
int unconnected_led_animation_counter = 0;

void Set_warning_lamp( int LED, int requested_state)
{
   digitalWrite(LED, requested_state);
}

void unconnected_update_handler()
{
   unconnected_led_animation_counter++;
   if(unconnected_led_animation_counter >= 6) unconnected_led_animation_counter = 0;
}

void play_unconnected_led_animation()
{
   switch(unconnected_led_animation_counter)
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
}

void initialize_led_controller()
{
   /* Initialize the PIN(s) */
   pinMode(LED_HEADLIGHT, OUTPUT);
   pinMode(RED_WL, OUTPUT);
   pinMode(YELLOW_WL, OUTPUT);
   pinMode(GREEN_WL, OUTPUT);

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

void led_main( connection_status_t connection)
{
   /* executed all the time when the connection status CONNECTED */
   if( connection == status_connected )
   {
      if(unconnected_cycle_timer.isRunning() == true) unconnected_cycle_timer.stop();
      
      /* yellow warning lamp */
      Set_warning_lamp(YELLOW_WL,LOW);

      /* green warning lamp */
      Set_warning_lamp(GREEN_WL,(is_fca_active()) ? HIGH : LOW);

      /* red warning lamp */
      if(is_fca_active())
         Set_warning_lamp(RED_WL,(Get_zone() == unsafe_zone) ? HIGH : LOW);
      else 
         Set_warning_lamp(RED_WL,LOW);
   }
   else
   {
      if(unconnected_cycle_timer.isRunning() == false) unconnected_cycle_timer.start();
      unconnected_cycle_timer.update();
      play_unconnected_led_animation();
   }
}

