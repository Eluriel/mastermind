#ifndef MY_DIGIT_H
#define MY_DIGIT_H

// Code taken and adapted from https://gitlab.com/Liquidje/arduino-code-breaker

#include <ArduinoSTL.h>

class Digit
{
private:
    int number;
    int value;
    int answer;
    int digitPin;
    int guess;
    bool isSelected;
    bool isHalfCorrect;
    bool isFullCorrect;
    bool answeredYet;

    Digit *nextDigit;
    Digit *previousDigit;

    static Digit *selectedDigit;
    static Digit *digits[];
    static void ResetAnsweredStatus();
    static Digit *unansweredDigitWithAnswer(int answerSearched);

    void init();
    void SetNumber();
    void SetDigitPin(int highLow);
    void UpdateAnsweredStatus();

public:
    static const int lcdDelay = 3;
    static const long blinkCycle = 750;

    static void InitSolution();
    static void Update();
    static void ClearAllDigits();
    static std::pair<int, int> SubmitAnswer(); // First is nb of full, second is nb of half
    static void ShowFinishLoop();

    Digit(int number, int value, int digitPin);

    // Getters/Setters
    static Digit *GetSelectedDigit();
    static void SetSelectedDigitToNext();
    static void SetSelectedDigitToFirst();
    Digit *GetPreviousDigit();
    void SetPreviousDigit(Digit *newPreviousDigit);
    Digit *GetNextDigit();
    void SetNextDigit(Digit *newNextDigit);
    int GetValue();
    void SetValue(int value);
};

const unsigned char table[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 0-15 are numbers 0-F
    0x00                                                                                            // 16 is blank
};
#endif