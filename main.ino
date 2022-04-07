#include "RTClib.h"

RTC_DS1307 rtc;

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  
  sdcard_setup();
  wifi_setup();
  bmp180_setup();
  rtc_setup();
  dht_setup();
  lcd_setup();
}

//mnoogo me boli dushata
//ama tva e nai-logichno :@

int counter = 0;
int whatToDisplay = 0;

void loop(){
  lcd_loop();
} 
