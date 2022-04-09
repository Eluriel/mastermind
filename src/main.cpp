#include <ArduinoSTL.h>
#include <Keypad.h>
#include <map>

#include "header.h"

int latch = 7; // 74HC595  pin 9 STCP
int clock = 8; // 74HC595  pin 10 SHCP
int data = 6;  // 74HC595  pin 8 DS

const int nbrDigits = 4; // Nb of 4 segment display
const int digitPins[nbrDigits] = {2, 3, 4, 5};

// Keypad config
const byte ROWS = 4; // four rows
const byte COLS = 4; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {A0, A1, A2, A3}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5, 12, 13}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Game settings

char lastNumber[nbrDigits] = {' ', '4', ' ', '2'};

void setup()
{
  // Configuring output pins for the 74HC595
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  // Configuring output pins for commun cathod of each 7 segment digit
  for (int i = 0; i < nbrDigits; i++)
  {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);
  }

  Serial.begin(9600);
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    Serial.println(key);
    lastNumber[0] = key;
  }
  DisplayLastNumber();
  delay(1);
}

// Function to display last number on screen
void DisplayLastNumber()
{
  for (int digit = 0; digit < nbrDigits; digit++)
  {
    if (lastNumber[digit] != ' ')
    {
      DisplayDigit(lastNumber[digit], digit);
    }
  }
}

// Function to display on one seven segments digit
void DisplayDigit(unsigned char num, int digit)
{
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, displayTable[conversionMap[num]]);
  digitalWrite(latch, HIGH);

  digitalWrite(digitPins[digit], LOW);
  delay(4);
  digitalWrite(digitPins[digit], HIGH);
}