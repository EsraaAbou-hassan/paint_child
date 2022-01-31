#include "ActionPickFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>
#include <typeinfo>
#include "../Figures/CSquare.h"

ActionPickFigure::ActionPickFigure(ApplicationManager* pApp) :Action(pApp)
{}

void ActionPickFigure::Execute()
{
	//int type = rand()%3; //return 0,1,2
	//std::cout << type;
	GUI* pGUI = pManager->GetGUI();
	//

	//switch (type)
	//{
	//case 0:
	//	pGUI->PrintMessage("Select all Squers ");
	//	
	//		
	//	break;

	//case 1:
	//	pGUI->PrintMessage("Select all Elips");
	//	break;

	//case 2:
	//	pGUI->PrintMessage(" Select all Hexa ");
	//	break;
	//
	//}
	Point point;
	CSquare *s = new CSquare();
	while (s->squarersNumber) {

	pGUI->GetPointClicked(point.x, point.y);
	if (!isValid(point))
	{
		point.x = 0;
		point.y = 0;
		(pManager->GetGUI())->PrintMessage("Invalid point, please select another action");
		return;
	}
	pManager->selectFigure(point.x, point.y);
	pManager->DeleteSelectedItem();
	std::cout << --s->squarersNumber;
	}


}

