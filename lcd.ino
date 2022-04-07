#include <LiquidCrystal.h>
#include "RTClib.h"

const int rs = 8, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

byte degree[8] = {
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
};

void lcd_setup(){
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  lcd.home();

  Serial.println("LCD initialized");
}

void PressureAndTemp() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  int temperature = GetTemperature();
  Serial.println(temperature);
  
  lcd.print(temperature);
  lcd.write(byte(0));
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Pressure: ");
  int pressure = readPressure();
  lcd.print(pressure);
  lcd.print("hPa");
        
}

void Humidity() {
  float h = dht.readHumidity();

  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Altitude: ");
  lcd.print(GetAltitude());
  lcd.print("m");
}

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


void lcd_loop(){
  lcd.setCursor(0, 0);

  if (counter % 5 == 0 && counter != 0) {
    whatToDisplay++;
  }
  
  if(counter % 3600 == 0){
    WriteFile();
    send_data();
  }
  counter++;

  if (whatToDisplay % 3 == 0) {
    lcd.clear();
    DateAndTime();
  } else if (whatToDisplay % 3 == 1) {
    lcd.clear();
    PressureAndTemp();
    whatToDisplay++;
    delay(5000);
  } else if (whatToDisplay % 3 == 2) {
    lcd.clear();
    Humidity();
  }

  

  delay(1000);
}
