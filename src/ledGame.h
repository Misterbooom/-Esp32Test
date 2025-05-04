#ifndef LEDGAME_H
#define LEDGAME_H

#include <Arduino.h>
#include <vector>
#define BUZZER_PIN 5

const int leds[] = {2, 4,21};
const int buttons[] = {18, 19,23};
const int ledsLength = sizeof(leds) / sizeof(leds[0]);
const int buttonsLength = sizeof(buttons) / sizeof(buttons[0]);

bool isGuessing = false;
int currentDelay = 700;

std::vector<int> generatedPattern;
std::vector<int> userPattern;

class LedGame
{
public:
    static void setup()
    {
        Serial.begin(9600);

        if (ledsLength != buttonsLength)
        {
            Serial.println("leds length != buttons length");
            while (true)
                ;
        }
        for (int i = 0; i < ledsLength; ++i)
        {
            pinMode(leds[i], OUTPUT);
            pinMode(buttons[i], INPUT_PULLUP);
        }
    }

    static std::vector<int> generateRandomPattern()
    {
        int len = random(4, 7);
        std::vector<int> res;
        res.reserve(len);
        for (int i = 0; i < len; ++i)
        {
            res.push_back(random(ledsLength));
        }
        return res;
    }

    static void loop()
    {
        if (!isGuessing)
        {
            generatedPattern = generateRandomPattern();
            showPattern(generatedPattern, currentDelay);
            currentDelay = max(100, currentDelay - 100);
            userPattern.clear();
            isGuessing = true;
        }

        int btn = whichButtonClicked();
        Serial.printf("butn : %d",btn); 
        if (btn != -1)
        {
            Serial.printf("Button clicked: %d\n",btn);
            digitalWrite(leds[btn], HIGH);
            delay(50);
            digitalWrite(leds[btn], LOW);
            userPattern.push_back(btn);
        }

        if (userPattern.size() == generatedPattern.size())
        {
            if (userPattern == generatedPattern)
            {
                showSuccessAnimation();
            }
            else
            {
                showFailedAnimation();
                currentDelay = 700;
            }
            isGuessing = false;
        }
    }

private:
    static void showPattern(const std::vector<int> &pattern, int d)
    {
        for (size_t i = 0; i < pattern.size(); ++i)
        {
            int idx = pattern[i];
            Serial.printf("pa: %d", idx);
            digitalWrite(leds[idx], HIGH);
            delay(d);
            digitalWrite(leds[idx], LOW);
            delay(100);
        }
        Serial.println("");
    }

    static void showFailedAnimation()
    {
        for (int i = 0; i < ledsLength; ++i)
            digitalWrite(leds[i], LOW);
        delay(100);

        for (int i = 0; i < ledsLength; ++i)
            digitalWrite(leds[i], HIGH);

        playFailedTone(); 
        delay(1000);

        noTone(BUZZER_PIN);

        for (int i = 0; i < ledsLength; ++i)
            digitalWrite(leds[i], LOW);
        delay(700);
    }

    static void showSuccessAnimation()
    {
        for (int i = 0; i < ledsLength * 10; ++i)
        {
            int ledIndex = i % ledsLength;
            digitalWrite(leds[ledIndex], HIGH);
            playSuccessTone(i);
            delay(100);
            digitalWrite(leds[ledIndex], LOW);
            delay(100);
        }
        noTone(BUZZER_PIN);
    }

    static int whichButtonClicked()
    {
        static bool prevStates[buttonsLength] = {HIGH, HIGH};

        for (int i = 0; i < buttonsLength; ++i)
        {
            bool currentState = digitalRead(buttons[i]);

            if (prevStates[i] != LOW && currentState == LOW)
            {
                prevStates[i] = currentState;
                return i;
            }
            prevStates[i] = currentState;
        }
        return -1;
    }
    static void playSuccessTone(int step)
    {
        int notes[] = {523, 659, 784}; 
        tone(BUZZER_PIN, notes[step % 3], 100);
    }
    static void playFailedTone()
    {
        tone(BUZZER_PIN, 200, 1000);
    }
};

#endif