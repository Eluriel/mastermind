#ifndef MY_PIN_H
#define MY_PIN_H

#include <ArduinoSTL.h>
// Arduino pin configuration

const int latch = 7; // 74HC595  pin 9 STCP
const int clock = 8; // 74HC595  pin 10 SHCP
const int data = 6;  // 74HC595  pin 8 DS

// Output pins for commun cathod of each 7 segment digit
const int digitPin1 = 2;
const int digitPin2 = 3;
const int digitPin3 = 4;
const int digitPin4 = 5;

// Row pinout of keypad
const byte rowPin1 = A0;
const byte rowPin2 = A1;
const byte rowPin3 = A2;
const byte rowPin4 = A3;

// Column pinout of keypad
const byte colPin1 = A4;
const byte colPin2 = A5;
const byte colPin3 = 12;
const byte colPin4 = 13;

// Led configuration

#define LED_PIN 9
#define LOCK_PIN 10

#endif