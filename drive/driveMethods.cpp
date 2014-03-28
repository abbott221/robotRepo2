//#include "main.h"

#include "driveHeaders.h"






//30s RPS Settings/General
//40s turning
//50s Real RPS
//70s Displaced RPS
//90s Relative RPS








void logDataStuffs()
{
    double dTime = TimeNow() - courseStartTime;

    //DO UPDATE CORRECTIVE STUFF HERE



    CBmidmovePassiveCheck();





    if (dTime > displayRate * numOfDisplays)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );


        //DO NOT UPDATE CORRECTIVE STUFF HERE



        if (buttons.MiddlePressed())
        {
            SetPowerStop();
            while (buttons.MiddlePressed())
            {
                //nothing
            }
            MainMenuCall();
        }




        LCD.Write(TheRPS.Heading());
        LCD.Write(" ");
        LCD.Write(TheRPS.X());
        LCD.Write(" ");
        LCD.WriteLine(TheRPS.Y());

        LCD.Write(optoLeft.Value());
        LCD.Write(" ");
        LCD.Write(optoMid.Value());
        LCD.Write(" ");
        LCD.WriteLine(optoRight.Value());



        LCD.Write("Left Power: ");
        LCD.WriteLine(leftPowerMode);

        LCD.Write("Right Power: ");
        LCD.WriteLine(rightPowerMode);



        LCD.Write("Power Mode: ");
        if (currentPowerMode == STRAIGHT)
        {
            LCD.WriteLine("Straight");
        }
        else if (currentPowerMode == LEFT)
        {
            LCD.WriteLine("Left");
        }
        else if (currentPowerMode == RIGHT)
        {
            LCD.WriteLine("Right");
        }
        else if (currentPowerMode == BACKWARDS)
        {
            LCD.WriteLine("Backwards");
        }
        else if (currentPowerMode == STOP)
        {
            LCD.WriteLine("Stop");
        }





        LCD.Write("Value of Light = ");

        //COMMENT OUT THIS LINE IF YOU DON'T WANT IT
        LCD.WriteLine(decisionLight);

        //Blue = 0.367
        //Red = 0.164
        //Threshold = 0.265

        if (decisionLight < 0.265)
        {
            LCD.WriteLine("Red");
        }
        else
        {
            LCD.WriteLine("Blue");
        }


        numOfDisplays++;
    }



    //potential for freezing in CBcorrective area
    //down here, middleButton escape still works?
    cleaner.update();
    //cleaner.update() and the methods in RPScleaner shouldn't call logDataStuffs()
    //because that would result in an infinite loop


    //milliCounter++;
}




void SetPowerStraight() {
    currentPowerMode = STRAIGHT;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(rightPower);
    lMotor.SetPercent(-1 * leftPower);
}
void SetPowerLeft() {
    currentPowerMode = LEFT;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(rightPower);
    lMotor.SetPercent(leftPower);
}
void SetPowerRight() {
    currentPowerMode = RIGHT;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(-1 * rightPower);
    lMotor.SetPercent(-1 * leftPower);
}
void SetPowerBackwards() {
    currentPowerMode = BACKWARDS;
    leftPowerMode = leftPower;
    rightPowerMode = rightPower;

    rMotor.SetPercent(-1 * rightPower);
    lMotor.SetPercent(leftPower);
}
void SetPowerStop() {
    currentPowerMode = STOP;
    leftPowerMode = 0;
    rightPowerMode = 0;

    rMotor.Stop();
    lMotor.Stop();
}



void SetPowerStraight(int left, int right) {
    currentPowerMode = STRAIGHT;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(rightPowerMode);
    lMotor.SetPercent(-1 * leftPowerMode);
}
void SetPowerLeft(int left, int right) {
    currentPowerMode = LEFT;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(rightPowerMode);
    lMotor.SetPercent(leftPowerMode);
}
void SetPowerRight(int left, int right) {
    currentPowerMode = RIGHT;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(-1 * rightPowerMode);
    lMotor.SetPercent(-1 * leftPowerMode);
}
void SetPowerBackwards(int left, int right) {
    currentPowerMode = BACKWARDS;
    leftPowerMode = left;
    rightPowerMode = right;

    rMotor.SetPercent(-1 * rightPowerMode);
    lMotor.SetPercent(leftPowerMode);
}



//METHOD 0
//goes "straight" for specified time
void DriveForTime(double time)
{
    SetPowerStraight();

    //Sleep(time);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time )
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    SetPowerStop();
}


//METHOD 1
//definitely turns left for specified time
void TurnLeftForTime(double time)
{
    SetPowerLeft();

    //rMotor.SetPercent(rightPower);
    //lMotor.SetPercent(leftPower);

    //Sleep(time);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time)
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}

//METHOD 2
//definitely turns right for specified time
void TurnRightForTime(double time)
{
    SetPowerRight();

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(-1 * leftPower);

    //Sleep(time);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time)
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}



//METHOD 3
//goes "straight" for specified time
void BackwardsForTime(double time)
{
    SetPowerBackwards();

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(leftPower);

    //Sleep(time);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time)
    {
        Sleep(1);

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}




//METHOD 4
void EncForward(double distance)
{
    SetPowerStraight();

    //rMotor.SetPercent(rightPower);
    //lMotor.SetPercent(-1 * leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

            rMotor.SetPercent(rightPower+6);

            lMotor.SetPercent(-1 * leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){
            rMotor.SetPercent(rightPower);

            lMotor.SetPercent(-1 * (leftPower+4));
 
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

            rMotor.SetPercent(rightPower);

            lMotor.SetPercent(-1 * leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD 5
void EncLeft(double distance)
{
    SetPowerLeft();

    //rMotor.SetPercent(rightPower);
    //lMotor.SetPercent(leftPower);


    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

              rMotor.SetPercent(rightPower+6);

              lMotor.SetPercent(leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

              rMotor.SetPercent(rightPower);

              lMotor.SetPercent(leftPower+4);

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

              rMotor.SetPercent(rightPower);

              lMotor.SetPercent(leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD 6
void EncRight(double distance)
{
    SetPowerRight();

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(-1* leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

             rMotor.SetPercent(-1 * (rightPower+6));

             lMotor.SetPercent(-1 *leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(-1 *(leftPower+4));

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(-1 *leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}



//METHOD 7
void EncBackward(double distance)
{
    SetPowerBackwards();

    //rMotor.SetPercent(-1 * rightPower);
    //lMotor.SetPercent(leftPower);

    while (rightEncoder.Counts() <= ((distance * 36) / (2.75 * 3.1415)))
    {
        if(leftEncoder.Counts() - rightEncoder.Counts() > 2){

             rMotor.SetPercent(-1 * (rightPower+6));

             lMotor.SetPercent(leftPower);
        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() < -2){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(leftPower+4);

        }
        else if(leftEncoder.Counts() - rightEncoder.Counts() > -2 && leftEncoder.Counts() - rightEncoder.Counts() < 2 ){

             rMotor.SetPercent(-1 * rightPower);

             lMotor.SetPercent(leftPower);
        }
        logDataStuffs();
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD 8
void SetServoDegree(int degrees)
{

    //Sleep(500);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < 0.5)
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    lolServo.SetDegree(degrees);
}



//METHOD 9
void FollowBlackLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);


    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 5);
            rMotor.SetPercent(75);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

//METHOD 10
void FollowLightLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 5);
            rMotor.SetPercent(75);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}



//METHOD 11
//this method sets the number for methods beyond 10



//METHOD 12
void ChangeOptoThreshold(double thresh)
{
    optoThresh = thresh;
}


//METHOD 13
void DisplayLightValue()
{
    double average = 0.0;
    for (int i = 0; i<100;i++)
    {
        average += CDS.Value();

        logDataStuffs();
        Sleep(1);
    }
    average = average / 100.0;

    LCD.Write("Value of Light = ");

    //COMMENT OUT THIS LINE IF YOU DON'T WANT IT
    LCD.WriteLine(average);

    //Blue = 0.367
    //Red = 0.164
    //Threshold = 0.265

    if (average < 0.265)
    {
        LCD.WriteLine("Red");
    }
    else
    {
        LCD.WriteLine("Blue");
    }
}

//METHOD 14
void FlyOverLightValue(double time)
{
    rMotor.SetPercent(50);
    lMotor.SetPercent(-1 * 50);

    double highest = 0.0;
    double newVal = 0.0;




    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time )
    {
        newVal = CDS.Value();
        if (newVal > highest)
        {
            highest = newVal;
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }







    //average = average / 100.0;

    LCD.Write("Value of Light = ");

    //COMMENT OUT THIS LINE IF YOU DON'T WANT IT
    LCD.WriteLine(highest);

    decisionLight = highest;

    //Blue = 0.367
    //Red = 0.164
    //Threshold = 0.265

    if (highest < 0.265)
    {
        LCD.WriteLine("Red");
    }
    else
    {
        LCD.WriteLine("Blue");
    }


    lMotor.Stop();
    rMotor.Stop();
}



//METHOD 16
void unFollowBlackLine(double goThisLong)
{
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

//METHOD 17
void unFollowLightLine(double goThisLong)
{
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if (optoMid.Value() > optoThresh)
        {
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);
        }
        else if (optoRight.Value() > optoThresh)
        {
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}


//METHOD 18
void Pause(double time)
{
    SetPowerStop();

    //rMotor.Stop();
    //lMotor.Stop();

    //Sleep(time);

    double startTime = TimeNow();
    double dTime = 0.0;
    while( dTime < time )
    {
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    //rMotor.Stop();
    //lMotor.Stop();

    SetPowerStop();
}


//METHOD 19
void LightDecisionTurn(double distance)
{


    if (decisionLight < 0.265)
    {
        //LCD.WriteLine("Red");
        EncLeft(distance);
    }
    else
    {
        //LCD.WriteLine("Blue");
        EncRight(distance);
    }


}

//METHOD 20
void GetOptoThresh(){
    double leftAverage = 0.0;
    double rightAverage = 0.0;
    double midAverage = 0.0;

    for(int i = 0; i < 100 ; i++){
        leftAverage += optoLeft.Value();
        rightAverage += optoRight.Value();
        midAverage += optoMid.Value();
    }
    leftOptoThresh = leftAverage/100;
    rightOptoThresh = rightAverage/100;
    midOptoThresh = midAverage/100;

}


//METHOD  21
void BlackLineFollow(double time){
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while(dTime < time){
        if(myAbsolute(midOptoThresh-optoMid.Value())>= bLineDifThresh){
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);

        }
        else if (myAbsolute(rightOptoThresh-optoRight.Value())>= bLineDifThresh){
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);


    }
        else if(myAbsolute(leftOptoThresh-optoLeft.Value())>= bLineDifThresh){
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);

        }
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }
    rMotor.Stop();
    lMotor.Stop();

}

//METHOD 22
void YellowLineFollow(double time){
    lMotor.SetPercent(60);
    rMotor.SetPercent(-1 * 60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while(dTime < time){
        if(myAbsolute(midOptoThresh-optoMid.Value())>= yLineDifThresh){
            lMotor.SetPercent(60);
            rMotor.SetPercent(-1 * 60);

        }
        else if (myAbsolute(rightOptoThresh-optoRight.Value())>= yLineDifThresh){
            lMotor.SetPercent(75);
            rMotor.SetPercent(-1 * 5);


    }
        else if(myAbsolute(leftOptoThresh-optoLeft.Value())>= yLineDifThresh){
            lMotor.SetPercent(5);
            rMotor.SetPercent(-1 * 75);

        }
        logDataStuffs();
        dTime = TimeNow() - startTime;
    }
    rMotor.Stop();
    lMotor.Stop();

}




//METHOD 23
void JeffBlackLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);


    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if ((optoMid.Value () -.6) > optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if ((optoRight.Value() + 1.6) > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        else if (optoLeft.Value() > optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        //go straight if nothing?
        else
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}

//METHOD 24
void JeffLightLine(double goThisLong)
{
    lMotor.SetPercent(-1 * 60);
    rMotor.SetPercent(60);

    double startTime = TimeNow();
    double dTime = 0.0;

    while( dTime < goThisLong)
    {
        if ((optoMid.Value() -1.1)< optoThresh)
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }
        else if ((optoRight.Value()- .06) < optoThresh)
        {
            lMotor.SetPercent(-1 * 75);
            rMotor.SetPercent(5);
        }
        else if (optoLeft.Value() < optoThresh)
        {
            lMotor.SetPercent(-1 * 5);
            rMotor.SetPercent(75);
        }
        //go straight if nothing?
        else
        {
            lMotor.SetPercent(-1 * 60);
            rMotor.SetPercent(60);
        }

        logDataStuffs();
        dTime = TimeNow() - startTime;
    }

    rMotor.Stop();
    lMotor.Stop();
}


