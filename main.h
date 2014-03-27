#ifndef MAIN_H
#define MAIN_H

//these were in main.cpp, are they necessary?
#include <string.h>
#include <stdio.h>

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHWONKA.h>
#include <FEHBattery.h>


#include "FEHGUI.h"
#include "driveHeaders.h"
#include "corrective.h"
#include "random.h"






extern int leftPower;
extern int rightPower;

extern int tempLeftPower;
extern int tempRightPower;

extern int servoMin;
extern int servoMax;

extern float lowThresh;
extern float highThresh;

extern float optoThresh;

extern float bLineDifThresh;
extern float yLineDifThresh;
extern float leftOptoThresh;
extern float rightOptoThresh;
extern float midOptoThresh;

extern bool configLightStart;
extern bool configCourseTimer;
extern bool configDelay;
extern bool configRPS;

extern double displayRate;

extern double courseStartTime;

extern int numOfDisplays;


extern int leftPowerMode;
extern int rightPowerMode;

extern float decisionLight;

extern int currentMove;





//lMotor: -power is forward
extern FEHMotor lMotor;
extern FEHMotor rMotor;

extern ButtonBoard buttons;
extern FEHEncoder  leftEncoder;
extern FEHEncoder  rightEncoder;

extern AnalogInputPin CDS;

extern AnalogInputPin optoLeft;
extern AnalogInputPin optoMid;
extern AnalogInputPin optoRight;

extern FEHWONKA TheRPS;
extern FEHServo lolServo;
extern FEHBattery lolBattery;


void MainMenuCall();




#endif // MAIN_H
