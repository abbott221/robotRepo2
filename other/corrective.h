#ifndef CORRECTIVE_H
#define CORRECTIVE_H


#include "main.h"





//extern int testingInteger;





extern int RPScustomAction;
extern double RPStolerance;
extern double tempDefaultStorage;

extern float initialMoveY;
extern float initialMoveAngle;

extern float updateX;
extern float updateY;
extern float updateHeading;

extern bool RPSisWorking;
extern bool initMoveDataValid;
extern bool correctionOn;

extern bool correctionAction;

extern bool insufficientY;


//==================================================




//METHOD 200 (changes RPS tolerance)
void ChangeTolerance(double value);

//Method 201
void SetUpComparison(double distance);

//Method 202
void TurnCorrectionOn();
//Method 203
void TurnCorrectionOff();


//THIS IS NOT A MOVEMENT
double PerformComparison(double RPSdistance);

//collect data from the start of the move to be checked throughout
void CBinitiateMoveData();
//check data, doesn't interfere unless it determines to do so
void CBmidmovePassiveCheck();



void fillerForActionTaken();

void updateRPSisWorking();

bool checkFlags();



#endif // CORRECTIVE_H
