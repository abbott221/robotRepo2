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
