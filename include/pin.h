#include <ArduinoSTL.h>
// Arduino pin configuration

int latch = 7; // 74HC595  pin 9 STCP
int clock = 8; // 74HC595  pin 10 SHCP
int data = 6;  // 74HC595  pin 8 DS

const int digitPins[4] = {2, 3, 4, 5};

byte rowPins[4] = {A0, A1, A2, A3}; // connect to the row pinouts of the keypad
byte colPins[4] = {A4, A5, 12, 13}; // connect to the column pinouts of the keypad
