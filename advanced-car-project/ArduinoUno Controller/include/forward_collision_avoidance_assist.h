/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Controller class of the forward collision avoidance assist (FCA) function.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef FORWARD_COLLISION_AVOIDANCE_H
   #define FORWARD_COLLISION_AVOIDANCE_H

   /**
    * Returns the state of the front-collision-avoidance-assist
    * 
    * @return Returns TRUE if FCA active otherwise FALSE.
    */
   extern boolean is_fca_active();

   /**
    * Disables the front-collision-avoidance-assist function
    */
   extern void disable_fca();

   /**
    * Enables the front-collision-avoidance-assist function
    */
   extern void enable_fca();

   /**
    * Cyclic main function of the front-collision-avoidance-assist function
    */
   extern void fca_main(connection_status_t connection_status);

   /**
    * Returns the distance based zone information wether moving forward is safe or not
    * 
    * @return Returns zone_mode_t:SAFE if the nearest object distance exceeds the EMERGENCY_STOP_DISTANCE otherwise returns zone_mode_t:UNSAFE
    */
   extern zone_mode_t get_fca_zone();

#endif /* FORWARD_COLLISION_AVOIDANCE_H */