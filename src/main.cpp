#include <ArduinoSTL.h>
#include <Keypad.h>

#include "header.h"
#include "pin.h"
#include "digit.h"

// Create global objects
byte rowPins[4] = {rowPin1, rowPin2, rowPin3, rowPin4};
byte colPins[4] = {colPin1, colPin2, colPin3, colPin4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Digit digits[] = {
    Digit(0, 0, digitPin1, 1),
    Digit(1, 0, digitPin2, 1),
    Digit(2, 0, digitPin3, 1),
    Digit(3, 0, digitPin4, 1)};

void setup()
{
  // Configuring output pins for the 74HC595
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  Serial.begin(9600);

  // Choose solution
  Digit::InitSolution();
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
      Digit::ClearAllDigits();
      break;
    case '#':
      Digit::SubmitAnswer();
      break;
    default:
      Digit *selectedDigit = Digit::GetSelectedDigit();
      selectedDigit->SetValue(key - '0');
      selectedDigit->SetSelectedDigitToNext();
      break;
    }
  }
  Digit::Update();
}

void CheckResult()
{
  std::cout << "Input number: " << digits[0].GetValue() << digits[1].GetValue() << digits[2].GetValue() << digits[3].GetValue() << std::endl;
}

void ClearNumber()
{
  // for (int digit = 0; digit < nbrDigits; digit++)
  // {
  //   lastNumber[digit] = EMPTY_DIGIT;
  // }
  // currentDigit = 0;
}