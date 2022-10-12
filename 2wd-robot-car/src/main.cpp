#include <Arduino.h>

/* STRAP(s) for enable or disable functionalities. */
#define CFG_WHL_SPEED_SENSOR            0
#define CFG_DEBUG_SERIAL_COM            1
#define CFG_DST_STOP_CONFIRM_NEEDED     1

/* List of the used and unused Arduino UNO PINs. */
#define PIN_SERIAL_RX                   0
#define PIN_SERIAL_TX                   1
#define PIN_LEFT_HCSR04_TRIGGER         2
#define PIN_LEFT_HCSR04_ECHO            3
#define PIN_WHL_FR_FORWARD              4
#define PIN_WHL_FR_PWMSPEED             5
#define PIN_WHL_FL_PWMSPEED             6
#define PIN_WHL_FR_BACKWARD             7
#define PIN_WHL_FL_BACKWARD             8
#define PIN_WHL_FL_FORWARD              9
#define PIN_CENTER_HCSR04_TRIGGER       10
#define PIN_CENTER_HCSR04_ECHO          11
#define PIN_RIGHT_HCSR04_ECHO           12
#define PIN_CTRLMODE_LED                13
#define PIN_RIGHT_HCSR04_TRIGGER        A0
#define PIN_LED_STRIP                   A1
#define UNUSED_PIN_A2                   A2      /* UNUSED */
#define UNUSED_PIN_A3                   A3      /* UNUSED */
#define UNUSED_PIN_A4                   A4      /* UNUSED */
#define UNUSED_PIN_A5                   A5      /* UNUSED */

/* Timeout for SelfDrive: If an action takes more time than defined SELF-Drive will disabled and the car go to WiFi-Control. */
#define INFINITE_LOOP_TIMEOUT           5500 /* 5,5 sec */

/* Wheel related DEFINEs. */
#define WHL_FL                          0 
#define WHL_FR                          1
#define NUMBER_OF_WHLs                  2       /* 2WD */
#define LEFT                            0
#define RIGHT                           1
#define STOP                            15

/* Wheel based control macros. */
#define WHL_FL_FORWARD_START            digitalWrite(PIN_WHL_FL_FORWARD, HIGH)
#define WHL_FL_FORWARD_STOP             digitalWrite(PIN_WHL_FL_FORWARD, LOW)
#define WHL_FR_FORWARD_START            digitalWrite(PIN_WHL_FR_FORWARD, HIGH)
#define WHL_FR_FORWARD_STOP             digitalWrite(PIN_WHL_FR_FORWARD, LOW)
#define WHL_FL_BACKWARD_START           digitalWrite(PIN_WHL_FL_BACKWARD, HIGH)
#define WHL_FL_BACKWARD_STOP            digitalWrite(PIN_WHL_FL_BACKWARD, LOW)
#define WHL_FR_BACKWARD_START           digitalWrite(PIN_WHL_FR_BACKWARD, HIGH)
#define WHL_FR_BACKWARD_STOP            digitalWrite(PIN_WHL_FR_BACKWARD, LOW)

/* Direction based control macros. */
#define STOP_WHLs                       {WHL_FL_FORWARD_STOP; WHL_FL_BACKWARD_STOP; WHL_FR_BACKWARD_STOP; WHL_FR_FORWARD_STOP;}
#define GO_FORWARD                      {WHL_FR_FORWARD_START;WHL_FL_FORWARD_START;}
#define GO_BACKWARD                     {WHL_FR_BACKWARD_START;WHL_FL_BACKWARD_START;}
#define GO_RIGHT                        {WHL_FL_FORWARD_START;}
#define GO_LEFT                         {WHL_FR_FORWARD_START;}
#define GO_RIGHT_REVERSE                {WHL_FL_BACKWARD_START;}
#define GO_LEFT_REVERSE                 {WHL_FR_BACKWARD_START;}

/* Wheel-speed sensor related defines. */
#define WHEEL_TEETH_NUMBER              20
#define WHEEL_CIRCUMFERENCE             215     // (mm)
#define WHEEL_TICK_DIAMETER             10.75   // (mm)

/* Start / Stop limits for distance sensor. */
#define STOP_VALUE_COUNTER              2    
#define STOP_DISTANCE_CENTER            25      // (cm)
#define START_DISTANCE_CENTER           35      // (cm)
#define STOP_DISTANCE_SIDE              10      // (cm)
#define START_DISTANCE_SIDE             10      // (cm)

/* Distance sensor read macros. */
#define DST_CENTER                      Get_Distance(PIN_CENTER_HCSR04_TRIGGER, PIN_CENTER_HCSR04_ECHO)
#define DST_RIGHT                       Get_Distance(PIN_RIGHT_HCSR04_TRIGGER, PIN_RIGHT_HCSR04_ECHO)
#define DST_LEFT                        Get_Distance(PIN_LEFT_HCSR04_TRIGGER, PIN_LEFT_HCSR04_ECHO)

/* Command for serial communication. */
#define WIFI_STOP_WHLs                  0x53    // ASCII: S
#define WIFI_FORWARD                    0x46    // ASCII: F
#define WIFI_BACKWARD                   0x42    // ASCII: B
#define WIFI_RIGHT                      0x52    // ASCII: R
#define WIFI_LEFT                       0x4c    // ASCII: L
#define WIFI_LED                        0x45    // ASCII: E
#define WIFI_CTRLMODE                   0x43    // ASCII: C

/* Macros for controlling the LED panel. */                   
#define LED_SWITCH                      {LED_state = !LED_state; digitalWrite(PIN_LED_STRIP,LED_state);};

/* ENUM for possible control modes. */
enum control_mode_t 
{
  WiFi_ControlMode,
  Self_ControlMode
};

/* Changes the control mode between WiFi_ControlMode and Self_ControlMode. */
#define CHANGE_CTRLMODE                 {control_mode = (control_mode == WiFi_ControlMode) ? Self_ControlMode : WiFi_ControlMode; digitalWrite(PIN_CTRLMODE_LED, CTRL_LED_STATE);}
#define CTRL_LED_STATE                  (control_mode == WiFi_ControlMode) ? HIGH : LOW


/* GLOBAL variables */
#if(CFG_WHL_SPEED_SENSOR)
volatile unsigned long int wheel_tick_counts[NUMBER_OF_WHLs] = {0,0}; /* Volatile type needed when a variable modified from interrupts. */
#endif 
bool LED_state                        = LOW;
control_mode_t control_mode           = WiFi_ControlMode;             // Default ControlMode is WiFi.
unsigned long int infinite_loop_timer = 0;                            // Used during SelfDrive to detect infinite loop - when the car is blocked by objects.


/* Returns the reported distance by the selected distance sensor. */
int Get_Distance(int TRG, int ECHO)
{
  digitalWrite(TRG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG, LOW);

  #if(CFG_DST_STOP_CONFIRM_NEEDED)
  int dst = (pulseIn(ECHO, HIGH) * 0.034 / 2);
  if((dst < STOP_DISTANCE_CENTER) && (TRG == PIN_CENTER_HCSR04_TRIGGER))
  {
    digitalWrite(TRG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRG, LOW);

    return (int)(pulseIn(ECHO, HIGH) * 0.034 / 2);
  }
  else
  {
    return dst;
  }
  #else
  return (int)(pulseIn(ECHO, HIGH) * 0.034 / 2);
  #endif
}


int LEFT_RIGHT_CHECK(void)
{  
   int t_left = DST_LEFT;
   int t_right = DST_RIGHT;
   if( t_left < STOP_DISTANCE_CENTER && t_right < STOP_DISTANCE_CENTER) return STOP;
   return (DST_LEFT > DST_RIGHT) ? LEFT : RIGHT;
}

/* COUNT_WHLTICK_xx functions  used to count the reported ticks from the wheel-speed sensor with the help of the interrupts. */
#if(CFG_WHL_SPEED_SENSOR)
void COUNT_WHLTICK_FL(void)
{
    wheel_tick_counts[WHL_FL]++;
}
void COUNT_WHLTICK_FR(void)
{
    wheel_tick_counts[WHL_FR]++;
}
#endif


/* Function called when the car is trying to do the same action more than the defined INFINITE_LOOP_TIMEOUT
 * The function will change the Control_mode from SELF to WiFI.  */
void infinite_LoopError_Callback()
{
  CHANGE_CTRLMODE;
  #if(CFG_DEBUG_SERIAL_COM)
  Serial.println("UNO >> Infinite loop error!");
  #endif
}


void setup() 
{
  /* Initialize interrupts for wheel speed sensor. */
  #if(CFG_WHL_SPEED_SENSOR)
  attachInterrupt(digitalPinToInterrupt(PIN_WHEEL_SPEED_SENSOR_FL),COUNT_WHLTICK_FL,RISING);   // Attach interrupts to PIN2 and PIN3 (these are the only compatible PINs on UNO).
  attachInterrupt(digitalPinToInterrupt(PIN_WHEEL_SPEED_SENSOR_FR),COUNT_WHLTICK_FR,RISING);
  #endif

  /* Initialize HC-SR04 Ultrasonic Sensor PINs. */
  pinMode(PIN_LEFT_HCSR04_TRIGGER, OUTPUT);
  pinMode(PIN_CENTER_HCSR04_TRIGGER, OUTPUT);
  pinMode(PIN_RIGHT_HCSR04_TRIGGER, OUTPUT);
  pinMode(PIN_LEFT_HCSR04_ECHO, INPUT);
  pinMode(PIN_CENTER_HCSR04_ECHO, INPUT);
  pinMode(PIN_RIGHT_HCSR04_ECHO, INPUT);

  /* Initialize motor driver board pins. */
  /* Direction */
  pinMode(PIN_WHL_FL_FORWARD, OUTPUT);
  pinMode(PIN_WHL_FL_BACKWARD, OUTPUT);
  pinMode(PIN_WHL_FR_FORWARD, OUTPUT);
  pinMode(PIN_WHL_FR_BACKWARD, OUTPUT);

  digitalWrite(PIN_WHL_FL_FORWARD, LOW);
  digitalWrite(PIN_WHL_FR_FORWARD, LOW);
  digitalWrite(PIN_WHL_FL_BACKWARD, LOW);
  digitalWrite(PIN_WHL_FR_BACKWARD, LOW);

  /* Motor-Speed */
  pinMode(PIN_WHL_FL_PWMSPEED, OUTPUT);
  pinMode(PIN_WHL_FR_PWMSPEED, OUTPUT);

  analogWrite(PIN_WHL_FL_PWMSPEED, 95);
  analogWrite(PIN_WHL_FR_PWMSPEED, 100);

  /* LED(s) */
  pinMode(PIN_LED_STRIP, OUTPUT);
  digitalWrite(PIN_LED_STRIP, LED_state);
  pinMode(PIN_CTRLMODE_LED, OUTPUT);
  digitalWrite(PIN_CTRLMODE_LED, CTRL_LED_STATE);

  /* Open Serial port on 115200 baudrate. */
  Serial.begin(115200);
  while(!Serial){}
}


/* This function taking care of the control of the car during WiFi_ControlMode. */
void wifi_ctrl_loop()
{
  STOP_WHLs;                                        // Stopping the car when WiFi_ControlMode enabled until further user interaction.
  #if(CFG_DEBUG_SERIAL_COM)
  Serial.println("UNO >> WiFi mode activated!");
  #endif
  while(control_mode == WiFi_ControlMode)           // Looping while the controlMode is WiFi. -> Can be changed only via a WiFi command from the driver. See below.
  {
    if(Serial.available() > 0)                      // Checking for newly received serial inputs.
    {                  
      switch (Serial.read())                        // Reads-out the received information and choose the correct action.
      {
      case WIFI_FORWARD:
        STOP_WHLs;
        GO_FORWARD;
        break;
      case WIFI_LEFT:
        STOP_WHLs;
        GO_LEFT;
        break;
      case WIFI_RIGHT:
        STOP_WHLs;
        GO_RIGHT;
        break;
      case WIFI_BACKWARD:
        STOP_WHLs;
        GO_BACKWARD;
        break;
      case WIFI_STOP_WHLs:
        STOP_WHLs;
        break;
      case WIFI_LED:
        LED_SWITCH;
        break;
      case WIFI_CTRLMODE:                         // CONTROL_MODE change command can break the loop.
        CHANGE_CTRLMODE;
        break;    
      default:
        /* Undefined data received */
        break;
      }
    }
  }
}


/* This function taking care of the control of the car during Self_ControlMode. */
void self_ctrl_loop()
{
  #if(CFG_DEBUG_SERIAL_COM)
  Serial.println("UNO >> Self-driving mode activated!");
  #endif
  while(control_mode == Self_ControlMode)                             // looping while control_mode is set the SELF.                          
  {
    if((Serial.available() > 0) && (Serial.read() == WIFI_CTRLMODE))  // Check the Serial COM for incoming WIFI_CTRLMODE command. 
    {
      STOP_WHLs;
      CHANGE_CTRLMODE;                                                // If WIFI_CTRLMODE command received change the control_mode and brake the loop.
      break;
    }
    
    if((DST_CENTER > STOP_DISTANCE_CENTER) /*&& (DST_LEFT > STOP_DISTANCE_SIDE) && (DST_RIGHT > STOP_DISTANCE_SIDE)*/ ) // If there is no close object go forward
    {
      #if(CFG_DEBUG_SERIAL_COM)
      Serial.println("UNO >> Go Forward");
      #endif
      GO_FORWARD;
    }
    else                                                                                                          // If any close object detected...
    {
      STOP_WHLs;
      int dir = LEFT_RIGHT_CHECK();
      switch(LEFT_RIGHT_CHECK())
      {
      case LEFT: 
         GO_LEFT;
         break;
      case RIGHT:
         GO_RIGHT;
         break;
      case STOP:
         CHANGE_CTRLMODE;
         break;
      }
      delay(100);
      STOP_WHLs
    }
  }
}


void loop()
{
  /* Software starts with WiFi ControlMode by default. - Driver can it change via WiFi commands. */
  if(control_mode == WiFi_ControlMode) wifi_ctrl_loop();
  if(control_mode == Self_ControlMode) self_ctrl_loop();

  /*Serial.print(DST_CENTER);
  Serial.print(", ");
  Serial.print(DST_LEFT);
  Serial.print(", ");
  Serial.println(DST_RIGHT);*/
}