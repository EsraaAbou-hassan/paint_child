#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include "Actions\ActionAddElps.h"
#include "Actions\ActionAddHex.h"
#include "Actions\ActionChangeDrawColor.h"
#include "Actions\ActionChangeFillColor.h"
#include "Actions\ActionChangeBackgroundColor.h"
#include "Actions\ActionDeleteItem.h"
#include "Actions\ActionLoad.h"
#include "Actions\ActionSave.h"
#include "Actions/ActionSendToBack.h"
#include "Actions/ActionBringToFront.h"
#include<iostream>
#include <fstream>

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
void ApplicationManager::DeleteFigures() {
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	FigCount = 0;
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

void ApplicationManager::reDrawBars() const{
	pGUI->CreateDrawToolBar();
	pGUI->CreateStatusBar();
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
			break;

		case SEND_BACK:
			newAct = new ActionSendToBack(this);
			break;
		case BRNG_FRNT:
			newAct = new ActionBringToFront(this);
			break;

		case EXIT:
			///create ExitAction here
			
			break;

		case SAVE:
			newAct = new ActionSave(this,false);
			break;
		case LOAD:
			if (FigCount == 0) {
				pGUI->PrintMessage("load");
				newAct = new ActionLoad(this);
			}
			else {
				pGUI->PrintMessage("Do you want to save the figuers ? y:n");
				char choice = pGUI->GetKeyPressed();
				switch (choice) {
				case 'N':
				case 'n':
					pGUI->PrintMessage("load");
					newAct = new ActionLoad(this);
					break;
				case 'Y':
				case 'y':
					newAct = new ActionSave(this,true);//with loading => true
					break;
				}
			}
			///create AddLineAction here

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
		case TO_PLAY:
			if (FigCount != 0) {
				//save figuers
				//figuerflag =1
			}
			pGUI->PrintMessage("playing");
			pGUI->CreatePlayToolBar();
			break;

		case TO_DRAW:
			//if figuerflag ==1
			//load figuers
			pGUI->CreateDrawToolBar();
			pGUI->PrintMessage("drwaing");
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
	UpdateInterface();
}

void ApplicationManager::BringToFront(int selectedIndex) {
	CFigure* SelectedFigure = FigList[selectedIndex];
	for (int i = selectedIndex; i < FigCount - 1; i++)
		FigList[i] = FigList[i + 1];

	FigList[FigCount - 1] = SelectedFigure;
	UpdateInterface();
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
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SaveAll(ofstream& MyFile)
{

	MyFile << to_string(FigCount) << endl;

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(MyFile);
	}

}
//Delete a figure to the list of figures
void ApplicationManager::DeleteSelectedItem() {

	for (int i = 0; i < FigCount; i++) {


		if (FigList[i]->IsSelected()) {

			delete 	FigList[i];
			FigList[i] = NULL;
			ShiftItem(i);
			FigCount--;

		}
		else {
			pGUI->PrintMessage("you must selected item first");
		}

	}
	pGUI->PrintMessage("Selected figuer Deleted");
	pGUI->ClearDrawArea();
	UpdateInterface();

}
void ApplicationManager::ShiftItem(int figure) {

	for (int i = figure; i < FigCount; i++) {
		FigList[i] = FigList[i + 1];
	}


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
