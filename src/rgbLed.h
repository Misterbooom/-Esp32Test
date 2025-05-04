#ifndef RGBLED_H
#define RGBLED_H

#include <Arduino.h>

#define RED_PIN 2
#define GREEN_PIN 4
#define BLUE_PIN 5


class RgbLed
{
public:
    static void setup()
    {
        ledcAttachPin(RED_PIN, 0);
        ledcAttachPin(GREEN_PIN, 1);
        ledcAttachPin(BLUE_PIN, 2);

        ledcSetup(0, 5000, 8);
        ledcSetup(1, 5000, 8);
        ledcSetup(2, 5000, 8);
    }

    static void loop()
    {
        fade(0, 255, 0, 0, 0, 255);
        fade(0, 0, 255, 0, 255, 0);
        fade(0, 0, 0, 255, 0, 0);
    }

private:
    static void fade(int r1, int g1, int b1, int r2, int g2, int b2)
    {
        for (int i = 0; i <= 255; i++)
        {
            int r = map(i, 0, 255, r1, r2);
            int g = map(i, 0, 255, g1, g2);
            int b = map(i, 0, 255, b1, b2);
            setColor(r, g, b);
            delay(5);
        }
    }

    static void setColor(int r, int g, int b)
    {
        ledcWrite(0, r);
        ledcWrite(1, g);
        ledcWrite(2, b);
    }
};
#endif
