#include <DS3231M.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

#define encoder0PinA  2
#define encoder0PinB  3
volatile unsigned int encoder0Pos = 0;

int valA;
int valB;
int valC;

byte clk;
byte menuCount = 1;
byte dir = 0;
bool runState = false;



void staticMenu() {
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 0);
  display.println("Neverest IOT Lab");
  //---------------------------------
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.println("Hours:");
  display.setCursor(60, 10);
  display.println(valA);

  display.setCursor(10, 20);
  display.println("Minutes:");
  display.setCursor(60, 20);
  display.println(valB);

  display.setCursor(10, 30);
  display.println("Days:");
  display.setCursor(60, 30);
  display.println(valC);

  display.setCursor(10, 40);
  display.println("Start:");
  display.setCursor(45, 40);
  if (encoder0Pos > 5 && menuCount == 4) {
    display.println("Run!");
    runState = true;
  } else {
    display.println("Idle");
    runState = false;
  }
  display.setCursor(2, (menuCount * 10) + 10);
  display.println(">");

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
    valA = encoder0Pos;
  }
  if (menuCount == 2) {
    valB = encoder0Pos;
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

void setup() {
    
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.display();
  display.clearDisplay();
  attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
}

void loop() {
  clk = digitalRead(4);
  menuCheck();
  staticMenu();
  display.clearDisplay();
  delay(100);
}
