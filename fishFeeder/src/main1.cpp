#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

#include <myHelperFunctions.h>

//////////////////////////////////////////////////
// Global Variables
//////////////////////////////////////////////////
class global {
    int myHour = 0;
    int myMinute = 0;
    int lastSecond = -1;
};

//////////////////////////////////////////////////
// Setup
//////////////////////////////////////////////////
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);

    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr); 

    encoder.setAccelerationEnabled(false);
    oldEncPos = 0;

    display.begin(SSD1306_SWITCHCAPVCC);

    display.clearDisplay();
    setHour();
    setMinute();
    display.clearDisplay();

    Serial.println();    
    Serial.print("hour: ");
    Serial.println(myHour);
    Serial.print("minute: ");
    Serial.println(myMinute);

    setTime(myHour, myMinute, 0, 1, 1, 11);

    Alarm.alarmRepeat(8, 0, 5, myAlarm);
    Alarm.alarmRepeat(7, 0, 5, myAlarm);
    Alarm.alarmRepeat(9, 0, 5, myAlarm);

}

//////////////////////////////////////////////////
// Main Loop
//////////////////////////////////////////////////
void loop() {
    int value = checkEncoder();
    digitalClockDisplay();

  if(value != 0) {
      Serial.println(value);
  }
}




//////////////////////////////////////////////////
// Todo
//////////////////////////////////////////////////
// boot
// enter hour
// click
// enter minute
// click
// enter dispense amount
// click
// 
// display clock
// hold 2s to dispense now?
// click does what?
//     swap between clock and logo?

// add alarms
