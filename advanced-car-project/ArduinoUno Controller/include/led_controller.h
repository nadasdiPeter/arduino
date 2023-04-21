/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Controller class of the LEDs.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef LED_CONTROLLER_H
   #define LED_CONTROLLER_H

   /**
    * Initialize the LEDs
    */
   extern void initialize_led_controller();

   /**
    * Switches on or off the LED headlight depending on the actual state.
    */
   extern void toggle_led_headlight();

   /**
    * Cyclic main function of the led-controller which calculates the warning lamps states. (green/yellow/red lamps)
    */
   extern void led_main();

   /**
    * Sets the state of the given warning lamps (green/yellow/red lamps)
    * 
    * @param LED ID of the green/yellow/red lamp
    * @param requested_state HIGH or LOW (on or off)
    */
   extern void set_warning_lamp( int led, int requested_state);

   /**
    * Cyclic task to trigger the chnages of the unconnected led animation
    */
   extern void unconnected_update_handler();

   /**
    * Controls the warning lamps according the given animation cycle (defined by the unconnected_led_animation_counter).
    */
   extern void play_unconnected_led_animation();

#endif /* LED_CONTROLLER_H  */