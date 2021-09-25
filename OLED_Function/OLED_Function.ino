
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 // use 64 for a 128x64
 String Text;
 int Xcoord;
 int Ycoord;
Adafruit_SSD1306 myScreen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() 
  {
    Serial.begin(11500);
    if(!myScreen.begin(SSD1306_SWITCHCAPVCC, 0x3C))
      {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // infinite loop
      }
    myScreen.display();
    delay(2000);
    myScreen.clearDisplay(); // all pixels are off
  

  }

void loop() 
  {
    String TextA= "Neverest IOT Lab";
//    int Row = 20;
//    int Column = 20;
  OLEDPrint(TextA, 0, 0);
  OLEDPrint("hello",40, 40);
  myScreen.clearDisplay(); // all pixels are off 

  delay(3000);
  }
  void OLEDPrint(String Text, int Xcoord, int Ycoord )
  {
      
  
    myScreen.setTextSize(1); // font-size allowed range 1-8
    myScreen.setTextColor(WHITE);
    myScreen.setCursor(Xcoord, Ycoord);
  
    // display static text
    myScreen.println(Text);
  
    myScreen.display();
    //myScreen.startscrollright(0x00, 0x07);
  }

  
