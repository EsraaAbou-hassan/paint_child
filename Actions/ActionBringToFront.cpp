#include "ActionBringToFront.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>

ActionBringToFront::ActionBringToFront(ApplicationManager* pApp) : Action(pApp)
{}

//Execute the action
void ActionBringToFront::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	int selectedIndexFigure = pManager->GetSelectedIndexFigure();
	if (selectedIndexFigure > -1) {
		pManager->BringToFront(selectedIndexFigure);
		pGUI->PrintMessage("The shape was brought to Front");
	}
}