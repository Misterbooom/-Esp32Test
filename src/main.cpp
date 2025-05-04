#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  Serial.begin(115200);
  tft.init(); 

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK); // Clear the screen
}

void loop()
{
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(20, 20);
  tft.println("Hello, ESP32!");

  tft.drawRect(10, 50, 100, 50, TFT_GREEN);
  tft.fillCircle(160, 80, 20, TFT_BLUE);

  delay(5000);
  tft.fillScreen(TFT_BLACK);
}
