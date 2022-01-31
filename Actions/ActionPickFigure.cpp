#include "ActionPickFigure.h"
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <iostream>
#include <typeinfo>
#include "../Figures/CSquare.h"
#include "../Figures/CElps.h"
#include "../Figures/CHex.h"

ActionPickFigure::ActionPickFigure(ApplicationManager* pApp) :Action(pApp)
{}

void ActionPickFigure::Execute()
{
	int type = pManager->getAtypefromFigureList();
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Select all Squers ");
	Point point;
	int count;
	switch (type)
	{
	case 1:
		pGUI->PrintMessage("Select all Squers");
		count= CSquare::squarersNumber;
			
		break;

	case 2:
		pGUI->PrintMessage("Select all Elips");
		count = CElps::ElpsNumber;
		break;

	case 3:
		pGUI->PrintMessage(" Select all Hexa ");
		count = CHex::hexaNumber;
		break;
	
	}
	int correct = 0;
	int wrong = 0;
	while (count) {

		pGUI->GetPointClicked(point.x, point.y);
		if (!isValid(point))
		{
			point.x = 0;
			point.y = 0;
			(pManager->GetGUI())->PrintMessage("Invalid point, please select another action");
			return;
		}
		pManager->selectFigure(point.x, point.y);
		CFigure *fig= pManager->GetFigure(point.x, point.y);
		
		if (fig !=NULL) {

		if ((typeid(*fig) == typeid(CSquare)) && type==1 || (typeid(*fig) == typeid(CElps)) && type == 2 || (typeid(*fig) == typeid(CHex)) && type == 3) {
			correct++;
		}
		else {
			wrong++;
		}
		}
		else {
			wrong++;
		}
		pManager->DeleteSelectedItem();
		std::cout << --count << endl;
		pGUI->PrintMessage(" corect :"+ to_string(correct) + " wrong :" + to_string(wrong));
	}
	if (correct > wrong) {
		pGUI->PrintMessage(" congratulation you win");
	}else if (correct < wrong) {
		pGUI->PrintMessage("sorry you lose");
	}
	else {
		pGUI->PrintMessage("DRAW");
	}

}

