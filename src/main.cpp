#include <ArduinoSTL.h>
#include <Keypad.h>
#include <map>

#include "header.h"
#include "pin.h"

// Global variables declaration
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char lastNumber[nbrDigits] = {EMPTY_DIGIT, '4', EMPTY_DIGIT, '2'};

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
  shiftOut(data, clock, MSBFIRST, conversionMap[num]);
  digitalWrite(latch, HIGH);

  digitalWrite(digitPins[digit], LOW);
  delay(4);
  digitalWrite(digitPins[digit], HIGH);
}