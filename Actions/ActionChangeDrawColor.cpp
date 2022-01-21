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

    ActionType ActType;
    pGUI->PrintMessage("Select a color");
    ActType = pGUI->MapInputToActionType();

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
    };

    pGUI->ClearStatusBar();
}