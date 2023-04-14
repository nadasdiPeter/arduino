#include <Arduino.h>

extern void initialize_serial_controller();
extern bool GetD_serial_message(byte * message);
extern void serial_com_timer_Callback();
extern void serial_controller_main();
extern void serial_write(char c);