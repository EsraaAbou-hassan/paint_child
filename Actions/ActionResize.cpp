#include "ActionResize.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>

ActionRsize::ActionRsize(ApplicationManager* pApp) : Action(pApp)
{}

void ActionRsize::Execute()
{
    GUI* pGUI = pManager->GetGUI();
    int x, y;
    ActionType ActType;
    pGUI->PrintMessage("resize");
    pGUI->CreateResizeToolBar();
    ActType = pGUI->MapInputToActionType(x,y);
    switch (ActType) {

    case RESIZE_4:
        pGUI->PrintMessage("resize 4");
        break;
    case RESIZE_2:
        pGUI->PrintMessage("resize 2");
        break;
    case RESIZE_0_5:
        pGUI->PrintMessage("resize 0.5");
        break;
    case RESIZE_0_25:
        pGUI->PrintMessage("resize 0.25");
        break;

    };

    pGUI->ClearStatusBar();
    pGUI->CreateDrawToolBar();
}
