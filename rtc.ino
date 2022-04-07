
void rtc_setup(){
  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("RTC adjusted");
  }
  Serial.println("RTC initialized");
}
