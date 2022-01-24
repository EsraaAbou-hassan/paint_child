#include "ActionChangeBackgroundColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>

ActionChangeBackgroundColor::ActionChangeBackgroundColor(ApplicationManager* pApp) : Action(pApp)
{}

//Execute the action
void ActionChangeBackgroundColor::Execute()
{

    GUI* pGUI = pManager->GetGUI();
    //pGUI->CreateColorToolBar();
    ActionType ActType;
    pGUI->PrintMessage("Select a Background color");
    pGUI->CreateColorToolBar();
    ActType = pGUI->MapInputToActionType();
    
    switch (ActType) {
    case SELECT_COLOR_CYAN:
        pGUI->setCrntBackgroundColor(CYAN);
        break;
    case SELECT_COLOR_GREEN:
        pGUI->setCrntBackgroundColor(GREEN);
        break;
    case SELECT_COLOR_RED:
        pGUI->setCrntBackgroundColor(RED);
        break;
    case SELECT_COLOR_BLACK:
        pGUI->setCrntBackgroundColor(BLACK);
        break;
    case SELECT_COLOR_YELLOW:
        pGUI->setCrntBackgroundColor(YELLOW);
        break;
    case SELECT_COLOR_BLUE:
        pGUI->setCrntBackgroundColor(BLUE);
        break;
    case SELECT_COLOR_PINK:
        pGUI->setCrntBackgroundColor(PINK);
        break;
    case SELECT_COLOR_BROWN:
        pGUI->setCrntBackgroundColor(BROWN);
        break;
    case SELECT_COLOR_ORANGE:
        pGUI->setCrntBackgroundColor(ORANGE);
        break;

     
    };

    pGUI->ClearDrawArea();
    pGUI->ClearStatusBar();
    pGUI->CreateDrawToolBar();
}