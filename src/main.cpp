#include <Arduino.h>
#include "RTClib.h"

#include "conf.h"

// #include "Debug.h"
#include "DHTSensor.h"
#include "DisplayDriver.h"
#include "RTC.h"
#include "Wifi.h"
#include "WifiNtp.h"
#include "MQTT.h"
#include "State.h"

int cacheTime = 0;

int getCacheTime(DateTime now);
void displayTemperature();
void displayTime();

State SegmentClock;

void setup() {
  SegmentClock.powerOn = true;

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Start");

  #if defined(SECRET_SSID) && defined(SECRET_PASS)
    initWifi();
    setupWifi(SECRET_SSID, SECRET_PASS);
  #else
    Serial.println();
    Serial.println("SECRET_SSID or SECRET_PASS not defined.");
    while (true);
  #endif

  setupNTP(NTP_TIME_ZONE, NTP_SERVER);

  initRTC();
  syncRTC();

  initMQTT(&SegmentClock, MQTT_SERVER, MQTT_PORT, MQTT_ID, MQTT_USER, MQTT_PASS);

  //initDHT();

  initDisplayDriver();
  // allSegmentsOn();
  refreshDisplays();
  delay(1000);
}

void loop() {
  if (reconnectWifi(SECRET_SSID, SECRET_PASS)) {
    initMQTT(&SegmentClock, MQTT_SERVER, MQTT_PORT, MQTT_ID, MQTT_USER, MQTT_PASS);
    delay(1000);
  }

  loopMQTT();

  if (SegmentClock.powerOn) {
    displayTime();
  } else {
    clear();
    delay(200);
  }

  // clear();
  // displayTemperature();
}

void displayTime() {
  DateTime now = getLocalTime();

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