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
    ActType = pGUI->MapInputToActionType();
    UI.isFilled = true;

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
    };

    pGUI->ClearStatusBar();
}