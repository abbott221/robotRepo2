

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


//************************************************
//*                                              *
//*          BEGIN RPScleaner CLASS              *
//*                                              *
//************************************************


//"CONSTRUCTOR" METHODS HERE
RPScleaner::RPScleaner()
{
    initX = 0.0;
    initY = 0.0;
    initAngle = 0.0;

    currentX = 0.0;
    currentY = 0.0;
    currentAngle = 0.0;

    displacementX = 0.0;
    displacementY = 0.0;
    displacementAngle = 0.0;
}




void RPScleaner::initiateMoveData()
{
    update();

    initX = currentX;
    initY = currentY;
    initAngle = currentAngle;
}


void RPScleaner::update()
{
    do {
        currentX = TheRPS.X();
        currentY = TheRPS.Y();
        currentAngle = TheRPS.Heading();
    } while ( !currentValuesAreLegit() );
    //continue until we don't have 0,0,0
}

bool RPScleaner::currentValuesAreLegit()
{
    bool returnThis = false;


    //check x =/= 0
    if (currentX > 0.0 || currentX < 0.0)
    {
        returnThis = true;
    }
    //check y =/= 0
    else if (currentY > 0.0 || currentY < 0.0)
    {
        returnThis = true;
    }
    //check angle =/= 0
    else if (currentAngle > 0.0)
    {
        returnThis = true;
    }
    else
    {
        returnThis = false;
    }



    return returnThis;
}



void RPScleaner::compareX(float supposedValue)
{
    //to-do
}
void RPScleaner::compareY(float supposedValue)
{
    //to-do
}
void RPScleaner::compareAngle(float supposedValue)
{
    //to-do
}


//LOTS OF "GETTER" METHODS

float RPScleaner::getInitX()
{
    return initX;
}
float RPScleaner::getInitY()
{
    return initY;
}
float RPScleaner::getInitAngle()
{
    return initAngle;
}


float RPScleaner::getCurrentX()
{
    return currentX;
}
float RPScleaner::getCurrentY()
{
    return currentY;
}
float RPScleaner::getCurrentAngle()
{
    return currentAngle;
}


float RPScleaner::getDisplacementX()
{
    return displacementX;
}
float RPScleaner::getDisplacementY()
{
    return displacementY;
}
float RPScleaner::getDisplacementAngle()
{
    return displacementAngle;
}


