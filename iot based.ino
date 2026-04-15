#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// RTC object
RTC_DS3231 rtc;

// LCD address 0x27 (kabhi 0x3F bhi ho sakta hai)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.setCursor(0,0);
    lcd.print("RTC NOT FOUND");
    while (1);
  }

  // 👉 FIRST TIME ONLY (upload ke baad ek baar uncomment karo)
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // Time display
  lcd.setCursor(0, 0);
  lcd.print("Time: ");

  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");

  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");

  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  // Date display
  lcd.setCursor(0, 1);
  lcd.print("Date: ");

  if (now.day() < 10) lcd.print("0");
  lcd.print(now.day());
  lcd.print("/");

  if (now.month() < 10) lcd.print("0");
  lcd.print(now.month());
  lcd.print("/");

  lcd.print(now.year());

  delay(1000);
}
