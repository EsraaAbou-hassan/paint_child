#include "ActionSendToBack.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>

ActionSendToBack::ActionSendToBack(ApplicationManager* pApp) : Action(pApp)
{}

//Execute the action
void ActionSendToBack::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	int selectedIndexFigure = pManager->GetSelectedIndexFigure();
	if (selectedIndexFigure > -1) {
		pManager->SendToBack(selectedIndexFigure);
		pGUI->PrintMessage("The shape was sent to Back");
	}
}