#include "Digit.h"
#include "pin.h"

Digit *Digit::selectedDigit = NULL;
Digit *Digit::digits[] = {NULL, NULL, NULL, NULL};

Digit::Digit(int number, int value, int digitPin, int answerPin)
{
    this->number = number;
    this->value = value;
    this->digitPin = digitPin;
    this->answerPin = answerPin;
    this->isHalfCorrect = false;
    this->isFullCorrect = false;
    this->guess = -1;
    this->isSelected = (number == 0) ? true : false;
    this->answeredYet = false;
    this->answer = random(10);
    if (number == 0)
    {
        selectedDigit = this;
    }
    digits[number] = this;
    digits[number - 1]->nextDigit = this;
    this->previousDigit = digits[number - 1];

    if (number == 3)
    { // At last pass set next/previousDigit for first/last digits to close the circle of previous/next relations
        digits[0]->previousDigit = this;
        digits[3]->nextDigit = digits[0];
    }
    init();
}

void Digit::init()
{
    pinMode(digitPin, OUTPUT);
    pinMode(answerPin, OUTPUT);
    digitalWrite(digitPin, HIGH); // set digitpin off by default
}

void Digit::InitSolution()
{
    int solution[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++)
    {
        digits[i]->value = 0;
        digits[i]->answer = solution[i];
        digits[i]->ResetAnsweredStatus();
        digitalWrite(digits[i]->answerPin, LOW); // turn off led
        digits[i]->SetNumber();
        selectedDigit = digits[0];
    }
}

// Update everything related to the digits
void Digit::Update()
{
    for (int i = 0; i < 4; i++)
    {
        Digit *digit = digits[i];
        digit->SetNumber();
        digits[i]->SetAnswerLed();
    }
}

void Digit::ShowFinishLoop()
{
    int emptyIndex = 16;
    selectedDigit = NULL;
    long startTime = millis();
    while (millis() - startTime < 10000)
    {
        bool showEmpty = (millis() % 1000) < 500;
        for (int i = 0; i < 4; i++)
        {
            digits[i]->value = showEmpty ? emptyIndex : digits[i]->answer;
            digits[i]->SetNumber();
        }
    }
    Digit::InitSolution();
}

bool Digit::SubmitAnswer()
{
    Digit::ResetAnsweredStatus();
    Serial.println(String("number: value, answer, halfCorrect, fullCorrect"));
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        digits[i]->UpdateAnsweredStatus();
        if (digits[i]->isFullCorrect)
        {
            count++;
        }
        Serial.println(String(digits[i]->number) + String(": ") + String(digits[i]->value) + String(", ") + String(digits[i]->answer) + String(", ") + String(digits[i]->isHalfCorrect) + String(", ") + String(digits[i]->isFullCorrect));
    }
    return (count == 4);
}

void Digit::SetAnswerLed()
{
    int highLow = LOW;
    if (isFullCorrect)
    {
        if (this->answer == this->value)
        {
            highLow = HIGH;
        }
        else if (millis() % blinkCycle < 0.9 * blinkCycle)
        {
            highLow = HIGH;
        }
    }

    if (isHalfCorrect)
    {
        if (this->value == this->guess && millis() % blinkCycle > 0.5 * blinkCycle)
        {
            highLow = HIGH;
        }
        else if ((millis() % blinkCycle > 0.4 * blinkCycle) && (millis() % blinkCycle < 0.5 * blinkCycle))
        {
            highLow = HIGH;
        }
    }
    digitalWrite(answerPin, highLow);
}

void Digit::UpdateAnsweredStatus()
{
    this->guess = this->value;
    if (this->guess == this->answer)
    {
        this->isFullCorrect = true;
        this->answeredYet = true;
    }
    else
    {
        Digit *digit = unansweredDigitWithAnswer(this->value);
        if (digit != NULL)
        {
            this->isHalfCorrect = true;
            digit->answeredYet = true;
        }
    }
}

Digit *Digit::unansweredDigitWithAnswer(int answerSearched)
{
    Digit *digit = NULL;
    for (int i = 0; i < 4; i++)
    {
        Digit *digitToCheck = digits[i];
        if (!digitToCheck->answeredYet && digitToCheck->value != digitToCheck->answer && digitToCheck->answer == answerSearched)
        {
            digit = digits[i];
            break;
        }
    }
    return digit;
}

void Digit::ResetAnsweredStatus()
{
    for (int i = 0; i < 4; i++)
    {
        digits[i]->answeredYet = false;
        digits[i]->isHalfCorrect = false;
        digits[i]->isFullCorrect = false;
    }
}

void Digit::SetNumber()
{
    // Update the digit on the display
    SetDigitPin(HIGH);                                   // Set pins off so we don't show the number change, else numbers become garbled
    digitalWrite(latch, LOW);                            // Let the shiftregister know we are sending data
    shiftOut(data, clock, MSBFIRST, table[this->value]); // Shift out bits of <table[num]> to <data> pin, pulsing <clock> every time (setting HIGH, then LOW). Order is defined by MSBFIRST
    digitalWrite(latch, HIGH);                           // Let the shiftregister know we are done sending data
    if (selectedDigit != this || (millis() % blinkCycle > 0.5 * blinkCycle))
    {
        SetDigitPin(LOW); // set pin on to show
    }
    delay(lcdDelay);
    SetDigitPin(HIGH); // Turn pin off again
}

void Digit::SetDigitPin(int highLow)
{
    digitalWrite(digitPin, highLow);
}

// Generic getters/setters
Digit *Digit::GetSelectedDigit()
{
    return Digit::selectedDigit;
}
void Digit::SetSelectedDigitToNext()
{
    selectedDigit = selectedDigit->GetNextDigit();
}

void Digit::SetSelectedDigitToPrevious()
{
    selectedDigit = selectedDigit->GetPreviousDigit();
}
Digit *Digit::GetPreviousDigit()
{
    return this->previousDigit;
}
Digit *Digit::GetNextDigit()
{
    return this->nextDigit;
}
int Digit::GetValue()
{
    return this->value;
}
void Digit::SetValue(int newValue)
{
    this->value = newValue;
}
