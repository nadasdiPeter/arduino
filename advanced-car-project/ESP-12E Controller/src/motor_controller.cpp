#include <ESP8266WiFi.h>
#include "config_definition_esp.h"
#include "motor_controller.h"
#include "serial_controller.h"

boolean         forward_allowed       = true;
turning_mode_t  turning_mode          = turning_mode_fast;
direction_t     vehicle_motion_status = d_stop;

void change_turning_mode()
{
  turning_mode = (turning_mode == turning_mode_fast) ? turning_mode_slow : turning_mode_fast;
}

turning_mode_t get_turning_mode()
{
  return turning_mode;
}

void move(int direction)
{
  switch (direction)
  {
  case FORWARD:
    if(forward_allowed == true)
    {
      digitalWrite(MotorB_DIR, FORWARD_direction);
      digitalWrite(MotorA_DIR, FORWARD_direction);
      digitalWrite(MotorA_PWM, MOTOR_SPEED__MAXIMUM);
      digitalWrite(MotorB_PWM, MOTOR_SPEED__MAXIMUM);
      vehicle_motion_status = d_forward;
    }
    else
    {
      move(STOP);
      vehicle_motion_status = d_stop;
    }
    break;
  case LEFT:
    digitalWrite(MotorB_DIR, FORWARD_direction);
    digitalWrite(MotorB_PWM, MOTOR_SPEED__MAXIMUM);
    if(turning_mode == turning_mode_fast)
    {
      digitalWrite(MotorA_DIR, BACKWARD_direction);
      digitalWrite(MotorA_PWM, MOTOR_SPEED__MAXIMUM);
    }
    vehicle_motion_status = d_left;
    break;
  case RIGHT:
    digitalWrite(MotorA_DIR, FORWARD_direction);
    digitalWrite(MotorA_PWM, MOTOR_SPEED__MAXIMUM);
    if(turning_mode == turning_mode_fast)
    {
      digitalWrite(MotorB_DIR, BACKWARD_direction);
      digitalWrite(MotorB_PWM, MOTOR_SPEED__MAXIMUM);
    }
    vehicle_motion_status = d_right;
    break;
  case BACKWARD:
    digitalWrite(MotorA_DIR, BACKWARD_direction);
    digitalWrite(MotorB_DIR, BACKWARD_direction);
    digitalWrite(MotorA_PWM, MOTOR_SPEED__MAXIMUM);
    digitalWrite(MotorB_PWM, MOTOR_SPEED__MAXIMUM);
    vehicle_motion_status = d_backward;
    break;
  case STOP:
  default:
    vehicle_motion_status = d_stop;
    digitalWrite(MotorA_PWM, MOTOR_SPEED__STANDSTILL);
    digitalWrite(MotorB_PWM, MOTOR_SPEED__STANDSTILL);  
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
  // Change from unsafe to safe when the vehicle is moving.
  if(forward_allowed == true && vehicle_motion_status != d_stop)
  {
    move(STOP);
    forward_allowed = false;
    serial_write(SERIAL_COM_COMMAND__stop);
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