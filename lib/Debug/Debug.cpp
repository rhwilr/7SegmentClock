#include <Arduino.h>

#include "DisplayDriver.h"
#include "RTC.h"

void debugTime(DateTime now) {
  char buff[20];
  sprintf(buff, "%02d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  Serial.println(buff);
}

void debugTemp(float temp) {
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C");
}

void allSegmentsOn() {
  fillPixel(0, 0, 5, 23, 0xff);
  refreshDisplays();
}

void blinkDot() {
  clear();
  refreshDisplays();
  delay(100);
  
  fillPixel(0, 0, 5, 23, 0b10000000);
  refreshDisplays();
  delay(100);

  clear();
  refreshDisplays();
  delay(100);
  
  fillPixel(0, 0, 5, 23, 0b10000000);
  refreshDisplays();
  delay(100);

  clear();
  refreshDisplays();
  delay(100);
  
  fillPixel(0, 0, 5, 23, 0b10000000);
  refreshDisplays();
  delay(100);
}

void drawEight() {
  fillPixel(0, 0, 5, 23, 0b00000001);
  refreshDisplays();
  delay(100);

  fillPixel(0, 0, 5, 23, 0b00000100);
  refreshDisplays();
  delay(100);

  fillPixel(0, 0, 5, 23, 0b00001000);
  refreshDisplays();
  delay(100);
  
  fillPixel(0, 0, 5, 23, 0b00010000);
  refreshDisplays();
  delay(100);

  fillPixel(0, 0, 5, 23, 0b00000001);
  refreshDisplays();
  delay(100);
  
  fillPixel(0, 0, 5, 23, 0b00000010);
  refreshDisplays();
  delay(100);

  fillPixel(0, 0, 5, 23, 0b01000000);
  refreshDisplays();
  delay(100);
  
  fillPixel(0, 0, 5, 23, 0b00100000);
  refreshDisplays();
  delay(100);
}
