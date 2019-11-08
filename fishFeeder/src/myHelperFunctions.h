#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <TimeLib.h>
#include <TimeAlarms.h>


//////////////////////////////////////////////////
// Method declarations
//////////////////////////////////////////////////
int checkEncoder();
void prepText(int, int, int);
void setHour();
void setMinute();
void myAlarm();
void digitalClockDisplay();
String printDigits(int);
void timerIsr();

//////////////////////////////////////////////////
// OLED Stuff
//////////////////////////////////////////////////
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//////////////////////////////////////////////////
// ClickEncoder Stuff
//////////////////////////////////////////////////
int16_t oldEncPos, encPos;
uint8_t buttonState;

#define pinA 4
#define pinB 5
#define pinSw 6 //switch
#define STEPS 4

ClickEncoder encoder(pinA, pinB, pinSw, STEPS);