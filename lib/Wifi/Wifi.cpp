#include "WiFi.h"
#include "WifiNtp.h"
#include <TimeLib.h> 
#include "SoftwareSerial.h"

SoftwareSerial Serial1(9, 8); // RX, TX
#define AT_BAUD_RATE 9600

void initWifi() {
  Serial1.begin(AT_BAUD_RATE);
  WiFi.init(Serial1);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
}

void setupWifi(const char* ssid, const char* passphrase) {
  WiFi.disconnect(); // to clear the way. not persistent
  WiFi.setPersistent(); // set the following WiFi connection as persistent
  WiFi.endAP(); // to disable default automatic start of persistent AP at startup

  Serial.println();
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  int status = WiFi.begin(ssid, passphrase);

  if (status == WL_CONNECTED) {
    Serial.println();
    Serial.println("Connected to WiFi network.");
  } else {
    WiFi.disconnect(); // remove the WiFi connection
    Serial.println();
    Serial.println("Connection to WiFi network failed.");
  }
}

void setupNTP(int8_t timezone, const char* server) {
  WiFi.sntp(timezone, server);

  Serial.println("Waiting for NTP");
  while (WiFi.getTime() < SECS_YR_2000) {
    delay(1000);
    Serial.print('.');
  }

  Serial.println();
}

unsigned long getNTPTime() {
  return WiFi.getTime();
}

bool reconnectWifi(const char* ssid, const char* passphrase) {
  int status = WiFi.status();

  while (status != WL_CONNECTED) {
    Serial.println("Reconnecting");
    status = WiFi.begin(ssid, passphrase);

    return true;
  }

  return false;
}