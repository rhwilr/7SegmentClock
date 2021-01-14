#include <Wire.h>
#include <Timezone.h>
#include "RTClib.h"

#include "Wifi.h"

RTC_DS3231 rtc;

unsigned int lastNtpSync = 0;

TimeChangeRule mez = {"MEZ", Last, Sun, Oct, 2, 60};     // UTC + 1 hours
TimeChangeRule mesz = {"MESZ", Last, Sun, Mar, 2, 120};    // UTC + 2 hours

Timezone middleEu(mez, mesz);

void syncRTC() {
  Serial.println("Fetching NTP time...");  

  unsigned long time = getNTPTime();
  rtc.adjust(DateTime(time));
}

DateTime getTime() {
  if (lastNtpSync >= 1000) {
    syncRTC();

    lastNtpSync = 0;
  }
  
  lastNtpSync++;
  
  return rtc.now();
}

DateTime getLocalTime()
{
  return middleEu.toLocal(getTime().unixtime());
}

void initRTC()
{
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while(1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power!");
  }

  middleEu.writeRules(100);
}


