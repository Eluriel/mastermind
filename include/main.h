#ifndef MY_MAIN_H
#define MY_MAIN_H

#include <ArduinoSTL.h>

void ClearData();
void SendAnswer();
void WriteKey(char key);

// Keypad settings

const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

#endif