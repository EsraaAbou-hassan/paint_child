#include "ActionAddElps.h"
#include "..\Figures\CElps.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddElps::ActionAddElps(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddElps::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo SqrGfxInfo;
	SqrGfxInfo.isFilled = pGUI->getCrntIsFilled();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
	SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Elps data from the user

	pGUI->PrintMessage("New Elps: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	if (!isValid(P1))
	{
		P1.x = 0;
		P1.y = 0;
		P2.x = 0;
		P2.y = 0;
		(pManager->GetGUI())->PrintMessage("Invalid point, please select another action");
		return;
	}

	pGUI->PrintMessage("New Elps: Click at second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	while (P2.x == P1.x || P2.y == P1.y)
	{
		(pManager->GetGUI())->PrintMessage("Invalid point, please select another point");
		pGUI->GetPointClicked(P2.x, P2.y);
	}
	if (!isValid(P2))
	{
		P1.x = 0;
		P1.y = 0;
		P2.x = 0;
		P2.y = 0;
		(pManager->GetGUI())->PrintMessage("Invalid point, please select another action");
		return;
	}

	pGUI->ClearStatusBar();


	//Step 2 - prepare elps data
	//User has entered two points P1&P2
	//2.1- Identify the Top left corner of the elps
	Point topLeft;
	topLeft.x = P1.x < P2.x ? P1.x : P2.x;
	topLeft.y = P1.y < P2.y ? P1.y : P2.y;
	Point bottomRight;
	bottomRight.x = P1.x > P2.x ? P1.x : P2.x;
	bottomRight.y = P1.y > P2.y ? P1.y : P2.y;

	//Step 3 - Create a Elps with the parameters read from the user
	CElps* R = new CElps(topLeft, bottomRight, SqrGfxInfo);

	//Step 4 - Add the Elps to the list of figures
	pManager->AddFigure(R);
}
