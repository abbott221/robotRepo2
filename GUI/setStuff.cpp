

#include "setStuff.h"



double SetDouble (double value, double increments[], int size)
{
    LCD.Write( "Current value = " );
    LCD.WriteLine(value);
    LCD.WriteLine( " Left = decrease" );
    LCD.WriteLine( " Right = increase" );
    LCD.WriteLine( " Middle = next" );

    for (int i = 0; i < size; i++)
    {
        value = IncrementDouble(value, increments[i]);
    }

    LCD.Write( "The value is set to " );
    LCD.WriteLine(value);

    return value;
}

double IncrementDouble (double value, double increment)
{
    LCD.Write( "Incrementing by " );
    LCD.WriteLine(increment);

    while( !buttons.MiddlePressed() )
    {
        if( buttons.LeftPressed() )
        {
            value -= increment;
            LCD.Write( "Current Value: " );
            LCD.WriteLine(value);
            while( buttons.LeftPressed() )
            {
                //nothing
            }
        }
        else if( buttons.RightPressed() )
        {
            value += increment;
            LCD.Write( "Current Value: " );
            LCD.WriteLine(value);
            while( buttons.RightPressed() )
            {
                //nothing
            }
        }

        Sleep(.10);
    }

    while( buttons.MiddlePressed() )
    {
        //nothing
    }

    return value;
}





int SetInteger (int value, int increments[], int size)
{
    LCD.Write( "Current value = " );
    LCD.WriteLine(value);
    LCD.WriteLine( " Left = decrease" );
    LCD.WriteLine( " Right = increase" );
    LCD.WriteLine( " Middle = next" );

    for (int i = 0; i < size; i++)
    {
        value = IncrementDouble(value, increments[i]);
    }

    LCD.Write( "The value is set to " );
    LCD.WriteLine(value);

    return value;
}

int IncrementInteger (int value, int increment)
{
    LCD.Write( "Incrementing by " );
    LCD.WriteLine(increment);

    while( !buttons.MiddlePressed() )
    {
        if( buttons.LeftPressed() )
        {
            value -= increment;
            LCD.Write( "Current Value: " );
            LCD.WriteLine(value);
            while( buttons.LeftPressed() )
            {
                //nothing
            }
        }
        else if( buttons.RightPressed() )
        {
            value += increment;
            LCD.Write( "Current Value: " );
            LCD.WriteLine(value);
            while( buttons.RightPressed() )
            {
                //nothing
            }
        }

        Sleep(.10);
    }

    while( buttons.MiddlePressed() )
    {
        //nothing
    }

    return value;
}



int setTheDataType ()
{
    LCD.WriteLine( "L = double" );
    LCD.WriteLine( "R = int" );
    LCD.WriteLine( "M = continue" );

    int value = 0;

    while( !buttons.MiddlePressed() )
    {
        if( buttons.LeftPressed() )
        {
            value = 0;
            LCD.Write( "double" );
            while( buttons.LeftPressed() )
            {
                //nothing
            }
        }
        else if( buttons.RightPressed() )
        {
            value = 1;
            LCD.Write( "int" );
            while( buttons.RightPressed() )
            {
                //nothing
            }
        }

        Sleep(.10);
    }

    while( buttons.MiddlePressed() )
    {
        //nothing
    }

    return value;
}








