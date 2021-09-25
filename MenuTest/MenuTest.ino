
#include <MenuSystem.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Streaming.h>
#include <PinChangeInterrupt.h>
#include <Servo.h>
#include "MyRenderer.h"
#include "MyRenderer.cpp"
#include "ToggleMenuItem.h"
#include "ToggleMenuItem.cpp"
#include "NumericDisplayMenuItem.h"
#include "NumericDisplayMenuItem.cpp"


//###############PIN CONFIG############
const uint8_t knobPbPin = 8;
const uint8_t knobAPin = 4;
const uint8_t knobBPin = 2;

//############Serial Config############
const uint32_t serialBaudRate = 115200;

//############LED Pin CONFIG###############
const uint8_t redLEDpin = 6;
const uint8_t greenLEDpin = 3;
const uint8_t blueLEDpin = 5;

//###########Photo Transistor Pin#########
uint8_t photoTransistorPin = A0;

//############Servo Pin Config#########
uint8_t servoPin = 11;

//#############OLED CONFIG#################
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const uint8_t textRows = 4;


//############Menu#########
const uint16_t updateMenuInterval = 200;
MyRenderer my_renderer(&display, textRows);
MenuSystem ms(my_renderer);

Menu ledMenu("LED MENU", nullptr);
BackMenuItem ledBackItem("Back", &on_ledBackItemSelected, &ms);
ToggleMenuItem ledPowerItem("LED Power - ", nullptr, "ON", "OFF", false);
NumericMenuItem ledRedItem("Red", nullptr,0,0,255);
NumericMenuItem ledGreenItem("Green", nullptr, 0, 0, 255);
NumericMenuItem ledBlueItem("Blue", nullptr, 0, 0, 255);
NumericDisplayMenuItem photoTransistorItem("Sensor", nullptr, 0);
Menu servoMenu("Servo Menu", nullptr);
BackMenuItem servoBackItem("Back", on_servoBackItemSelected, &ms);
ToggleMenuItem servoPowerItem("Servo Power - ", &on_servoPowerItemSelected, "ON", "OFF", false);
NumericMenuItem servoAngleItem("Set Angle", nullptr, 0, 0, 180);

//##############Servo ###############
Servo myServo;

void setup()
{
	Serial.begin(serialBaudRate);
	initializeDisplay();
	initializeMenu();
	initializeKnob();
	initializePhotoTransistor();
}


void loop()
{
	updateMenu();
	updateLEDs();
	updateServo();
	updatePhotoTransistorValue();
	delay(100);
}

void on_ledBackItemSelected(BackMenuItem* p_menu_item)
{
	ms.back();
}

void on_servoBackItemSelected(BackMenuItem* p_menu_item)
{
	ms.back();
}

void on_servoPowerItemSelected(ToggleMenuItem* p_menu_item)
{
	if (p_menu_item->get_state())
		myServo.attach(servoPin);
	else
		myServo.detach();
}

//#######Encoder knob Functions###############
void initializeKnob()
{
	pinMode(knobAPin, INPUT_PULLUP);
	pinMode(knobBPin, INPUT_PULLUP);
	pinMode(knobPbPin, INPUT_PULLUP);
	attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(knobBPin), knob_isr, CHANGE);
	attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(knobPbPin), pbPressed, FALLING);
}

void knob_isr()
{
	//if the encoder knob was rotated, the dirction of motion
	//can be decoded as following
	if (digitalRead(knobAPin))
	{
		if (digitalRead(knobBPin)) //knob moved CW
			ms.next();
		else if (!digitalRead(knobBPin)) //knob moved CCW
			ms.prev();
	}

}

//button pushed interrupt
void pbPressed()
{
	ms.select();
}

//############Update LED##############
void updateLEDs()
{
	if (ledPowerItem.get_state())
	{
		analogWrite(redLEDpin, ledRedItem.get_value());
		analogWrite(greenLEDpin, ledGreenItem.get_value());
		analogWrite(blueLEDpin, ledBlueItem.get_value());
	}
	else
	{
		analogWrite(redLEDpin, 0);
		analogWrite(greenLEDpin, 0);
		analogWrite(blueLEDpin, 0);
	}
	
}
//#######Phototransistor Functions####
void initializePhotoTransistor()
{
	pinMode(photoTransistorPin, INPUT_PULLUP);
}
void updatePhotoTransistorValue()
{
	photoTransistorItem.set_value(analogRead(photoTransistorPin));
}
//###########Servo Functions###############
void updateServo()
{
	myServo.write(servoAngleItem.get_value());
}
//#######Display Functions###############
void initializeDisplay()
{
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
		Serial.println(F("SSD1306 allocation failed"));
		for (;;); // Don't proceed, loop forever
	}
	display.clearDisplay();
	display.setTextColor(WHITE, BLACK);
	display.setTextSize(1);
}
//#######Menu Functions##################
void initializeMenu()
{
	Serial << servoAngleItem.get_formatted_value() << endl;
	//add menus to root 
	ms.get_root_menu().add_menu(&ledMenu);
	ledMenu.add_item(&ledBackItem);
	ledMenu.add_item(&ledPowerItem);
	ledMenu.add_item(&ledRedItem);
	ledMenu.add_item(&ledGreenItem);
	ledMenu.add_item(&ledBlueItem);
	ledMenu.add_item(&photoTransistorItem);
	ms.get_root_menu().add_menu(&servoMenu);
	//servoMenu.add_item(&backItem);
	servoMenu.add_item(&servoBackItem);
	servoMenu.add_item(&servoPowerItem);
	servoMenu.add_item(&servoAngleItem);

	//initialize menu update service
	ms.display();
}

void updateMenu()
{
	ms.display();
}

