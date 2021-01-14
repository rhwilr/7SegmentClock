#include <Arduino.h>
#include "RTClib.h"

#include "conf.h"

#include "Debug.h"
#include "DHTSensor.h"
#include "DisplayDriver.h"
#include "RTC.h"
#include "Wifi.h"

int cacheTime = 0;

int getCacheTime(DateTime now);
void displayTemperature();
void displayTime();

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Start");
  
  initWifi();
  setupWifi();
  setupNTP();

  initDisplayDriver();
  initRTC();
  syncRTC();

  initDHT();

  allSegmentsOn();
  refreshDisplays();
  delay(1000);
}

void loop() {
  clear();

  for(int i = 0; i < 20; ++i) {
    displayTime();
  }
  
  clear();
  displayTemperature();
}

void displayTime() {
  DateTime now = getLocalTime();
  debugTime(now);

  if (getCacheTime(now) != cacheTime) {
    cacheTime = getCacheTime(now);
    clear();
  }
  
  digits(0,  (now.hour()/10)%10);
  digits(5,  now.hour()%10);
  digits(13,  (now.minute()/10)%10);
  digits(18,  now.minute()%10);
  putPixel(1, 12, 0b00011101);
  putPixel(4, 11, 0b00011101);
  
  refreshDisplays();
  delay(800);
  
  putPixel(1, 12, 0b00000000);
  putPixel(4, 11, 0b00000000);
  
  refreshDisplays();
  delay(800);
}

void displayTemperature() {
  float temp = getTemperature();
  debugTemp(temp);

  letters(0, 'T');
  putPixel(2, 5, 0b00011101);
  putPixel(4, 4, 0b00011101);
  
  digits(7,  (int(temp)/10)%10);
  digits(12,  int(temp)%10);
  putPixel(5, 17, 0b00011101);
  digits(18,  int(temp*10)%10);
  
  refreshDisplays();
  delay(10000);
}

int getCacheTime(DateTime now) {
  return now.minute() + now.hour() * 100;
}
