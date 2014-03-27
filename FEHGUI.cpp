

#include "FEHGUI.h"





//************************************************
//*                                              *
//*           BEGIN MOVEMENT CLASS               *
//*                                              *
//************************************************

//"CONSTRUCTOR" METHODS HERE

movement::movement()
{
    operation = 0;
    dataType = tVoid;
    intValue = 0;
    floatValue = 0.0;
    doubleValue = 0.0;
    movementState = false;
}





//"SETTER" METHODS HERE

void movement::setMovement(int dOperation, int dValue)
{
    operation = dOperation;
    dataType = tInt;
    intValue = dValue;
    movementState = true;
}

void movement::setMovement(int dOperation, float dValue)
{
    operation = dOperation;
    dataType = tFloat;
    floatValue = dValue;
    movementState = true;
}

void movement::setMovement(int dOperation, double dValue)
{
    operation = dOperation;
    dataType = tDouble;
    doubleValue = dValue;
    movementState = true;
}

void movement::setMovement(int dOperation)
{
    operation = dOperation;
    dataType = tVoid;
    movementState = true;
}

void movement::setState(bool dState)
{
    if (dState == true)
    {
        movementState = true;
    }
    else
    {
        movementState = false;
    }
}





//"GETTER" METHODS HERE

int movement::getOperation()
{
    return operation;
}

TypeEnum movement::getDataType()
{
    return dataType;
}

int movement::getIntValue()
{
    return intValue;
}

float movement::getFloatValue()
{
    return floatValue;
}

double movement::getDoubleValue()
{
    return doubleValue;
}

bool movement::getState()
{
    return movementState;
}





//************************************************
//*                                              *
//*            BEGIN ROBOT CLASS                 *
//*                                              *
//************************************************

//"CONSTRUCTOR" METHODS HERE

robot::robot()
{
    currentMove = 0;
    moreMoves = new movement[144];
}





//************************************************
//*                                              *
//*           BEGIN OPTION CLASS                 *
//*                                              *
//************************************************

//"CONSTRUCTOR" METHODS HERE

option::option()
{
    dataType = tVoid;
    line = 0;
    name = "";
    optionMovement;
    optionState = false;
}





//"SETTER" METHODS HERE

void option::setOption(int dLine, const char * dName)
{
    dataType = tString;
    line = dLine;
    name = dName;
}

void option::setOption(int dLine, movement dOptionMove)
{
    dataType = dOptionMove.getDataType();
    line = dLine;
    optionMovement = dOptionMove;
    //optionMovement.setMovement(dOptionMove.getType(), dOptionMove.getDoubleValue());
}





//"GETTER" METHODS HERE

TypeEnum option::getDataType()
{
    return dataType;
}

int option::getLine()
{
    return line;
}

const char * option::getName()
{
    return name;
}

bool option::getState()
{
    return optionState;
}





//OTHER METHODS HERE

void option::display()
{
    if (dataType == tString)
    {
        LCD.WriteLine(name);
    }
    else if (dataType == tInt)
    {
        LCD.Write("  Type: ");
        LCD.Write(optionMovement.getOperation());
        LCD.Write("  Int: ");
        LCD.WriteLine(optionMovement.getIntValue());
    }
    else if (dataType == tFloat)
    {
        LCD.Write("  Type: ");
        LCD.Write(optionMovement.getOperation());
        LCD.Write("  Flo: ");
        LCD.WriteLine(optionMovement.getFloatValue());
    }
    else if (dataType == tDouble)
    {
        LCD.Write("  Type: ");
        LCD.Write(optionMovement.getOperation());
        LCD.Write("  Dou: ");
        LCD.WriteLine(optionMovement.getDoubleValue());
    }
    else if (dataType == tVoid)
    {
        LCD.Write("  Type: ");
        LCD.Write(optionMovement.getOperation());
        LCD.Write("  Void");
    }
}






//************************************************
//*                                              *
//*            BEGIN MENU CLASS                  *
//*                                              *
//************************************************

//class menu
menu::menu()
{
    selectionSize = 0;
    selection;
}



//an attempt at dynamic allocation
void menu::addOption(const char *dLine)
{
    //a temporary holder of the data
    option tempSelection[selectionSize + 1];


    for (int i = 0; i < selectionSize; i++)
    {
        tempSelection[i].setOption(i+1, selection[i].getName());
    }

    //add the new option
    tempSelection[selectionSize].setOption(selectionSize, dLine);
    selectionSize += 1;


    //resize selection
    selection = new option[selectionSize];

    //copy the data back into selection
    for (int i = 0; i < selectionSize; i++)
    {
        selection[i].setOption(i+1, tempSelection[i].getName());
    }
}



//a grossly implemented attempt at a GUI
int menu::UserInterface()
{
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    ButtonBoard buttons( FEHIO::Bank3 );


    int height[selectionSize];

    LCD.SetFontColor( FEHLCD::White );

    for (int i = 0; i < selectionSize; i++)
    {
        selection[i].display();
        height[i] = 6 + ( (selection[i].getLine() - 1) * 17);

        if (selection[i].getState() == true)
        {
            //DISPLAY THE LITTLE DOT
            LCD.SetFontColor(FEHLCD::Green);
            //x,y,width,height
            LCD.FillRectangle(12, (height[i]+2),5,5);
            LCD.SetFontColor( FEHLCD::White );
        }
    }



    int minHeight = 0;
    int maxHeight = selectionSize - 1;

    int current = 0;
    int previous = 0;


    LCD.SetFontColor( FEHLCD::Red );
    drawCursor(height[current]);


    bool noSelection = true;

    while( noSelection )
    {
        previous = current;

        if( buttons.LeftPressed() )
        {
            while( buttons.LeftPressed() )
            {
                //nothing
            }
            //Do Stuff here

            if (current == minHeight)
            {
                current = maxHeight;
            }
            else
            {
                current--;
            }
        }
        else if( buttons.RightPressed() )
        {
            while( buttons.RightPressed() )
            {
                //nothing
            }
            //Do Stuff here

            if (current == maxHeight)
            {
                current = minHeight;
            }
            else
            {
                current++;
            }
        }
        else if( buttons.MiddlePressed() )
        {
            while( buttons.MiddlePressed() )
            {
                //nothing
            }

            //Exit the loop
            noSelection = false;
        }

        if (current != previous)
        {
            //cover up previous cursor
            LCD.SetFontColor( FEHLCD::Black );
            drawCursor(height[previous]);

            //draw new cursor
            LCD.SetFontColor( FEHLCD::Red );
            drawCursor(height[current]);
        }

        Sleep(.10);
    }

    LCD.SetFontColor( FEHLCD::White );
    return current;
}

//draw the cursor
void menu::drawCursor(int pixHeight)
{
    LCD.DrawRectangle(1,(pixHeight - 5), 310, 17);
}





