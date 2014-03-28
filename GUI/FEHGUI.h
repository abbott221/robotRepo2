#ifndef FEHGUI_H
#define FEHGUI_H


#include "main.h"


typedef enum
{
    tString = 0,
    tInt,
    tFloat,
    tDouble,
    tVoid
} TypeEnum;

typedef enum
{
    STRAIGHT = 0,
    LEFT,
    RIGHT,
    BACKWARDS,
    STOP
} PMode;




class movement
{
    public:
        movement();

        //dataType is set by the following four methods
        void setMovement(int dOperation, int dValue);
        void setMovement(int dOperation, float dValue);
        void setMovement(int dOperation, double dValue);
        void setMovement(int dOperation);
        //***move.setMove(otherMove)
        void setMovement(movement otherMove);
        void setState(bool state);

        int getOperation();
        TypeEnum getDataType();
        int getIntValue();
        float getFloatValue();
        double getDoubleValue();
        //no get void type
        bool getState();

    private:
        int operation;
        TypeEnum dataType;
        int intValue;
        float floatValue;
        double doubleValue;
        //no voidValue
        bool movementState;
};


//this could probably just be passed off as a struct?
class robot
{
    public:
        robot();

        int currentMove;
        //int currentMove = 0;
        movement * moreMoves;
        //movement moreMoves[144];
};



class option
{
    public:
        option();

        //setters
        //dataType is set automatically by the following 2 methods
        void setOption(int dLine, const char *dName);
        void setOption(int dLine, movement dOptionMovement);
        void setOption(option dOption);
        void setState(bool state);

        //getters
        TypeEnum getDataType();
        int getLine();
        const char * getName();
        movement getMovement();
        bool getState();

        void display();

    private:
        TypeEnum dataType;
        int line;
        const char * name;
        movement optionMovement;
        bool optionState;
};



class menu
{
    public:
        menu();
        void addOption(const char * dLine);
        void addOption(movement dMovement);

        int UserInterface();
        void drawCursor(int pixHeight);

        int pageAndMoveInterface(movement moreMoves[]);
        int pageInterface();
        int moveTypeInterface();
        int moveInterface(movement moves[]);

        option * selection;

    private:
        int selectionSize;
};






class RPScleaner
{
    public:
        RPScleaner();

        //set initial move values
        void initiateMoveData();
        //set current values
        //stalls out after x time?
        //continues to scan until values aren't 0,0,0
        //SETTER method
        void update();

        //DO INTERNAL CALLS NEED [THIS.]METHOD();???

        //called internally, avoid externally
        //checks for 0,0,0
        bool currentValuesAreLegit();

        //sets X displacement
        void compareX(float supposedValue);
        //sets Y displacement
        void compareY(float supposedValue);
        //sets Angle displacement
        void compareAngle(float supposedValue);



        float getInitX();
        float getInitY();
        float getInitAngle();

        float getCurrentX();
        float getCurrentY();
        float getCurrentAngle();

        float getDisplacementX();
        float getDisplacementY();
        float getDisplacementAngle();


    private:
        float initX;
        float initY;
        float initAngle;

        float currentX;
        float currentY;
        float currentAngle;

        float displacementX;
        float displacementY;
        float displacementAngle;
};




extern RPScleaner cleaner;



extern int mainChoice;
extern menu mainMenu;

extern int pageChoice;
extern menu pageMenu;

extern int configureChoice;
extern menu configureMenu;

extern int operationChoice;
extern menu operationMenu;



extern robot chet;
extern PMode currentPowerMode;





#endif // FEHGUI_H
