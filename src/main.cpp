#include <ArduinoSTL.h>
#include <Keypad.h>
#include <map>

#include "header.h"
#include "pin.h"

// Global variables declaration
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char lastNumber[nbrDigits] = {EMPTY_DIGIT, '4', EMPTY_DIGIT, '2'};
int currentDigit = 0;


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

  // Choose solution
  
  currentDigit = 0;
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
    std::cout << "Last pressed key: " << key << std::endl;
    switch (key)
    {
    case '*':
      ClearNumber();
      break;
    case '#':
      CheckResult();
      break;
    default:
      lastNumber[currentDigit] = key;
      currentDigit++;
      if (currentDigit >= nbrDigits)
      {
        currentDigit = 0;
      }
      break;
    }
  }
  DisplayLastNumber();
  delay(1);
}

void CheckResult()
{
  std::cout << "Input number: " << lastNumber[0] << lastNumber[1] << lastNumber[2] << lastNumber[3] << std::endl;
}

void ClearNumber()
{
  for (int digit = 0; digit < nbrDigits; digit++)
  {
    lastNumber[digit] = EMPTY_DIGIT;
  }
  currentDigit = 0;
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