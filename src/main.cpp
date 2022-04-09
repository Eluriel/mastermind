#include <ArduinoSTL.h>
#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#include "digit.h"
#include "main.h"
#include "pin.h"

// Create global objects
byte rowPins[4] = {rowPin1, rowPin2, rowPin3, rowPin4};
byte colPins[4] = {colPin1, colPin2, colPin3, colPin4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Adafruit_NeoPixel pixels(4, LED_PIN, NEO_GRB + NEO_KHZ800);

Digit digits[] = {
    Digit(0, 0, digitPin1),
    Digit(1, 0, digitPin2),
    Digit(2, 0, digitPin3),
    Digit(3, 0, digitPin4)};

void setup()
{
  // Configuring output pins for the 74HC595
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  Serial.begin(9600);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();  // Send the updated pixel colors to the hardware.

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
      if (selectedDigit == NULL)
      {
        // No digit selected. Select first digit, clear and set value
        Digit::SetSelectedDigitToFirst();
        Digit::ClearAllDigits();
        selectedDigit = Digit::GetSelectedDigit();
      }
      selectedDigit->SetValue(key - '0');
      selectedDigit->SetSelectedDigitToNext();
      break;
    }
  }
  Digit::Update();
}
