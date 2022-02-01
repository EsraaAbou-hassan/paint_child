#include "ActionPickFig_Color.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
#include <typeinfo>
#include "../Figures/CSquare.h"
#include "../Figures/CElps.h"
#include "../Figures/CHex.h"
#include "ActionLoad.h"
ActionPickFig_Color::ActionPickFig_Color(ApplicationManager* pApp):Action(pApp)
{
}

void ActionPickFig_Color::Execute()
{

	GUI* pGUI = pManager->GetGUI();
	Action* pAct = new ActionLoad(pManager, true);
	pAct->Execute();
	pManager->UpdateInterface();

	int count = 0;
	string ColorMsg ="";
	string type = pManager->getAtypeWithAcolor(count, ColorMsg);
	pGUI->PrintMessage("Select all "+ type +" that Filled with " + ColorMsg + " color ");
	Point point;
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
		CFigure* fig = pManager->GetFigure(point.x, point.y);
		if (fig == NULL) {
			wrong++;
		}
		else {
			if (ColorMsg == "NONE") {
				if (((typeid(*fig) == typeid(CSquare)) && type == "Squers" || (typeid(*fig) == typeid(CElps)) && type == "Elps" || (typeid(*fig) == typeid(CHex)) && type == "Hexes") && (!fig->IsFilled())) {
					correct++;
				}
				else {
					wrong++;
				}
			}
			else {
				if (((typeid(*fig) == typeid(CSquare)) && type == "Squers" || (typeid(*fig) == typeid(CElps)) && type == "Elps" || (typeid(*fig) == typeid(CHex)) && type == "Hexes") && (pGUI->ConvertColorToString(fig->GetFigureFillColor()) == ColorMsg)) {
					correct++;
				}
				else {
					wrong++;
				}
			}

		}
		pManager->DeleteSelectedItem();
		--count;
		pGUI->PrintMessage(" corect :" + to_string(correct) + " wrong :" + to_string(wrong));
	}
	string msg;
	if (correct > wrong) {
		msg = " congratulation you win";
	}
	else if (correct < wrong) {
		msg = "sorry you lose";
	}
	else {
		msg = "DRAW";
	}
	pGUI->PrintMessage(msg);
}

