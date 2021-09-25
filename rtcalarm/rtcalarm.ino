
#include <DS3231M.h>  // Include the DS3231M RTC library
/***************************************************************************************************
** Declare all program constants                                                                  **
***************************************************************************************************/

const uint32_t SERIAL_SPEED{115200};     ///< Set the baud rate for Serial I/O
const uint8_t  LED_PIN{13};              ///< Arduino built-in LED pin number
const uint8_t  SPRINTF_BUFFER_SIZE{32};  ///< Buffer size for sprintf()

/***************************************************************************************************
** Declare global variables and instantiate classes                                               **
***************************************************************************************************/
DS3231M_Class DS3231M;                           ///< Create an instance of the DS3231M Class
char          inputBuffer[SPRINTF_BUFFER_SIZE];  ///< Buffer for sprintf()/sscanf()

int AlarmDay = 0;
int AlarmHour = 0;
int AlarmMin = 0;
int AlarmSec = 0;


void setup() {
  /*!
    @brief    Arduino method called once at startup to initialize the system
    @details  This is an Arduino IDE method which is called first upon boot or restart. It is only
              called one time and then control goes to the main "loop()" method, from which control
              never returns
    @return   void
  */
  Serial.begin(SERIAL_SPEED);
#ifdef __AVR_ATmega32U4__  // If 32U4 then wait for the serial interface to initialize
  delay(3000);
#endif
  Serial.print(F("\nStarting Set program\n"));
  Serial.print(F("- Compiled with c++ version "));
  Serial.print(F(__VERSION__));
  Serial.print(F("\n- On "));
  Serial.print(F(__DATE__));
  Serial.print(F(" at "));
  Serial.print(F(__TIME__));
  Serial.print(F("\n"));
  while (!DS3231M.begin())  // Initialize communications with the RTC
  {
    Serial.println(F("Unable to find DS3231MM. Checking again in 3s."));
    delay(3000);
  }  // of loop until device is located
  Serial.println(F("DS3231M initialized."));
  DS3231M.adjust();  // Set to library compile Date/Time
  Serial.print(F("Date/Time set to compile time: "));
  DateTime now = DS3231M.now();  // get the current time
  // Use sprintf() to pretty print the date/time with leading zeros
  sprintf(inputBuffer, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  Serial.println(inputBuffer);
  Serial.print(F("DS3231M chip temperature is "));
  Serial.print(DS3231M.temperature() / 100.0, 1);  // Value is in 100ths of a degree
  Serial.println(
      "\xC2\xB0"
      "C");
  Serial.println(F("Setting alarm to go off in 12 seconds."));
  DS3231M.setAlarm(secondsMinutesHoursDateMatch,
                   now + TimeSpan(0, 0, 0, 12));  // Alarm goes off in 12 seconds
  Serial.println(F("Setting INT/SQW pin to toggle at 1Hz."));
  DS3231M.pinSquareWave();  // Make 1Hz signal on INT/SQW pin
}  // of method setup()

void loop() {
  /*!
    @brief    Arduino method for the main program loop
    @details  This is the main program for the Arduino IDE, it is an infinite loop and keeps on
              repeating.
    @return   void
  */
  static uint8_t secs;
  DateTime       now = DS3231M.now();  // get the current time
  if (secs != now.second())            // Output if seconds have changed
  {
    sprintf(inputBuffer, "%04d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(),
            now.hour(), now.minute(), now.second());
    Serial.println(inputBuffer);  // Display the current date/time
    secs = now.second();          // Set the counter variable
  }                               // of if the seconds have changed
  if (DS3231M.isAlarm())          // If the alarm bit is set
  {
    Serial.println("Alarm has gone off.");
    DS3231M.clearAlarm();
    // Alarm in 12 seconds. This will also reset the alarm state
    DS3231M.setAlarm(secondsMinutesHoursDateMatch, now + TimeSpan(AlarmDay, AlarmHour, AlarmMin, AlarmSec));  //AlarmDay AlarmHour AlarmMin AlarmSec
  }  // of if-then an alarm has triggered
}  // of method loop()
