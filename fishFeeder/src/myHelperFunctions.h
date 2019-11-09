#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <BasicStepperDriver.h>


//////////////////////////////////////////////////
// Method declarations
//////////////////////////////////////////////////
int checkEncoder();
void prepText(int, int, int);
int setTime(int, String);
// void setMinute();
void myAlarm();
void digitalClockDisplay();
String printDigits(int);
void timerIsr();
void setMyTime();

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

// //////////////////////////////////////////////////
// // Global Variables
// //////////////////////////////////////////////////
// extern int myHour;
// extern int myMinute;
// extern int lastSecond;


//////////////////////////////////////////////////
// Stepper Driver Stuff
//////////////////////////////////////////////////
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 8
// #define STEP 9
#define STEP LED_BUILTIN

//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);