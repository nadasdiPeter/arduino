/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Configuration file. 
 *                 Contains the PIN layout and all the parameters which can be modified.
 *                 It also contains structs, enums and class definitions used by the program.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef CONFIG_DEFINITION_UNO_H
  #define CONFIG_DEFINITION_UNO_H

  #include <Arduino.h>

  /* Arduino-UNO pin layout */
  #define PIN_0           0     /* unused */
  #define PIN_1           1     /* unused */
  #define PIN_2           2     /* unused */
  #define PIN_3           3     /* unused */
  #define RED_WL          4
  #define YELLOW_WL       5
  #define GREEN_WL        6
  #define PIN_7           7     /* unused */
  #define PIN_8           8     /* unused */
  #define HCSR04_TRIGGER  9 
  #define HCSR04_ECHO     10
  #define PIN_11          11    /* unused */
  #define PIN_12          12    /* unused */
  #define PIN_13          13    /* unused */
  #define PIN_ANALOG0     A0    /* unused */
  #define LED_HEADLIGHT   A1
  #define PIN_ANALOG2     A2    /* unused */
  #define PIN_ANALOG3     A3    /* unused */
  #define PIN_ANALOG4     A4    /* unused */
  #define PIN_ANALOG5     A5    /* unused */

  #define SERIAL_BAUD_RATE                  115200u   // serial communication speed (need to be the same on both side)
  #define SONAR_REFRESH_CYCLE               35u       // (ms) - minimum time between two update is 29ms !!!
  #define UNCONNECTED_LED_ANIMATION_CYCLE   200u      // Flashing rate of the warning lamps, when the device is unconnected
  #define MAX_DISTANCE                      100u      // Maximum distance to measure with HCSR04 sonar (in centimeters)
  #define INVALID_DISTANCE                  0u        // Measures distance outside the maximum range.
  #define EMERGENCY_STOP_DISTANCE           25u       // Minimum distance to measure with HCSR04 sonar (in centimeters)
  #define DISPLAY_REFRESH_RATE              1000u     // Refresh cycle of the LCD display in ms.

  #define WIFI_HOST_NAME                    "myCAR"      // Name of the created Wifi network
  #define WIFI_PASSWORD                     "letmejoin"  // The password of the created Wifi network
  

  /* Commands / messages used for serial bus communication between the ESP-12E a Arduino-UNO */
  #define SERIAL_COM_COMMAND__stop                        (char)0x53    /* Asci code: S */
  #define SERIAL_COM_COMMAND__forward                     (char)0x46    /* Asci code: F */
  #define SERIAL_COM_COMMAND__backward                    (char)0x42    /* Asci code: B */
  #define SERIAL_COM_COMMAND__right                       (char)0x52    /* Asci code: R */
  #define SERIAL_COM_COMMAND__left                        (char)0x4c    /* Asci code: L */
  #define SERIAL_COM_COMMAND__led                         (char)0x30    /* Asci code: 0 */
  #define SERIAL_COM_COMMAND__lcd                         (char)0x31    /* Asci code: 1 */
  #define SERIAL_COM_COMMAND__disconnected                (char)0x32    /* Asci code: 2 */
  #define SERIAL_COM_COMMAND__connected                   (char)0x33    /* Asci code: 3 */
  #define SERIAL_COM_COMMAND__info                        (char)0x34    /* Asci code: 4 */
  #define SERIAL_COM_COMMAND__unsafe_distance             (char)0x75    /* Asci code: u */
  #define SERIAL_COM_COMMAND__safe_distance               (char)0x73    /* Asci code: s */
  #define SERIAL_COM_COMMAND__fca                         (char)0x66    /* Asci code: f */
  #define SERIAL_COM_COMMAND__test                        (char)0x54    /* Asci code: T */

  enum connection_status_t
  {
    status_unconnected = SERIAL_COM_COMMAND__disconnected,
    status_connected = SERIAL_COM_COMMAND__connected,
  };

  enum display_info_mode_t
  {
    ip_mode,
    clock_mode,
    distance_mode
  };

  enum zone_mode_t
  {
    safe_zone,
    unsafe_zone
  };

  enum msg_direction_t
  {
    rx,
    tx
  };

  struct serial_command_t
  {
    String cmd_name;
    int cmd_id;

    serial_command_t( String name, int id)
    {
      cmd_name = name;
      cmd_id = id;
    }
  };

  #if( SONAR_REFRESH_CYCLE < 29 )
  #error  SONAR_REFRESH_CYCLE can not be less than 29
  #endif
  
#endif /* CONFIG_DEFINITION_UNO_H */