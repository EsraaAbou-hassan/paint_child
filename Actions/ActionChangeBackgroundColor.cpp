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

    ActionType ActType;
    pGUI->PrintMessage("Select a Background color");
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
    };

    pGUI->ClearDrawArea();
    pGUI->ClearStatusBar();
}