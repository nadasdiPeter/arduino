/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Controller class of the HCSR-04 ultrasonic distance sensor.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef SONAR_CONTROL_H
   #define SONAR_CONTROL_H

   /**
    * Cyclic main function of the sonar-controller which calculates the distance based on the HCSR04 sensor data.
    */
   extern void sonar_main();
   
   /**
    * Initialization of the the Sonar controller.
    */
   extern void initialize_sonar();
   
   /**
    * Cyclic function to calculate the distance based on the HCSR04 sensor data.
    */
   extern void cyclic_distance_update_handler() ;

   /**
    * Provides the latest and greatast distance information in centimeter measured by the HCSR04 sensor 
    * 
    * @returns Returns the latest and greatest measured distance information in centimeter.
    */
   extern unsigned int get_last_measured_distance();

#endif /* SONAR_CONTROL_H */