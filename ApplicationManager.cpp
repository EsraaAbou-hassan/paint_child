#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddElps.h"
#include "Actions\ActionAddHex.h"
#include "Actions\ActionChangeDrawColor.h"
#include "Actions\ActionChangeFillColor.h"
#include "Actions\ActionChangeBackgroundColor.h"
#include "Actions\ActionDeleteItem.h"
#include "Actions/ActionSendToBack.h"
#include "Actions/ActionBringToFront.h"
#include<iostream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	int x, y;
	CFigure* temp;
	POINT p1, p2;
	int numberOfFiguresSelected = 0, previosFigure = 0;
	int length;
	bool s=false;
	string figureName;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS:
			///create ELPS here
			newAct = new ActionAddElps(this);
			break;

		case DRAW_HEX:
			///create HEX here
			newAct = new ActionAddHex(this);
			break;

		case CHNG_DRAW_CLR:
			for (int i = 0; i < FigCount; i++)
			{
				temp = FigList[i];
				if (temp->IsSelected()) {
					temp->changeFigureDrawClr(pGUI);
					s = true;
					break;
				}
			}
			if(!s)
			newAct = new ActionChangeDrawColor(this);
			break;

		case CHNG_FILL_CLR:
			for (int i = 0; i < FigCount; i++)
			{
				temp = FigList[i];
				if (temp->IsSelected()) {
					temp->changeFigureFillClr(pGUI);
					s = true;
					break;
				}
			}
			if(!s)
				newAct = new ActionChangeFillColor(this);
			break;

		case CHNG_BK_CLR:
			newAct = new ActionChangeBackgroundColor(this);
			break;

		case DEL:
			newAct = new ActionDeleteItem(this);
		
		case SEND_BACK:
			newAct = new ActionSendToBack(this);
			break;
		case BRNG_FRNT:
			newAct = new ActionBringToFront(this);
			break;

		case EXIT:
			///create ExitAction here
			
			break;
		
		case DRAWING_AREA:
			pGUI->GetPointClicked(x, y);
			if (FigCount == 0) {
				pGUI->PrintMessage("no figures drawing");
			}
			else {
				for (int i = 0; i < FigCount; i++)
				{
					temp = FigList[i];
					length = temp->getFigureData(p1, p2);

					if (x >= p1.x && x <= p2.x && y >= p1.y && y <= p2.y)
					{
						s = temp->IsSelected();
						numberOfFiguresSelected++;
						figureName = temp->getFigureName();
						s ? pGUI->CreateStatusBar() : pGUI->PrintMessage(figureName);
						s ? temp->SetSelected(false) : temp->SetSelected(true);
					}
					else {
						//s? pGUI->PrintMessage(figureName):pGUI->PrintMessage("drawing area");
						temp->SetSelected(false);
					}
					if (numberOfFiguresSelected == 1 && previosFigure == 0) {
						previosFigure = i;
					}
					else if (numberOfFiguresSelected > 1) {
						CFigure* t = FigList[previosFigure];
						t->SetSelected(false);
						previosFigure = i;
					}
				}
			}
			break;
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////

int ApplicationManager::GetSelectedIndexFigure() {
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i] != NULL) {
			if (FigList[i]->IsSelected())
				return i;
		}
	}
	return -1;
}

void ApplicationManager::SendToBack(int selectedIndex) {
	CFigure* SelectedFigure = FigList[selectedIndex];
	for (int i = selectedIndex; i > 0; i--)
		FigList[i] = FigList[i - 1];

	FigList[0] = SelectedFigure;
}

void ApplicationManager::BringToFront(int selectedIndex) {
	CFigure* SelectedFigure = FigList[selectedIndex];
	for (int i = selectedIndex; i < FigCount - 1; i++)
		FigList[i] = FigList[i + 1];

	FigList[FigCount - 1] = SelectedFigure;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	
	CFigure* pFig;
	for (int i = 0; i < FigCount; i++) {
		pFig = FigList[i];
		pFig->SetSelected(true);

	}
	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
