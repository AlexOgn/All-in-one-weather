#include <LiquidCrystal.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"
#include <SPI.h>
#include <SD.h>

#define ALTITUDE 550
#define DHTPIN 7
#define DHTTYPE DHT11

SFE_BMP180 pressure;
RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);
File file;

byte degree[8] = {
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
};

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int counter = 0;
int whatToDisplay = 0;

void PressureAndTemp();
void DateAndTime();
void Humidity();
int GetPressure();
int GetTemperature();
int GetHumidity();
void ReadFile();
String MakeString(int, int, int);
void WriteFile();

void setup() {
  pressure.begin();
  dht.begin();

  lcd.begin(16, 2);
  lcd.createChar(0, degree);

  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  //SD.remove("data.txt");
}

void loop() {
  lcd.setCursor(0, 0);

  if (counter % 5 == 0 && counter != 0) {
    whatToDisplay++;
  }
  
  if(counter % 300 == 0){
    WriteFile();
    ReadFile();
  }
  counter++;

  if (whatToDisplay % 3 == 0) {
    lcd.clear();
    DateAndTime();
  } else if (whatToDisplay % 3 == 1) {
    lcd.clear();
    PressureAndTemp();
  } else if (whatToDisplay % 3 == 2) {
    lcd.clear();
    Humidity();
  }

  

  delay(1000);
}

//////////////////////////////////
///////////FUNCTIONS//////////////
//////////////////////////////////

void DateAndTime() {
  DateTime now = rtc.now();

  if (now.day() < 10) {
    lcd.print("0");
  }
  lcd.print(now.day(), DEC);
  lcd.print('/');

  if (now.month() < 10) {
    lcd.print("0");
  }
  lcd.print(now.month(), DEC);
  lcd.print('/');

  lcd.print(now.year(), DEC);

  lcd.print(" ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);

  lcd.setCursor(0, 1);

  if (now.hour() < 10) {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if (now.second() < 10) {
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);
}

void PressureAndTemp() {
  char status;
  double T, P, p0, a;
  status = pressure.startTemperature();
  if (status != 0) {
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0) {
      lcd.print("Temp: ");
      int a = T / 1;
      lcd.print(a);
      lcd.write(byte(0));
      lcd.print("C");

      status = pressure.startPressure(3);
      if (status != 0) {
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0) {
          lcd.setCursor(0, 1);
          lcd.print("Pressure: ");
          int b = P / 1;
          lcd.print(b);
          lcd.print("hPa");
        }
      }
    }
  }
}

void Humidity() {
  float h = dht.readHumidity();

  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Altitude: ");
  lcd.print(ALTITUDE);
  lcd.print("m");
}

int GetPressure(){
  char status;
  double T, P, p0, a;
  int b;
  status = pressure.startTemperature();
  if (status != 0) {
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0) {
      lcd.print("Temp: ");
      int a = T / 1;

      status = pressure.startPressure(3);
      if (status != 0) {
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0) {
          b = P / 1;
        }
      }
    }
  }

  return b;
}

int GetTemperature(){
  char status;
  double T, P, p0, a;
  int b;
  status = pressure.startTemperature();
  if (status != 0) {
    delay(status);
    
    status = pressure.getTemperature(T);
    if (status != 0) {
      int a = T / 1;
    }
  }

  return a;
}

int GetHumidity(){
  int h = dht.readHumidity();

  return h;
}

void ReadFile(){
  file = SD.open("data.txt", FILE_READ);
  if (file) {
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.println("");
    file.close();
  } else {
    Serial.println("error opening test.txt");
  }
}

String MakeString(int pressure, int temperature, int humidity){
  DateTime date = rtc.now();
  int year = date.year();
  int month = date.month();
  int day = date.day();

  int hour = date.hour();
  int minute = date.minute();
  int second = date.second();
  
  String start = "{";
    
  start += "'date': '" + String(year) + "-" + (month < 10 ? "0" : "" ) + String(month) + "-" + (day < 10 ? "0" : "" ) + String(day) + "T" + (hour < 10 ? "0" : "" ) + String(hour) + ":" + (minute < 10 ? "0" : "" ) + String(minute) + ":" + (second < 10 ? "0" : "" ) + String(second) + ".000Z',";

  start += "'pressure': '" + String(pressure) + "',";
  start += "'temperature': '" + String(temperature) + "',";
  start += "'humidity': '" + String(humidity) + "',";
  start += "'altitude': '" + String(ALTITUDE) + "'";
  start += "}";

  return start;
}

void WriteFile(){
  file = SD.open("data.txt", FILE_WRITE);
  
  String data = MakeString(GetPressure(), GetTemperature(), GetHumidity());
  
  file.print(data);
  file.print(",");

  file.close();

}
