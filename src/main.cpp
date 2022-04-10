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

Adafruit_NeoPixel pixels(4, LED_PIN, NEO_RGB);

Digit digits[] = {
    Digit(0, 0, digitPin1),
    Digit(1, 0, digitPin2),
    Digit(2, 0, digitPin3),
    Digit(3, 0, digitPin4)};

bool finished = false;

void setup()
{
  // Configuring output pins for the 74HC595
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  // Set pin for lock
  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, LOW);

  Serial.begin(9600);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setBrightness(64);
  pixels.show(); // Send the updated pixel colors to the hardware.

  // Choose solution
  Digit::InitSolution();
  finished = false;
}

void loop()
{
  char key = keypad.getKey();

  // Disable keypad when game is finished
  if (key && !finished)
  {
    std::cout << "Last pressed key: " << key << std::endl;
    switch (key)
    {
    case '*':
      ClearData();
      break;
    case '#':
      SendAnswer();
      break;
    // Disable for A, B, C or D
    case 'A':
    case 'B':
    case 'C':
    case 'D':
      break;
    default:
      WriteKey(key);
      break;
    }
  }
  Digit::Update();
}

void ClearData()
{
  Digit::ClearAllDigits();
  pixels.clear();
  pixels.show();
}

void WriteKey(char key)
{
  Digit *selectedDigit = Digit::GetSelectedDigit();
  if (selectedDigit == NULL)
  {
    // No digit selected. Select first digit, clear and set value
    Digit::SetSelectedDigitToFirst();
    ClearData();
    selectedDigit = Digit::GetSelectedDigit();
  }
  selectedDigit->SetValue(key - '0');
  selectedDigit->SetSelectedDigitToNext();
}

void SendAnswer()
{
  // Prevent displaying answer if no all 4 values entered
  if (digits[3].GetValue() == 16)
  {
    return;
  }
  std::pair<int, int> reply = Digit::SubmitAnswer();
  int nbFull = reply.first;
  int nbHalf = reply.second;
  std::cout << "Results: " << nbFull << " full, " << nbHalf << " half." << std::endl;

  // Display results on LEDs
  pixels.clear();

  for (int i = 0; i < 4; i++)
  {
    if (i < nbFull)
    {
      pixels.setPixelColor(i, 0, 204, 0);
    }
    else if (i < (nbFull + nbHalf))
    {
      pixels.setPixelColor(i, 0, 0, 204);
    }
    else
    {
      pixels.setPixelColor(i, 204, 0, 0);
    }
  }
  pixels.show();

  // Won game!
  if (nbFull == 4)
  {
    finished = true;
    // Open lock
    digitalWrite(LOCK_PIN, HIGH);
    Digit::ShowFinishLoop();
  }
}