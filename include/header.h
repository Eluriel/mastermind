#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <ArduinoSTL.h>

void CheckResult();
void ClearNumber();

// Keypad settings

const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

#endif