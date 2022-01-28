#include "ActionChangeDrawColor.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>

ActionChangeDrawColor::ActionChangeDrawColor(ApplicationManager* pApp) : Action(pApp)
{}

//Execute the action
void ActionChangeDrawColor::Execute()
{

    GUI* pGUI = pManager->GetGUI();
    int x, y;
    ActionType ActType;
    pGUI->PrintMessage("Select a color");
    pGUI->CreateColorToolBar();
    ActType = pGUI->MapInputToActionType(x,y);
    switch (ActType) {
    case SELECT_COLOR_CYAN:
        pGUI->setCrntDrawColor(CYAN);
        break;
    case SELECT_COLOR_GREEN:
        pGUI->setCrntDrawColor(GREEN);
        break;
   case SELECT_COLOR_RED:
        pGUI->setCrntDrawColor(RED);
        break;
   case SELECT_COLOR_BLACK:
       pGUI->setCrntDrawColor(BLACK);
       break;
   case SELECT_COLOR_YELLOW:
       pGUI->setCrntDrawColor(YELLOW);
       break;
   case SELECT_COLOR_BLUE:
       pGUI->setCrntDrawColor(BLUE);
       break;
   case SELECT_COLOR_PINK:
       pGUI->setCrntDrawColor(PINK);
       break;
   case SELECT_COLOR_BROWN:
       pGUI->setCrntDrawColor(BROWN);
       break;
   case SELECT_COLOR_ORANGE:
       pGUI->setCrntDrawColor(ORANGE);
       break;
       
    };

    pGUI->ClearStatusBar();
    pGUI->CreateDrawToolBar();
}