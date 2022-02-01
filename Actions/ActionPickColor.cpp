#include "ActionPickColor.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
#include <typeinfo>
#include "../Figures/CSquare.h"
#include "../Figures/CElps.h"
#include "../Figures/CHex.h"
#include "ActionLoad.h"

ActionPickColor::ActionPickColor(ApplicationManager* pApp) :Action(pApp)
{

}

void ActionPickColor::Execute()
{
	
		GUI* pGUI = pManager->GetGUI();
		Action* pAct = new ActionLoad(pManager, true);
		pAct->Execute();
		pManager->UpdateInterface();
		
		int count = 0;
		color chossenColor = pManager->getAcolorfromFigureList(count);
		string ColorMsg = pGUI->ConvertColorToString(chossenColor);
		pGUI->PrintMessage("Select all figuers with color :" + ColorMsg);
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
				if (pGUI->ConvertColorToString(fig->GetFigureFillColor()) == ColorMsg) {
					correct++;
				}
				else {
					wrong++;
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
		pGUI->PrintMessage(msg );
		
}
