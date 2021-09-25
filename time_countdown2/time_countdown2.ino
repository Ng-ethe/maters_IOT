// this program gets the time duration set by the user 
// for the restart function 
// The default time is 8 hours but this value can be adjusted (both hours and minutes)
// using the rotary encoder

#include "rotary_encoder.h"
#include <DS3231M.h>  // Include the DS3231M RTC library
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
//Adafruit_SSD1306 display(-1);

DS3231M_Class DS3231M;
rotary_encoder_Class rotary_encoder;

DateTime initial_time = DS3231M.now();  // get the current time
int initial_hour = initial_time.hour();
int initial_min = initial_time.minute();
int restartHour = initial_hour + valHr;
int restartMin = initial_min + valMin;

void displayCountdown(){
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Time remaining to Restart:");
  
  display.setCursor(10, 30);
  display.println(countdown_hr);
  display.setCursor(30, 30);
  display.println(":");
  display.setCursor(35, 30);
  display.println(countdown_min);

}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  clk = digitalRead(4);
  DateTime countdown_hr = restartHour - now.hour();
  DateTime countdown_min = restartMin - now.minute();
  displayCountdown();
  
  menuCheck();
  //staticMenu();
  display.clearDisplay();
  delay(50);

}
