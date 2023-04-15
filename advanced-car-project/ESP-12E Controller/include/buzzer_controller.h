/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Control functions of the buzzer.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef BUZZER_CONTROLLER_H
  #define BUZZER_CONTROLLER_H

   /**
    * Cyclic main task for controlling the buzzer.
    */
   extern void buzzer_main();

   /**
    * Initilaze all the resources used for the buzzer.
    */
   extern void initialize_buzzer();

   /**
    * Requesting a beep sound from the buzzer
    * 
    * @param hertz the frequency of the requested beep sound. Predefined frequentzies can be found in the config file. (unit: kHz)
    */
   extern void request_beep( int hertz );

   /**
    * Cyclic task called by the buzzer timer, which intended to disable the beep sound after the defined BEEP_TIME (50ms by default).
    */
   extern void buzzer_timer_Callback();

#endif /* BUZZER_CONTROLLER_H */