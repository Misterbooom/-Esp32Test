#ifndef LEDBLINKINGDELAY_H
#define LEDBLINKINGDELAY_H
#include <Arduino.h>

#define SWITCH_DELAY 300
const int leds[] = {2, 4};
void activateLed(int pin)
{
    digitalWrite(pin, HIGH);
}
void disactivateLed(int pin)
{
    digitalWrite(pin, LOW);
}
class LedBlinkingDelay
{
public:
    static void setup()
    {
        for (int i = 0; i < sizeof(leds) / sizeof(int); i++)
        {
            pinMode(leds[i], OUTPUT);
        }
    }
    static void loop()
    {
        for (int i = 0; i < sizeof(leds) / sizeof(int); i++)
        {
            int led = leds[i];
            activateLed(led);
            delay(SWITCH_DELAY);
            disactivateLed(led);
        }
    }
};
#endif