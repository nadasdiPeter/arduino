/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  The main control functions of the motor controller.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef MOTOR_CONTROLLER_H
  #define MOTOR_CONTROLLER_H

   /**
    * Controls the motors  to reach the desired state. 
    * 
    * @param direction The requested direction how the car should move. ( FORWARD / BACKWARD / LEFT / RIGHT / STOP )
    */
   extern void move(int direction);

   /**
    * Initialize all the resources used to control the motors.
    */
   extern void initilazize_motor_controller();

   /**
    * Enables the option to go FORWARD until further notice (Called when no near object(s) detected ahed the vehicle by the SONAR or the FCA disabled.)
    */
   extern void move_foward_safe();

   /**
    * Disable the option to go FORWARD until further notice (Only called when near object(s) detected ahed the vehicle by the SONAR.)
    */
   extern void move_foward_unsafe();

   /**
    * Provides the information if going forward is allowed by the FCA controller. (No near object(s) ahed the vehicle.)
    * 
    * @return Returns TRUE if going forward is SAFE othirwise FALSE.
    */
   extern boolean is_forward_allowed();

   /**
    * Toggles between the two defined turning mode of the motor driver.
    * If the previous mode was turning_fast than it sets the actual mode to slow, or vica-versa.
    * 
    * The two mode: fast and slow.
    */
   extern void change_turning_mode();

   /**
    * Gets the active turning mode. (Fast or slow)
    * 
    * @returns turning_mode_t (Fast or slow)
    */
   extern turning_mode_t get_turning_mode();

#endif /* MOTOR_CONTROLLER_H */