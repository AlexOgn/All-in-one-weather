#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void dht_setup(){
  dht.begin();
  Serial.println("DHT initialized");
}

int GetHumidity(){
  int h = dht.readHumidity();

  return h;
}
