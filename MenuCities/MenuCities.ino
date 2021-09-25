
#include "flexmenu.h"
#include "flexmisc.h"
#include <Arduino.h>
#include <U8g2lib.h>
 
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /*DO clock=*/ 13, /*DI data=*/ 11, /*CS cs=*/ 10, /*DC dc=*/ 9, /* RES reset=*/ 8);
 
TFlexMenu FlexMenu; // Menu class I wrote myself 
 TFlexRotaryEncoder re (2, 3, 4); // For the rotary encoder class I wrote myself, please refer to this post: https://www.arduino.cn/thread-86535-1-1.html
 
char *psCitiesChina[6] ={"Beijing", "Shanghai", "Guangzhou", "Shenzhen","Tianjin", "Hangzhou"};
char *psCitiesUSA[4] ={"NewYork", "Manhattan", "Washington", "Seattle"};
char *psAnimals[5] ={"dog", "cat", "mouse", "pig", "cow"};
 
void reRotateEvent(int direct)
{
    if (direct == -1) FlexMenu.clickUp();
    if (direct == 1)  FlexMenu.clickDown();
}
 
void Int0Event()
{
  re.checkState();
}
 
 void fmOnDisplayTiltle (char * content, int ttype) // Display title
{
    u8g2.setFont(u8g2_font_unifont_t_chinese1);
    u8g2.drawUTF8(0, 15, content);
    u8g2.drawLine(0, 16, 128, 16);
}
 
 void fmOnDisplayContent (int idx, char * content, int ctype) // Display menu content
{
         if (ctype == 1) // What needs to be displayed is: general menu items
    {
        u8g2.drawUTF8(5, (idx + 1) * 16,content);
    }
         else if (ctype == 2) // What needs to be displayed is: the general menu item indicated by the cursor
    {
        u8g2.drawUTF8(5, (idx + 1) * 16,content);
        u8g2.drawTriangle(0, 8 + idx * 16, 0, 16 + idx * 16, 4, 12+ idx * 16);
    }
         else if (ctype == 3) // What needs to be displayed is: the value to be adjusted
    {
       int ll = strlen(content) * 8;
       int sp = (128 - ll) / 2;
       u8g2.drawUTF8(sp, 3 * 16, content);
    }
}
 
void fmOnAdjustValueEvent(int id, int value, int upDown)
{
   String s = "fmOnAdjustValueEvent: id: " + id ;
   s = s + " value: " + value;
   s = s + " UpDown: " + upDown;
   //Serial.println(s);  
}
 
void fmOnOKValueEvent(int id, int value)
{
 // Serial.println("fmOnOKValueEvent: id:%d, value: %d ", id, value);  
}
 
void initMenu()
{
         TFlexMenuItem * mi1, * mi2; // Create two temporary variables for creating hierarchical menus.
 
 
         // Add a menu under the root menu named "menu1 Value", NULL means there is no parent menu item, addMenuItem returns the handle (address) of the menu item after adding
    mi1 = FlexMenu.addMenuItem("menu1 Value", NULL);
 
         // Add a menu under the "menu1 Value" menu, named "menu11", mi1 passes in the handle of menu1 Value
    mi2 = FlexMenu.addMenuItem("menu11", mi1);
 
         // Add an integer parameter, the name of this parameter is "value111", the id is 1 (used to set and read at runtime), the maximum value is 200, the minimum value is 3, the default value is 100,
    FlexMenu.addMenuValue(1,"value111", mi2, 100, 200, 3);
    
    mi1 = FlexMenu.addMenuItem("menu2 Cities", NULL);
 
 
         // Add a list parameter, the name of this parameter is "China Cities", id is 2 (used to set and read at runtime), the list of candidates is psCitiesChina, the default is to select the first one, a total of 6 candidates Value
    FlexMenu.addMenuValueList(2,"China Cities", mi1, 0, 6, psCitiesChina);
 
         // Add a list parameter, the name of this parameter is "USA Cities", id is 3 (used to set and read at runtime), the list of candidates is psCitiesUSA, the default is to select the first one, a total of 4 candidates Value
    FlexMenu.addMenuValueList(3,"USA Cities", mi1, 0, 4, psCitiesUSA);
    
    mi1 = FlexMenu.addMenuItem("menu3 Animals", NULL);
    FlexMenu.addMenuValueList(4,"Animal Type", mi1, 0, 5, psAnimals);
    
    mi1 = FlexMenu.addMenuItem("MENU4", NULL);
    mi1 = FlexMenu.addMenuItem("MENU41", mi1);
    mi1 = FlexMenu.addMenuItem("MENU411", mi1);
    mi1 = FlexMenu.addMenuItem("MENU4111", mi1);
    mi1 = FlexMenu.addMenuItem("MENU41111", mi1);
    
    mi1 = FlexMenu.addMenuItem("menu5", NULL);
    mi1 = FlexMenu.addMenuItem("menu6", NULL);
    mi1 = FlexMenu.addMenuItem("menu7", NULL);
    mi1 = FlexMenu.addMenuItem("menu8", NULL);
    mi1 = FlexMenu.addMenuItem("menu9", NULL);
    mi1 = FlexMenu.addMenuItem("menu0", NULL);
    
    FlexMenu.addMenuValue(100,"value00", NULL, 9, 1000, 3);
    
    FlexMenu.init();
}
 
void setup()
{
    //Serial.begin (9600);
 
    FlexMenu.pU8G2 = &u8g2;
    FlexMenu.pageRow = 3;
    FlexMenu.attachDisplayTitle(fmOnDisplayTiltle);
    FlexMenu.attachDisplayContent(fmOnDisplayContent);
    FlexMenu.attachAdjustValueEvent(fmOnAdjustValueEvent);
    FlexMenu.attachOKValueEvent(fmOnOKValueEvent);
    
    initMenu();
    
    re.attachRotateEvent(reRotateEvent);
    re.setClickResetCount(true);
 
    u8g2.begin();
    attachInterrupt(0, Int0Event, CHANGE);
}
 
void loop()
{
    FlexMenu.display();
    
    if (re.isClick()){ FlexMenu.clickOK();};
}
