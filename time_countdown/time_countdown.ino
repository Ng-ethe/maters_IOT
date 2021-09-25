// this program gets the time duration set by the user 
// for the restart function 
// The default time is 8 hours but this value can be adjusted (both hours and minutes)
// using the rotary encoder

#include <DS3231M.h>  // Include the DS3231M RTC library
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

DS3231M_Class DS3231M;

#define encoder0PinA  2
#define encoder0PinB  3
volatile unsigned int encoder0Pos = 0;

int valHr = 8;
int valMin;
int valC;

byte clk;
byte menuCount = 1;
byte dir = 0;
bool runState = false;

DateTime initial_time = DS3231M.now();  // get the current time
DateTime now = DS3231M.now();
int initial_hour = initial_time.hour();
int initial_min = initial_time.minute();
int restartHour = initial_hour + valHr;
int restartMin = initial_min + valMin;

DateTime countdown_hr ;
DateTime countdown_min ;




////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.display();
  display.clearDisplay();
  attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2

}

void loop() {
  // put your main code here, to run repeatedly:
  clk = digitalRead(4);
  
  countdown_hr = restartHour - now.hour();
  countdown_min = restartMin - now.minute();
  
  menuCheck();
  displayCountdown();
  display.clearDisplay();
  delay(50);

}

void displayCountdown(){
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.println("Time left to Restart:");
  
  display.setCursor(10, 30);
//  display.println(countdown_hr);
  display.setCursor(30, 30);
  display.println(":");
  display.setCursor(35, 30);
  //display.println(countdown_min);

  display.display();

}

void menuCheck() {
  if (clk == LOW && menuCount < 5) {
    menuCount++;
    encoder0Pos = 0;
  }
  if (clk == LOW && menuCount >= 5) {
    menuCount = 1;
  }

  if (menuCount == 1) {
    valHr = 8 + encoder0Pos;
  }
  if (menuCount == 2) {
    valMin = encoder0Pos;
  }
  if (menuCount == 3) {
    valC = encoder0Pos;
  }
}

void doEncoder() {
  if (digitalRead(encoder0PinA) == HIGH) {
    if (digitalRead(encoder0PinB) == LOW && encoder0Pos > 0) {
      encoder0Pos = encoder0Pos - 1;
      dir = 0;
    }
    else {
      encoder0Pos = encoder0Pos + 1;
      dir = 1;
    }
  }
  else
  {
    if (digitalRead(encoder0PinB) == LOW ) {
      encoder0Pos = encoder0Pos + 1;
      dir = 1;
    }
    else {
      if (encoder0Pos > 0) {
        encoder0Pos = encoder0Pos - 1;
        dir = 0;
      }
    }
  }
}
