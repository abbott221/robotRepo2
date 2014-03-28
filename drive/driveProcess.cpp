
#include "main.h"


void theLoop(movement loopMoves[], int numMoves);


void tempBefore ()
{
    //int tempSize = 20;
    //movement useThese[tempSize];
    //theLoop(useThese, tempSize);
}


void tempAfter ()
{
    //int tempSize = 14;
    //movement useThese[tempSize];
    //theLoop(useThese, tempSize);
}



void driveProcess(movement moves[])
{
    //Option 4: Run

    double time;
    int pressOven;

    lMotor.Stop();
    rMotor.Stop();

    leftEncoder.SetThresholds(lowThresh, highThresh);

    lolServo.SetMin(servoMin);
    lolServo.SetMax(servoMax);

    //LCD.WriteLine(lolBattery.Voltage());

    if (configRPS)
    {
        TheRPS.InitializeMenu();
        TheRPS.Enable();
        pressOven = TheRPS.Oven();
    }

    if (configLightStart)
    {
        float value = 0.60;
        while (value > 0.30 && !buttons.MiddlePressed() )
        {
            value = CDS.Value();
            Sleep(.10);

            LCD.WriteLine(value);
        }
    }

    if (configCourseTimer)
    {
        time = TimeNow();
    }
    courseStartTime = TimeNow();
    numOfDisplays = 0;


    tempBefore();

    theLoop(moves, 144);

    tempAfter();

    if (configRPS)
    {
        TheRPS.Disable();

        LCD.Write("Oven Presses: ");
        LCD.WriteLine(pressOven);
    }

    if (configCourseTimer)
    {
        time = TimeNow() - time;
        LCD.Write("Time for run: ");
        LCD.WriteLine(time);
    }

    LCD.Write("Voltage: ");
    LCD.WriteLine(lolBattery.Voltage());

    LCD.WriteLine("Press Middle Button");
    while( !buttons.MiddlePressed() )
    {
        //nothing
    }

    lMotor.Stop();
    rMotor.Stop();
}



void theLoop(movement loopMoves[], int numMoves)
{
    double useDoubleValue = 0.0;
    int useIntValue = 0;

    /*
     * THE METHOD "logDataStuffs()" HAS REMOVED THE NEED FOR THE COMPLETION VARIABLE
     *
     *
    for (int i = 0; i < numMoves; i++)
    {
        loopMoves[i].setCompletion(false);
    }
    */

    //currentMove

    for (currentMove = 0; currentMove < numMoves; currentMove++)
    {

        useDoubleValue = loopMoves[currentMove].getDoubleValue();
        useIntValue = loopMoves[currentMove].getIntValue();

        /*
         * USE "logDataStuffs()" INSTEAD
         *
         *
        if (configRPS)
        {
            LCD.Write(TheRPS.Heading());
            LCD.Write(" ");
            LCD.Write(TheRPS.X());
            LCD.Write(" ");
            LCD.WriteLine(TheRPS.Y());
        }
        */

        if (loopMoves[currentMove].getState() == true)
        {
            //milliCounter = 0;
            //initialMoveAngle = TheRPS.Heading();
            CBinitiateMoveData();
            cleaner.initiateMoveData();


            leftEncoder.ResetCounts();
            rightEncoder.ResetCounts();

            //this sleep timer was for diagnosis of the first move not being a proper distance?
            //Sleep(.25);


            tempLeftPower = leftPower;
            tempRightPower = rightPower;


            if (loopMoves[currentMove].getOperation() == 0)
            {
                DriveForTime(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 1)
            {
                TurnLeftForTime(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 2)
            {
                TurnRightForTime(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 3)
            {
                BackwardsForTime(useDoubleValue);
            }

            else if (loopMoves[currentMove].getOperation() == 18)
            {
                Pause(useDoubleValue);
            }




            else if (loopMoves[currentMove].getOperation() == 4)
            {
                EncForward(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 5)
            {
                EncLeft(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 6)
            {
                EncRight(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 7)
            {
                EncBackward(useDoubleValue);
            }





            else if (loopMoves[currentMove].getOperation() == 8)
            {
                SetServoDegree(useIntValue);
            }


            else if (loopMoves[currentMove].getOperation() == 9)
            {
                FollowBlackLine(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 10)
            {
                FollowLightLine(useDoubleValue);
            }



            //METHOD 12
            else if (loopMoves[currentMove].getOperation() == 12)
            {
                ChangeOptoThreshold(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 13)
            {
                DisplayLightValue();
            }

            else if (loopMoves[currentMove].getOperation() == 14)
            {
                FlyOverLightValue(useDoubleValue);
            }




            else if (loopMoves[currentMove].getOperation() == 16)
            {
                unFollowBlackLine(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 17)
            {
                unFollowLightLine(useDoubleValue);
            }

            else if (loopMoves[currentMove].getOperation() == 18)
            {
                Pause(useDoubleValue);
            }




            else if (loopMoves[currentMove].getOperation() == 19)
            {
                LightDecisionTurn(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 20)
            {
                GetOptoThresh();
            }
            else if (loopMoves[currentMove].getOperation() == 21)
            {
                BlackLineFollow(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 22)
            {
                YellowLineFollow(useDoubleValue);
            }





            else if (loopMoves[currentMove].getOperation() == 30)
            {
                SetCustomAction(useIntValue);
            }





            else if (loopMoves[currentMove].getOperation() == 50)
            {
                MoveToRealX(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 51)
            {
                MoveToRealY(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 52)
            {
                CheckRealX(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 53)
            {
                CheckRealY(useDoubleValue);
            }




            else if (loopMoves[currentMove].getOperation() == 60)
            {
                TurnLeftPast180();
            }
            else if (loopMoves[currentMove].getOperation() == 61)
            {
                TurnRightPast0();
            }
            else if (loopMoves[currentMove].getOperation() == 62)
            {
                TurnLeftToAngle(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 63)
            {
                TurnRightToAngle(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 64)
            {
                UnsafeTurnToAngle(useDoubleValue);
            }




            else if (loopMoves[currentMove].getOperation() == 80)
            {
                RelativeTurnLeft(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 81)
            {
                RelativeTurnRight(useDoubleValue);
            }





            else if (loopMoves[currentMove].getOperation() == 200)
            {
                ChangeTolerance(useDoubleValue);
            }
            else if (loopMoves[currentMove].getOperation() == 201)
            {
                SetUpComparison(useDoubleValue);
            }

            else if (loopMoves[currentMove].getOperation() == 202)
            {
                TurnCorrectionOn();
            }
            else if (loopMoves[currentMove].getOperation() == 203)
            {
                TurnCorrectionOff();
            }





            leftPower = tempLeftPower;
            rightPower = tempRightPower;


        }



    } //end for loop
}














