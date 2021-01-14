#include <DHT.h>

#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

void initDHT()
{
  dht.begin();
}

float getHumidity()
{
  return dht.readHumidity();
}

float getTemperature()
{
  return dht.readTemperature();
}
