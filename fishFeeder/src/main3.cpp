// /*
//  * TimeAlarmExample.pde
//  *
//  * This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
//  * and simulates turning lights on at night and off in the morning
//  * A weekly timer is set for Saturdays at 8:30:30
//  *
//  * A timer is called every 15 seconds
//  * Another timer is called once only after 10 seconds
//  *
//  * At startup the time is set to Jan 1 2011  8:29 am
//  */

// // Questions?  Ask them here:
// // http://forum.arduino.cc/index.php?topic=66054.0

// #include <TimeLib.h>
// #include <TimeAlarms.h>
// #include <TimerOne.h>
// #include <ClickEncoder.h>

// #define pinA 4
// #define pinB 5
// #define pinSw 6 //switch
// #define STEPS 4

// ClickEncoder encoder(pinA, pinB, pinSw, STEPS);

// void myAlarm();
// void digitalClockDisplay();
// void printDigits(int);

// void timerIsr() {
//   encoder.service();
// }


// AlarmId id;

// void setup() {
//   Serial.begin(9600);
//   while (!Serial) ; // wait for Arduino Serial Monitor

//   Timer1.initialize(1000);
//   Timer1.attachInterrupt(timerIsr); 

//   setTime(8,0,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

//   // create the alarms, to trigger at specific times
//   Alarm.alarmRepeat(8,0,5, myAlarm);  // 8:30am every day
// }

// void loop() {
//   digitalClockDisplay();
//   Alarm.delay(1000); // wait one second between clock display
// }

// // functions to be called when an alarm triggers:
// void myAlarm() {
//   Serial.println("Alarm: - turn lights off");
// }


// void digitalClockDisplay() {
//   // digital clock display of the time
//   Serial.print(hour());
//   printDigits(minute());
//   printDigits(second());
//   Serial.println();
// }

// void printDigits(int digits) {
//   Serial.print(":");
//   if (digits < 10)
//     Serial.print('0');
//   Serial.print(digits);
// }