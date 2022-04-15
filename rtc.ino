#include "RTCLib.h"

void rtc_setup(){
  if(!rtc.begin()){
    Serial.println("RTC module has messed up");
  }
  
  if(!rtc.isrunning()){
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("RTC adjusted");
  }
  Serial.println("RTC initialized");
}
