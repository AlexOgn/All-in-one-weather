#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;

double baseline = 1000;

void bmp180_setup() {
  if (pressure.begin())
    Serial.println("BMP180 initialized");
  else {
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while (1);
  }
  
}
double GetAltitude() {
  double a, P;
  P = readPressure();
  a = pressure.altitude(P, baseline);

  return a;
}

double readPressure() {
  char status;
  double T, P, p0, a;
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          return (P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

int GetTemperature(){
  char status;
  double T;
  int a;
  status = pressure.startTemperature();
  if (status != 0) {
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0) {
      a = T / 1;
    }
  }

  return a;
}
