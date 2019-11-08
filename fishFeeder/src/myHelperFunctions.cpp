#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

#include <myHelperFunctions.h>

global g = new global();

//////////////////////////////////////////////////
// Set up timer
//////////////////////////////////////////////////
void timerIsr() {
  encoder.service();
}

//////////////////////////////////////////////////
// prepText
//////////////////////////////////////////////////
void prepText(int x, int y, int size) {
  display.setCursor(x, y);
  display.setTextColor(WHITE);
  display.setTextSize(size);
}

//////////////////////////////////////////////////
// checkEncoder
//////////////////////////////////////////////////
int checkEncoder() {
  encPos -= encoder.getValue();
    // if value > temp, UP
    // if value < temp, DOWN
  int16_t temp = 0;
  
  if (encPos != oldEncPos) {
    temp = encPos - oldEncPos;
    oldEncPos = encPos;
    return temp;
  } 

buttonState = encoder.getButton();

  if (buttonState != 0) {
    temp = buttonState;

    switch (buttonState) {
      case ClickEncoder::Open:          //0
        break;
      case ClickEncoder::Closed:        //1
        break;
      case ClickEncoder::Pressed:       //2
        break;
      case ClickEncoder::Held:          //3
        break;
      case ClickEncoder::Released:      //4
        break;
      case ClickEncoder::Clicked:       //5
        break;
      case ClickEncoder::DoubleClicked: //6
        break;
    }
  }

  return temp;
}

void setHour() {
    Serial.println("Set Hour");
    
    while(1) {
        int readEncoder = checkEncoder();
        switch (readEncoder)
        {
            case -1:
            case 1:
                g.myHour += readEncoder;
                if (g.myHour < 0)
                {
                    g.myHour = 23;
                } else if (g.myHour > 23)
                {
                    g.myHour = 0;
                }
                Serial.println(g.myHour);
                break;
            
            case 5:
            case 6:
                return;  
            default:
                break;   
        }

        display.clearDisplay();
        prepText(0, 0, 2);
        display.print("Hour: ");
        display.print(g.myHour);
        display.display();
    }
}

void setMinute() {
    while(1) {
        int readEncoder = checkEncoder();
        switch (readEncoder)
        {
            case -1:
            case 1:
                g.myMinute += readEncoder;
                if (myMinute < 0) {
                    myMinute = 59;
                } 
                else if (myMinute > 59) {
                    myMinute = 0;
                }
                Serial.println(myMinute);
                break;
            case 5:
            case 6:
                return;  
            default:
                break;   
        }

        display.clearDisplay();
        prepText(0, 0, 2);
        display.print("Minute: ");
        display.print(g.myMinute);
        display.display();
    }
}

//////////////////////////////////////////////////
// Alarm stuff
//////////////////////////////////////////////////
void myAlarm() {
    // stepper.move(stepsToTurn);
    Serial.println("myAlarm is going off");
}

void digitalClockDisplay() {
  // digital clock display of the time

    if (g.lastSecond != second())
    {
        g.lastSecond = second();
        // Serial.print(hour());
        // printDigits(minute());
        // printDigits(second());

        display.clearDisplay();
        prepText(0, 0, 2);
        Serial.print(hour());
        display.print(hour());
        display.print(printDigits(minute()));
        display.print(printDigits(second()));
        display.display();

        Serial.println(); 
    }
}

String printDigits(int digits) {
    String myString = ":";
  Serial.print(":");
  if (digits < 10) {
    myString += '0';
    Serial.print('0');
  }
  myString += digits;
  Serial.print(digits);
  return myString;
}