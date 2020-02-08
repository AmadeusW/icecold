#include "Arduino.h"
#include "../state.h"
#include "../pins.h"
#include "../composition.h"

int moveDispatcher(Method method)
{
    switch (method) {
        case METHOD_SETUP:
            moveSetup();
        case METHOD_WORK:
            moveWork();
        case METHOD_DEBUG:
            moveDebug();
        default:
            return -1;
    }
    return 0;
}

void moveSetup()
{
    startMotor();
}

void moveWork()
{
    switch (state) {
        case moveUp:
            move(true, 255);
            return;
        case moveDown:
            move(false, 255);
            return;
        case idle:
        case errorInvalidInput:
            brake();
            return;
    }
}

void moveDebug()
{
    switch (state) {
        case moveUp:
        case moveDown:
            digitalWrite(LED, HIGH);
            return;
        case errorInvalidInput:
            digitalWrite(LED, turn % 2 == 0 ? HIGH : LOW);
            return;
        default:
            return;
    }
}

void startMotor()
{
   digitalWrite(STBY, HIGH);
}

void brake()
{
   digitalWrite(AIN1, HIGH);
   digitalWrite(AIN2, HIGH);
}

void move(bool up, int speed)
{
   if (up)
   {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);  
   }
   else
   {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
   }
   analogWrite(PWMA, speed);
}

