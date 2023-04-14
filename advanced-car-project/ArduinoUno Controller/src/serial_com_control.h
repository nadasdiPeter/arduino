#include <Arduino.h>

extern void initialize_serial_com();
extern bool GetD_serial_message(byte * message);
extern void serial_write(char message);