#include "ActionPickFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>
#include <typeinfo>

ActionPickFigure::ActionPickFigure(ApplicationManager* pApp) :Action(pApp)
{}

void ActionPickFigure::Execute()
{
	int type = rand()%3; //return 0,1,2
	std::cout << type;
	GUI* pGUI = pManager->GetGUI();
	

	if (type == 0) {

	}
	switch (type)
	{
	case 0:
		pGUI->PrintMessage("Select all Squers ");

		break;

	case 1:
		pGUI->PrintMessage("Select all Elips");
		break;

	case 2:
		pGUI->PrintMessage(" Select all Hexa ");
		break;
	
	}


}

