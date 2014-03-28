
#include "corrective.h"


//int testingInteger = 0;




double RPStolerance = 2.0;
int RPScustomAction = 0;
double tempDefaultStorage= 0.0;

//initial
float initialMoveY = 0.0;
float initialMoveAngle = 0.0;

//current
//put variables here
float updateX = 0.0;
float updateY = 0.0;
float updateHeading = 0.0;

bool RPSisWorking = false;
bool initMoveDataValid = false;
bool correctionOn = false;

bool correctionAction = false;

bool insufficientY = false;



//================================================================




//METHOD 200
void ChangeTolerance(double value)
{
    RPStolerance = value;
}



//Method 201
void SetUpComparison(double distance)
{
    tempDefaultStorage = distance;
}

//Method 202
void TurnCorrectionOn()
{
    correctionOn = true;
}

//Method 203
void TurnCorrectionOff()
{
    correctionOn = false;
}


/*
 *
 * @clears tempDefaultStorage
 *
 */
//THIS IS NOT A MOVEMENT; returns the value of the distance which should be moved
double PerformComparison(double RPSdistance)
{
    double returnMe = RPSdistance;



    if (tempDefaultStorage > 0.0)
    {

        double inaccuracy = myAbsolute(RPSdistance - tempDefaultStorage);

        //if the rps is full of crap
        if (inaccuracy > RPStolerance)
        {
            returnMe = tempDefaultStorage;
        }
        else
        {
            returnMe = RPSdistance;
        }


    }
    tempDefaultStorage = 0.0;



    return returnMe;
}

//========================================================

void CBinitiateMoveData()
{
    initialMoveY = TheRPS.Y();
    initialMoveAngle = TheRPS.Heading();

    //likely to change this statement or add conditions
    updateRPSisWorking();
    //RPSisWorking = true;

    if (RPSisWorking)
    {
        initMoveDataValid = true;
    }
    else
    {
        initMoveDataValid = false;
    }

}



void CBmidmovePassiveCheck()
{
    updateRPSisWorking();

    if (!initMoveDataValid && RPSisWorking)
    {
        initMoveDataValid = true;
        initialMoveY = TheRPS.Y();
        initialMoveAngle = TheRPS.Heading();
    }


    if (RPSisWorking && initMoveDataValid && !correctionAction)
    {
        float dAngle = initialMoveAngle - TheRPS.Heading();
        dAngle = myAbsolute( dAngle );
        //dAngle is the change in the angle since start of move


        if (dAngle > 20.0)
        {

            fillerForActionTaken();
        }



    }


}



void fillerForActionTaken()
{
    //31.7
    correctionAction = true;

    updateRPSisWorking();

    float tempX = updateX;

    bool go = checkFlags();

    if (go)
    {
        //top part of course
        if (updateY > 31.7)
        {
            EncBackward(1.0);
            UnsafeTurnToAngle(90.0);
            UnsafeTurnToAngle(90.0);
            EncBackward(1.0);

            RelativeTurnLeft(90.0);

            if (tempX < -1.0)
            {
                double distance = -1.0 - tempX;
                EncForward(distance);
            }
            else
            {
                double distance = tempX - (-1.0);
                EncBackward(distance);
            }

            RelativeTurnRight(90.0);

            UnsafeTurnToAngle(90.0);
            UnsafeTurnToAngle(90.0);

        }
        //bottom part of course
        else
        {
            EncBackward(1.0);
            UnsafeTurnToAngle(90.0);
            UnsafeTurnToAngle(90.0);
            EncBackward(1.0);

            RelativeTurnRight(90.0);

            if (tempX < 1.7)
            {
                double distance = 1.7 - tempX;
                EncForward(distance);
            }
            else
            {
                double distance = tempX - 1.7;
                EncBackward(distance);
            }

            RelativeTurnLeft(90.0);

            UnsafeTurnToAngle(90.0);
            UnsafeTurnToAngle(90.0);
        }
    }

    correctionAction = false;

}



void updateRPSisWorking()
{
    float updateX = TheRPS.X();
    float updateY = TheRPS.Y();
    float updateHeading = TheRPS.Heading();

    if (updateX > 0.0 || updateX < 0.0)
    {
        RPSisWorking = true;
    }
    else if (updateY > 0.0 || updateY < 0.0)
    {
        RPSisWorking = true;
    }
    else if (updateHeading > 0.0)
    {
        RPSisWorking = true;
    }
    else
    {
        RPSisWorking = false;
    }
}




bool checkFlags()
{
    bool flagsAreGood = false;

    if (correctionOn)
    {
        if (initMoveDataValid)
        {
            if (RPSisWorking)
            {
                //sufficientY
                float dY = updateY - TheRPS.Heading();
                dY = myAbsolute( dY );

                if (dY < 2.0)
                {
                    insufficientY = true;

                    flagsAreGood = true;
                }
                else
                {
                    insufficientY = false;

                    flagsAreGood = false;
                }
            }
            else
            {
                flagsAreGood = false;
            }
        }
        else
        {
            flagsAreGood = false;
        }
    }
    else
    {
        flagsAreGood = false;
    }

    return flagsAreGood;
}
















