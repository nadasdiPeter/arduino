/**
 *   Author:       Peter Horvath
 *   Email:        nadasdi.horvath.peter@gmail.com
 * 
 *   Description:  Configuration file. 
 *                 Contains the PIN layout and all the parameters which can be modified.
 *                 It also contains struct, enum and class definitions used by the program.
 * 
 *   (c) Copyright by Peter Horvath
 *
 **/

#ifndef CONFIG_DEFINITION_ESP_H
  #define CONFIG_DEFINITION_ESP_H

   /* Network credentials */
   #define SSID                            "myCAR"
   #define PASSWORD                        "letmejoin"
   #define PORT                            8080

   /* Keywords used in sourcecode for better understanding */
   #define FORWARD                         0
   #define LEFT                            1
   #define RIGHT                           2
   #define BACKWARD                        3
   #define STOP                            4
   #define LED                             5
   #define LCD                             7
   #define INFO                            8
   #define FCA                             10 /* Forward Collision-Avoidance Assist */
   #define TURNING_MODE                    11

   #define FORWARD_direction               LOW
   #define BACKWARD_direction              HIGH

   #define MotorA_PWM                      D1
   #define MotorB_PWM                      D2
   #define MotorA_DIR                      D3
   #define MotorB_DIR                      D4
   #define BUZZER                          D5

   #define MOTOR_SPEED__MAXIMUM            255u
   #define MOTOR_SPEED__STANDSTILL         0u
   #define SERIAL_BAUD_RATE                115200u
   #define SERIAL_COM_CYCLE                100u

   #define BEEP_TIME                       50u   // (ms)
   #define BEEP_500kHz                     500u  // (kHz)
   #define BEEP_650kHz                     650u  // (kHz)
   #define BEEP_800kHz                     800u  // (kHz)
   #define BEEP_1000kHz                    1000u // (kHz)
   #define BEEP_1500kHz                    1500u // (kHz)

   /* Commands / messages used for serial communication between the ESP-12E a Arduino-UNO */
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
   #define SERIAL_COM_COMMAND__turning_mode                (char)0x54    /* Asci code: T */
   #define SERIAL_COM_COMMAND__test                        (char)0x74    /* Asci code: t */


  enum turning_mode_t
  {
    turning_mode_slow,
    turning_mode_fast
  };

  enum direction_t
  {
    d_forward,
    d_backward,
    d_left,
    d_right,
    d_stop
  };
  
#endif /* CONFIG_DEFINITION_ESP_H */