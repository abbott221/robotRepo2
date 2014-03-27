


#include "main.h"




//lMotor: -power is forward
FEHMotor lMotor(FEHMotor::Motor0);
FEHMotor rMotor(FEHMotor::Motor1);

ButtonBoard buttons( FEHIO::Bank3 );
FEHEncoder  leftEncoder( FEHIO::P0_0);
FEHEncoder  rightEncoder( FEHIO::P0_1);

AnalogInputPin CDS(FEHIO::P0_7);

AnalogInputPin optoLeft(FEHIO::P2_0);
AnalogInputPin optoMid(FEHIO::P2_2);
AnalogInputPin optoRight(FEHIO::P2_4);

FEHWONKA TheRPS;
FEHServo lolServo(FEHServo::Servo0);
FEHBattery lolBattery (FEHIO::BATTERY_VOLTAGE);

//======================================




int leftPower = 80;
int rightPower = 78;

int tempLeftPower = 80;
int tempRightPower = 78;

int servoMin = 556;
int servoMax = 2500;

//for the encoders
float lowThresh = 0.388;
float highThresh = 1.547;

//for line following
float optoThresh = 2.0;
float bLineDifThresh = 1.0;
float yLineDifThresh = .4;
float leftOptoThresh = 0.0;
float rightOptoThresh = 0.0;
float midOptoThresh = 0.0;

bool configLightStart = true;
bool configCourseTimer = true;
bool configDelay = true;
bool configRPS = true;

double displayRate = 0.2;

double courseStartTime = 0.0;
int numOfDisplays = 0;

PMode currentPowerMode = STOP;
int leftPowerMode = leftPower;
int rightPowerMode = rightPower;

float decisionLight = 0.0;

int currentMove = 0;



robot chet;
RPScleaner cleaner;



void driveProcess(movement moves[]);


//===================================================

int mainChoice = -1;
menu mainMenu;

int pageChoice = -1;
menu pageMenu;

int configureChoice = -1;
menu configureMenu;

int operationChoice = -1;
menu operationMenu;

int main(void)
{
    chet.moreMoves[0].setMovement(8, 120);
    chet.moreMoves[1].setMovement(50, 1.50);
    chet.moreMoves[2].setMovement(6, 4.697);
    //chet.moreMoves[3].setMovement(202, 0.0);
    chet.moreMoves[4].setMovement(4, 21.2);
    //chet.moreMoves[5].setMovement(203, 0.0);
    chet.moreMoves[6].setMovement(5, 4.00);
    //chet.moreMoves[5].setMovement(12, 2.00);
    chet.moreMoves[7].setMovement(21, 5.0);
    chet.moreMoves[8].setMovement(8, 45);
    chet.moreMoves[9].setMovement(8, 120);

    chet.moreMoves[12].setMovement(6, 4.0);
    chet.moreMoves[13].setMovement(50, -2.549);
    chet.moreMoves[14].setMovement(6, 4.00);
    chet.moreMoves[15].setMovement(51, 20.559);
    chet.moreMoves[16].setMovement(64, 88.80);
    chet.moreMoves[17].setMovement(64, 88.80);
    chet.moreMoves[18].setMovement(51, 46.0);
    chet.moreMoves[19].setMovement(64, 84.00);
    chet.moreMoves[20].setMovement(64, 84.00);
    chet.moreMoves[21].setMovement(4, 8.00);
    chet.moreMoves[22].setMovement(5, 5.00);

    chet.moreMoves[24].setMovement(6, 6.0);
    chet.moreMoves[25].setMovement(64, 133.0);
    chet.moreMoves[26].setMovement(64, 133.0);

    chet.moreMoves[36].setMovement(8, 45);
    chet.moreMoves[37].setMovement(8, 120);
    chet.moreMoves[38].setMovement(7, 3.50);
    chet.moreMoves[39].setMovement(5, 4.0);
    chet.moreMoves[40].setMovement(50, -1.299);
    chet.moreMoves[41].setMovement(5, 11.0);
    chet.moreMoves[42].setMovement(64, 103.0);
    chet.moreMoves[43].setMovement(64, 103.00);
    chet.moreMoves[44].setMovement(4, 21.50);
    chet.moreMoves[45].setMovement(6, 4.00);






    //choice 0
    mainMenu.addOption("  PLACE HOLDER :)");
    //choice 1
    mainMenu.addOption("  Run");
    //choice 2
    mainMenu.addOption("  Adjust Movement");
    //choice 3
    mainMenu.addOption("  Display Movements");
    //choice 4
    mainMenu.addOption("  Insert Movement");
    //choice 5
    mainMenu.addOption("  Turn On Movement");
    //choice 6
    mainMenu.addOption("  Turn Off Movement");
    //choice 7
    mainMenu.addOption("  Turn On Page");
    //choice 8
    mainMenu.addOption("  Turn Off Page");
    //choice 9
    mainMenu.addOption("  Calibrate/Configure");




    pageMenu.addOption("  Page 1");
    pageMenu.addOption("  Page 2");
    pageMenu.addOption("  Page 3");
    pageMenu.addOption("  Page 4");
    pageMenu.addOption("  Page 5");
    pageMenu.addOption("  Page 6");
    pageMenu.addOption("  Page 7");
    pageMenu.addOption("  Page 8");
    pageMenu.addOption("  Page 9");
    pageMenu.addOption("  Page 10");
    pageMenu.addOption("  Page 11");
    pageMenu.addOption("  Page 12");

    for (int i = 0; i < 12; i++)
    {
        pageMenu.selection[i].setState(true);
    }









    while (true)
    {
        MainMenuCall();
    }

    return 0;
}



void MainMenuCall()
{


    mainChoice = mainMenu.UserInterface();




    int typeChoice;
    int moveChoice;

    int tempNum;
    int incrs[] = {25, 10, 1};





    //option 0: in case your finger slips
    if (mainChoice == 0)
    {
        //
    }



    //Option 1: Run
    else if (mainChoice == 1)
    {
        driveProcess(chet.moreMoves);
    }



    //Option 2: Adjust (Set) Movement
    else if (mainChoice == 2)
    {
        moveChoice = mainMenu.pageAndMoveInterface(chet.moreMoves);



        //USER INTERFACE: MOVEMENT TYPE SELECTION
        typeChoice = mainMenu.moveTypeInterface();



        //Set the time of the adjusted move
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        //integer valued move
        if (typeChoice == 8)
        {
            int tempIntValue = chet.moreMoves[moveChoice].getIntValue();

            int incrs[] = {5, 3, 1};

            tempIntValue = SetInteger(tempIntValue, incrs, 3);

            chet.moreMoves[moveChoice].setMovement(typeChoice, tempIntValue);
        }
        else if (typeChoice == 11)
        {
            int moveIncrs[] = {100, 25, 5, 1};

            int intIncrs[] = {5, 3, 1};
            double doubleIncrs[] = {1.0, 0.1, 0.01};

            int tempIntValue = 0;
            double tempDoubleValue = 0.0;

            int expansion = SetInteger(tempIntValue, moveIncrs, 4);

            //EXPANSION IS THE VALUE OF THE TYPE OF MOVE TO SET; NOW IT'S LIKE SETTING ANOTHER MOVE

            //change threshold method
            if (expansion == 12)
            {
                tempDoubleValue = SetDouble(tempDoubleValue, doubleIncrs, 3);

                chet.moreMoves[moveChoice].setMovement(expansion, tempDoubleValue);
            }
            else if (expansion == 13)
            {
                chet.moreMoves[moveChoice].setMovement(expansion, 0.0);
            }
            else
            {
                int theDataType = setTheDataType();

                if (theDataType == 0)
                {
                    tempDoubleValue = SetDouble(tempDoubleValue, doubleIncrs, 3);
                    chet.moreMoves[moveChoice].setMovement(expansion, tempDoubleValue);
                }

                else
                {
                    tempIntValue = SetInteger(tempIntValue, intIncrs, 3);
                    chet.moreMoves[moveChoice].setMovement(expansion, tempIntValue);
                }

            }



            //tempIntValue stores that out of range move
            //tempIntValue = SetInteger(tempIntValue, incrs, 3);

            //moreMoves[moveChoice].setMovement(typeChoice, tempIntValue);
        }
        //double valued move
        else
        {
            double tempDoubleValue = chet.moreMoves[moveChoice].getDoubleValue();

            double incrs[] = {1.0, 0.1, 0.01};

            tempDoubleValue = SetDouble(tempDoubleValue, incrs, 3);

            chet.moreMoves[moveChoice].setMovement(typeChoice, tempDoubleValue);
        }
    }



    //Option 3: Display movements
    else if (mainChoice == 3)
    {
        mainMenu.pageAndMoveInterface(chet.moreMoves);
    }



    //Option 4: Insert movement
    else if (mainChoice == 4)
    {
        LCD.WriteLine("Enter num of move (0-142)");


        tempNum = SetInteger(0, incrs, 3);

        bool tempState;
        for (int i = 142; i >= tempNum; i--)
        {
            tempState = chet.moreMoves[i].getState();
            if (chet.moreMoves[i].getDataType() == tDouble)
            {
                chet.moreMoves[i+1].setMovement(chet.moreMoves[i].getOperation(), chet.moreMoves[i].getDoubleValue());
            }
            else
            {
                chet.moreMoves[i+1].setMovement(chet.moreMoves[i].getOperation(), chet.moreMoves[i].getIntValue());
            }
            chet.moreMoves[i+1].setState(tempState);
        }
        chet.moreMoves[tempNum].setMovement(0, 0.0);
        chet.moreMoves[tempNum].setState(false);
    }



    //Option 5: Turn on (Old Add) movement
    else if (mainChoice == 5)
    {
        moveChoice = mainMenu.pageAndMoveInterface(chet.moreMoves);

        chet.moreMoves[moveChoice].setState(true);
    }



    //Option 6: Turn off (Old Delete) Movement
    else if (mainChoice == 6)
    {
        moveChoice = mainMenu.pageAndMoveInterface(chet.moreMoves);

        chet.moreMoves[moveChoice].setState(false);
    }



    //Option 7: Add page
    else if (mainChoice == 7)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Select Page");

        //pageChoice = pageInterface();
        pageChoice = pageMenu.UserInterface();


        for (int i = 0; i < 12; i++)
        {
            chet.moreMoves[i + (12 * pageChoice)].setState(true);
        }

        pageMenu.selection[pageChoice].setState(true);
    }



    //Option 8: Delete Page
    else if (mainChoice == 8)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Select Page");

        //pageChoice = pageInterface();
        pageChoice = pageMenu.UserInterface();


        for (int i = 0; i < 12; i++)
        {
            chet.moreMoves[i + (12 * pageChoice)].setState(false);
        }

        pageMenu.selection[pageChoice].setState(false);
    }



    //Option 9: Calibrate/Configure
    else if (mainChoice == 9)
    {
        ConfigureMenuCall();
    }

}



void ConfigureMenuCall()
{
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    //LCD.WriteLine("Cunfiguer Yor Stuf Heer");

    LCD.Write("Voltage: ");
    LCD.WriteLine(lolBattery.Voltage());

    configureMenu.addOption("  Calibrate Power");

    configureMenu.addOption("  Calibrate Servo");

    configureMenu.addOption("  Start with Light");
    configureMenu.selection[2].setState(configLightStart);

    configureMenu.addOption("  Course Timer");
    configureMenu.selection[3].setState(configCourseTimer);

    configureMenu.addOption("  2 sec delay");
    configureMenu.selection[4].setState(configDelay);

    configureMenu.addOption("  Use RPS");
    configureMenu.selection[5].setState(configRPS);

    configureMenu.addOption("  Read mid-opto value");

    configureMenu.addOption("  Read CDS values");

    configureMenu.addOption("  Read RPS values");

    //configureSelect[9].setOption(11, "  Data Spew Modulus");
    configureMenu.addOption("  Time between displays");





    configureChoice = configureMenu.UserInterface();



    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    //calibrate motor
    if (configureChoice == 0)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Setting Left Motor");

        int tempPower = leftPower;
        int incrs[] = {5, 3, 1};
        tempPower = SetInteger(tempPower, incrs, 3);

        leftPower = tempPower;

        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );
        LCD.WriteLine("Setting Right Motor");


        tempPower = rightPower;
        //int incrs[] = {5, 3, 1};
        tempPower = SetInteger(tempPower, incrs, 3);

        rightPower = tempPower;
    }
    //calibrate servo
    else if (configureChoice == 1)
    {
        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );

        LCD.WriteLine("Commence the calibration?");

        lolServo.Calibrate();

        //INPUT THE NUMBERS


        LCD.WriteLine("Setting Min");

        int tempTicks = 0;
        int incrs[] = {500, 100, 10, 1};
        tempTicks = SetInteger(tempTicks, incrs, 4);

        servoMin = tempTicks;

        LCD.Clear( FEHLCD::Black );
        LCD.SetFontColor( FEHLCD::White );
        LCD.WriteLine("Setting Max");


        tempTicks = 0;
        //int incrs[] = {5, 3, 1};
        tempTicks = SetInteger(tempTicks, incrs, 4);

        servoMax = tempTicks;



    }

    else if (configureChoice == 2)
    {
        if (configLightStart == true)
        {
            configLightStart = false;
        }
        else
        {
            configLightStart = true;
        }
    }
    else if (configureChoice == 3)
    {
        if (configCourseTimer == true)
        {
            configCourseTimer = false;
        }
        else
        {
            configCourseTimer = true;
        }
    }
    else if (configureChoice == 4)
    {
        if (configDelay == true)
        {
            configDelay = false;
        }
        else
        {
            configDelay = true;
        }
    }
    else if (configureChoice == 5)
    {
        if (configRPS == true)
        {
            configRPS = false;
        }
        else
        {
            configRPS = true;
        }
    }

    //mid-opto values
    else if (configureChoice == 6)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }
        while( !buttons.MiddlePressed() )
        {
            LCD.Write(optoLeft.Value());
            LCD.Write(" ");
            LCD.Write(optoMid.Value());
            LCD.Write(" ");
            LCD.WriteLine(optoRight.Value());

            Sleep(0.10);
        }
        while( buttons.MiddlePressed() )
        {
            //nothing
        }
    }

    //CDS values
    else if (configureChoice == 7)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }
        while( !buttons.MiddlePressed() )
        {
            LCD.WriteLine(CDS.Value());
            Sleep(.10);
        }
        while( buttons.MiddlePressed() )
        {
            //nothing
        }
    }

    //RPS values
    else if (configureChoice == 8)
    {
        while( buttons.MiddlePressed() )
        {
            //this menu is entered by pressing the middle button
        }
        TheRPS.InitializeMenu();
        TheRPS.Enable();
        while( !buttons.MiddlePressed() )
        {
            LCD.Write(TheRPS.Heading());
            LCD.Write(" ");
            LCD.Write(TheRPS.X());
            LCD.Write(" ");
            LCD.WriteLine(TheRPS.Y());
            Sleep(.10);
        }
        TheRPS.Disable();
        while( buttons.MiddlePressed() )
        {
            //nothing
        }
    }
    else if (configureChoice == 9)
    {
        LCD.WriteLine("Setting display rate");

        double tempRate = displayRate;
        double incrs[] = {1.0, 0.1, 0.01};
        tempRate = SetDouble(tempRate, incrs, 3);

        //dataSpew = tempSpew;
        displayRate = tempRate;
    }
}










