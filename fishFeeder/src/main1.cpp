#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <BasicStepperDriver.h>

#include <myHelperFunctions.h>

//////////////////////////////////////////////////
// Global Variables
//////////////////////////////////////////////////
int myHour;
int myMinute;
int lastSecond = -1;
int stepsToTurn = 1800;
int displayScreen = 0;
int displayScreenCount = 2;

//////////////////////////////////////////////////
// Set up timer
//////////////////////////////////////////////////
void timerIsr()
{
    encoder.service();
}

//////////////////////////////////////////////////
// Setup
//////////////////////////////////////////////////
void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
    while (!Serial)
        ;

    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr);

    encoder.setAccelerationEnabled(false);
    encoder.setHoldTime(2000);
    oldEncPos = 0;

    display.begin(SSD1306_SWITCHCAPVCC);

    display.clearDisplay();
    myHour = setTime(23, "Hour");
    myMinute = setTime(59, "Min");

    display.clearDisplay();

    stepper.begin(RPM, MICROSTEPS);

    setMyTime();
}

//////////////////////////////////////////////////
// Main Loop
//////////////////////////////////////////////////
void loop()
{
    int value = checkEncoder();

    switch (displayScreen)
    {
    case 0:
        digitalClockDisplay();
        break;
    case 1:
        logoDisplay();
        break;

    default:
        break;
    }

    Alarm.delay(100);

    switch (value)
    {
    case 1:
    case 2:
    case 4:
    case 6:
        Serial.println(value);
        break;
    case 5:
        Serial.println(value);

        displayScreen++;
        if (displayScreen >= displayScreenCount)
        {
            displayScreen = 0;
        }
        break;
    case 3:
        dispense();
        break;
    default:
        break;
    }
}

//////////////////////////////////////////////////
// prepText
//////////////////////////////////////////////////
void prepText(int x, int y, int size)
{
    display.setCursor(x, y);
    display.setTextColor(WHITE);
    display.setTextSize(size);
}

//////////////////////////////////////////////////
// checkEncoder
//////////////////////////////////////////////////
int checkEncoder()
{
    encPos -= encoder.getValue();
    // if value > temp, UP
    // if value < temp, DOWN
    int16_t temp = 0;

    if (encPos != oldEncPos)
    {
        temp = encPos - oldEncPos;
        oldEncPos = encPos;
        return temp;
    }

    buttonState = encoder.getButton();
    if (buttonState != 0)
    {
        temp = buttonState;

        switch (buttonState)
        {
        case ClickEncoder::Open: //0
            break;
        case ClickEncoder::Closed: //1
            break;
        case ClickEncoder::Pressed: //2
            break;
        case ClickEncoder::Held: //3
            break;
        case ClickEncoder::Released: //4
            break;
        case ClickEncoder::Clicked: //5
            break;
        case ClickEncoder::DoubleClicked: //6
            break;
        }
    }
    return temp;
}

//////////////////////////////////////////////////
// Set Time
//////////////////////////////////////////////////
int setTime(int upperLimit, String timeToSet)
{
    Serial.print("Set ");
    Serial.print(timeToSet);
    Serial.println(": ");

    int myTime = 0;

    while (1)
    {
        int readEncoder = checkEncoder();
        switch (readEncoder)
        {
        case -1:
        case 1:
            myTime += readEncoder;
            if (myTime < 0)
            {
                myTime = upperLimit;
            }
            else if (myTime > upperLimit)
            {
                myTime = 0;
            }
            Serial.println(myTime);
            break;
        case 5:
        case 6:
            return myTime;
        default:
            break;
        }

        display.clearDisplay();
        prepText(0, 0, 2);
        display.print("Set ");
        display.print(timeToSet);
        display.print(":");

        prepText(0, 18, 2);
        display.print(myTime);
        display.display();
    }
}

//////////////////////////////////////////////////
// Alarm stuff
//////////////////////////////////////////////////
void dispense()
{
    display.clearDisplay();
    prepText(0, 0, 2);
    display.print("Dispensing!");
    display.display();
    Serial.println("Dispensing!");

    stepper.move(stepsToTurn);
}

void setMyTime()
{
    Serial.println();
    Serial.print("hour: ");
    Serial.println(myHour);
    Serial.print("minute: ");
    Serial.println(myMinute);

    setTime(myHour, myMinute, 0, 1, 1, 11);

    Alarm.alarmRepeat(8, 0, 5, dispense);
}

//////////////////////////////////////////////////
// Clock Display Stuff
//////////////////////////////////////////////////
void digitalClockDisplay()
{
    // digital clock display of the time

    if (lastSecond != second())
    {
        lastSecond = second();

        display.clearDisplay();

        prepText(0, 0, 2);
        display.print("H. Farms");

        prepText(0, 18, 2);
        Serial.print(hour());
        display.print(hour());
        display.print(printDigits(minute()));
        display.print(printDigits(second()));
        display.display();

        Serial.println();
    }
}

String printDigits(int digits)
{
    String myString = ":";
    Serial.print(":");
    if (digits < 10)
    {
        myString += '0';
        Serial.print('0');
    }
    myString += digits;
    Serial.print(digits);
    return myString;
}

//////////////////////////////////////////////////
// logoDisplay
//////////////////////////////////////////////////
void logoDisplay()
{
    // add code to display the Heyward Farms Logo
    display.clearDisplay();
    prepText(0, 0, 2);
    display.print("HFarms Logo");
    display.display();
}

//////////////////////////////////////////////////
// Todo
//////////////////////////////////////////////////
// display clock
// hold 2s to dispense now?
// click does what?
//     swap between clock and logo?

// add alarms
