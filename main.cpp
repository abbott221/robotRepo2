


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

robot chet;


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



    while (true)
    {
        MainMenuCall();
    }

    return 0;
}



void MainMenuCall()
{
    int mainChoice;
    menu main;
    //choice 0
    main.addOption("  PLACE HOLDER :)");
    //choice 1
    main.addOption("  Run");
    //choice 2
    main.addOption("  Adjust Movement");
    //choice 3
    main.addOption("  Display Movements");
    //choice 4
    main.addOption("  Insert Movement");
    //choice 5
    main.addOption("  Turn On Movement");
    //choice 6
    main.addOption("  Turn Off Movement");
    //choice 7
    main.addOption("  Turn On Page");
    //choice 8
    main.addOption("  Turn Off Page");
    //choice 9
    main.addOption("  Calibrate/Configure");

    mainChoice = main.UserInterface();

    switch (mainChoice)
    {
        //option 0: in case your finger slips
        case 0:
            break;
        //Option 1: Run
        case 1:
            LCD.WriteLine( "Settings" );
            break;
        //Option 2: Adjust (Set) Movement
        case 2:
            LCD.WriteLine( "Logs" );
            break;
        //Option 3: Display movements
        case 3:
            LCD.WriteLine( "Calibrate" );
            break;
        //Option 4: Insert movement
        case 4:
            LCD.WriteLine( "Calibrate" );
            break;
        //Option 5: Turn on (Old Add) movement
        case 5:
            LCD.WriteLine( "Calibrate" );
            break;
        //Option 6: Turn off (Old Delete) Movement
        case 6:
            LCD.WriteLine( "Calibrate" );
            break;
        //Option 7: Add page
        case 7:
            LCD.WriteLine( "Calibrate" );
            break;
        //Option 8: Delete Page
        case 8:
            LCD.WriteLine( "Calibrate" );
            break;
        //Option 9: Calibrate/Configure
        case 9:
            LCD.WriteLine( "Calibrate" );
            break;
        default:
            LCD.WriteLine( "Error" );
    }
}














