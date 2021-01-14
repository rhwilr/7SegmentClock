#include <WiFiEspAT.h>
#include <TimeLib.h> 
#include "SoftwareSerial.h"

SoftwareSerial Serial1(9, 8); // RX, TX
#define AT_BAUD_RATE 9600

const int8_t TIME_ZONE = 0; // UTC
const char NTP_SERVER[] = "0.ch.pool.ntp.org";

void initWifi() {
  Serial1.begin(AT_BAUD_RATE);
  WiFi.init(Serial1);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
}

void setupWifi() {
  WiFi.disconnect(); // to clear the way. not persistent
  WiFi.setPersistent(); // set the following WiFi connection as persistent
  WiFi.endAP(); // to disable default automatic start of persistent AP at startup

#if defined(SECRET_SSID) && defined(SECRET_PASS)
  Serial.println();
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(SECRET_SSID);

  int status = WiFi.begin(SECRET_SSID, SECRET_PASS);

  if (status == WL_CONNECTED) {
    Serial.println();
    Serial.println("Connected to WiFi network.");
  } else {
    WiFi.disconnect(); // remove the WiFi connection
    Serial.println();
    Serial.println("Connection to WiFi network failed.");
  }
#else
  Serial.println();
  Serial.print("SECRET_SSID or SECRET_PASS not defined.");
#endif
}

void setupNTP() {
  WiFi.sntp(TIME_ZONE, NTP_SERVER);

  Serial.println("Waiting for SNTP");
  while (WiFi.getTime() < SECS_YR_2000) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println();

}

unsigned long getNTPTime() {
  return WiFi.getTime();
}
