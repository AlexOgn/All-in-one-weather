#include <SPI.h>
#include <SD.h>

File file;

void sdcard_setup(){
  pinMode(53, OUTPUT);
  Serial.print("Initializing SD card...");
  if (!SD.begin(50)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  //SD.remove("data.txt");
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

String MakeString(int pressure, int temperature, int humidity, int altitude){
  DateTime date = rtc.now();
  int year = date.year();
  int month = date.month();
  int day = date.day();

  int hour = date.hour();
  int minute = date.minute();
  int second = date.second();
  
  String start = "{";
    
  start += "\"date\": \"" + String(year) + "-" + (month < 10 ? "0" : "" ) + String(month) + "-" + (day < 10 ? "0" : "" ) + String(day) + "T" + (hour < 10 ? "0" : "" ) + String(hour) + ":" + (minute < 10 ? "0" : "" ) + String(minute) + ":" + (second < 10 ? "0" : "" ) + String(second) + ".000Z\",";

  start += "\"pressure\": \"" + String(pressure) + "\",";
  start += "\"temperature\": \"" + String(temperature) + "\",";
  start += "\"humidity\": \"" + String(humidity) + "\",";
  start += "\"altitude\": \"" + String(altitude) + "\"";
  start += "}";

  return start;
}

void WriteFile(){
  file = SD.open("data.txt", FILE_WRITE);
  
  String data = MakeString(readPressure(), GetTemperature(), GetHumidity(), GetAltitude());
  
  file.print(data);
  file.print(",");

  file.close();

}
