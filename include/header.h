#include <ArduinoSTL.h>

void ClearNumber();
void DisplayDigit(unsigned char num, int digit);
void DisplayLastNumber();

// Keypad settings

const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Screen display conversion settings

const int nbrDigits = 4; // Nb of 4 segment display
const char EMPTY_DIGIT = ' ';
std::map<char, unsigned char> conversionMap = {
    {'0', 0x3f},
    {'1', 0x06},
    {'2', 0x5b},
    {'3', 0x4f},
    {'4', 0x66},
    {'5', 0x6d},
    {'6', 0x7d},
    {'7', 0x07},
    {'8', 0x7f},
    {'9', 0x6f},
    {'A', 0x77},
    {'B', 0x7c},
    {'C', 0x39},
    {'D', 0x5e},
    {'E', 0x79},
    {'F', 0x71},
    {EMPTY_DIGIT, 0x00}};
