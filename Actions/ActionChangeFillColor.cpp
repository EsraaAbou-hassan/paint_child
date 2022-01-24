#include "ActionChangeFillColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>

ActionChangeFillColor::ActionChangeFillColor(ApplicationManager* pApp) : Action(pApp)
{}

//Execute the action
void ActionChangeFillColor::Execute()
{

    GUI* pGUI = pManager->GetGUI();

    ActionType ActType;
    pGUI->PrintMessage("Select a color");
    pGUI->CreateColorToolBar();
    ActType = pGUI->MapInputToActionType();

    switch (ActType) {
    case SELECT_COLOR_CYAN:
        pGUI->setCrntFillColor(CYAN);
        break;
    case SELECT_COLOR_GREEN:
        pGUI->setCrntFillColor(GREEN);
   
        break;
        
    case SELECT_COLOR_RED:
        pGUI->setCrntFillColor(RED);
        break;
    case SELECT_COLOR_BLACK:
        pGUI->setCrntFillColor(BLACK);
        break;
    case SELECT_COLOR_YELLOW:
        pGUI->setCrntFillColor(YELLOW);
        break;
    case SELECT_COLOR_BLUE:
        pGUI->setCrntFillColor(BLUE);
        break;
    case SELECT_COLOR_PINK:
        pGUI->setCrntFillColor(PINK);
        break;
    case SELECT_COLOR_BROWN:
        pGUI->setCrntFillColor(BROWN);
        break;
    case SELECT_COLOR_ORANGE:
        pGUI->setCrntFillColor(ORANGE);
        break;
        
    };

    pGUI->ClearStatusBar();
    pGUI->CreateDrawToolBar();
}