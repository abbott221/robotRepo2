

#include "FEHGUI.h"


int menu::pageAndMoveInterface(movement moreMoves[])
{
    int pageChoice = -1;
    int moveChoice = -1;


    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    pageChoice = pageInterface();

    movement tempMoves[12];


    for (int i = 0; i < 12; i++)
    {
        tempMoves[i] = moreMoves[i + (12 * pageChoice)];
    }

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    moveChoice = moveInterface(tempMoves);
    moveChoice = moveChoice + (12 * pageChoice);

    return moveChoice;
}

int menu::pageInterface()
{
    int pageChoice = -1;
    menu pageMenu;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

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

    pageChoice = pageMenu.UserInterface();

    return pageChoice;
}


int menu::moveTypeInterface()
{
    int typeChoice = -1;
    menu typeMenu;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    typeMenu.addOption("  Time: Straight");
    typeMenu.addOption("  Time: Left");
    typeMenu.addOption("  Time: Right");
    typeMenu.addOption("  Time: Backwards");

    typeMenu.addOption("  Encoder: Straight");
    typeMenu.addOption("  Encoder: Left");
    typeMenu.addOption("  Encoder: Right");
    typeMenu.addOption("  Encoder: Backwards");

    typeMenu.addOption("  Set Servo Position");

    typeMenu.addOption("  Line From Right");
    typeMenu.addOption("  Line From Left");

    typeMenu.addOption("  Num Codes - Sheet");

    typeChoice = typeMenu.UserInterface();


    return typeChoice;
}


int menu::moveInterface(movement moves[])
{
    int moveChoice = -1;
    menu moveMenu;
    movement tempMove;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    LCD.WriteLine("Select movement");

    for (int i = 0; i < 12; i++)
    {
        if (moves[i].getDataType() == tInt)
        {
            tempMove.setMovement(moves[i].getOperation(), moves[i].getIntValue());
            moveMenu.addOption("temp");
            moveMenu.selection[i].setOption( (i+2), tempMove );
            moveMenu.selection[i].setState( moves[i].getState() );
        }
        else if (moves[i].getDataType() == tFloat)
        {
            tempMove.setMovement(moves[i].getOperation(), moves[i].getFloatValue());
            moveMenu.addOption("temp");
            moveMenu.selection[i].setOption( (i+2), tempMove );
            moveMenu.selection[i].setState( moves[i].getState() );
        }
        else if (moves[i].getDataType() == tDouble)
        {
            tempMove.setMovement(moves[i].getOperation(), moves[i].getDoubleValue());
            moveMenu.addOption("temp");
            moveMenu.selection[i].setOption( (i+2), tempMove );
            moveMenu.selection[i].setState( moves[i].getState() );
        }
        else if (moves[i].getDataType() == tVoid)
        {
            tempMove.setMovement(moves[i].getOperation());
            moveMenu.addOption("temp");
            moveMenu.selection[i].setOption( (i+2), tempMove );
            moveMenu.selection[i].setState( moves[i].getState() );
        }
    }

    moveChoice = moveMenu.UserInterface();

    return moveChoice;
}

