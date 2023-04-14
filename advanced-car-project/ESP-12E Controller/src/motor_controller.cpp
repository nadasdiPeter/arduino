#include <ESP8266WiFi.h>
#include "config_definition_esp.h"

boolean forward_allowed = true;

void move(int direction)
{
  switch (direction)
  {
  case FORWARD:
    if(forward_allowed == true)
    {
      digitalWrite(MotorB_DIR, FORWARD_direction);
      digitalWrite(MotorA_DIR, FORWARD_direction);
      digitalWrite(MotorA_PWM, motor_speed_maximum);
      digitalWrite(MotorB_PWM, motor_speed_maximum); 
    }
    else
    {
      move(STOP);
    }
    break;
  case LEFT:
    digitalWrite(MotorB_DIR, FORWARD_direction);
    digitalWrite(MotorB_PWM, motor_speed_maximum);
    break;
  case RIGHT:
    digitalWrite(MotorA_DIR, FORWARD_direction);
    digitalWrite(MotorA_PWM, motor_speed_maximum);
    break;
  case BACKWARD:
    digitalWrite(MotorA_DIR, BACKWARD_direction);
    digitalWrite(MotorB_DIR, BACKWARD_direction);
    digitalWrite(MotorA_PWM, motor_speed_maximum);
    digitalWrite(MotorB_PWM, motor_speed_maximum);
    break;
  case STOP:
  default:
    digitalWrite(MotorA_PWM, motor_speed_standstill);
    digitalWrite(MotorB_PWM, motor_speed_standstill);  
    break;
  }
}

void initilazize_motor_controller()
{
   /* Initialize the used motor driver PINs */
   pinMode(MotorA_PWM, OUTPUT); 
   pinMode(MotorB_PWM, OUTPUT);
   pinMode(MotorA_DIR, OUTPUT);
   pinMode(MotorB_DIR, OUTPUT);
   
   /* initialize motors with state: stop. */
   move(STOP);
}

void move_foward_unsafe()
{
  if(forward_allowed == true) 
  {
    move(STOP);
    forward_allowed = false;
  }
}

void move_foward_safe()
{
  forward_allowed = true;
}

boolean is_forward_allowed()
{
  return forward_allowed;
}