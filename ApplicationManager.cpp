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
#include "Actions/ActionPickFigure.h"
#include "Actions/ActionResize.h"
#include"Actions/actionSelectFigure.h"
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
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
	}	
	FigCount = 0;
}
void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{
		int x, y;
		//1- Read user action
		ActType = pGUI->MapInputToActionType(x,y);

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType,x,y);
		
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
Action* ApplicationManager::CreateAction(ActionType ActType,int &x,int &y) 
{
	Action* newAct = NULL;
	CFigure* temp;
	
	bool s = false, clear = true;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case FIGURES:
			pGUI->CreateFiguresToolBar();
			break;
		case DRAWING:
			pGUI->CreateDrawToolBar();
			break;
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
			if (FigCount != 0) {
				pGUI->PrintMessage("Do you want to save the figuers ? y for yes");
				char choicing = pGUI->GetKeyPressed();
				if(choicing =='Y'||choicing=='y') {
					newAct = new ActionSave(this, false, false);//with loading => false //for playing => false
				}
				DeleteFigures();
			}
			
			
			break;

		case SAVE:
			newAct = new ActionSave(this,false,false);//with loading => false //for playing => false
			break;
		case LOAD:
			if (FigCount == 0) {
				pGUI->PrintMessage("load");
				newAct = new ActionLoad(this,false);
			}
			else {
				pGUI->PrintMessage("Do you want to save the figuers ? y:n");
				char choice = pGUI->GetKeyPressed();
				switch (choice) {
				case 'N':
				case 'n':
					pGUI->PrintMessage("load");
					newAct = new ActionLoad(this,false);
					break;
				case 'Y':
				case 'y':
					newAct = new ActionSave(this,true,false);//with loading => true //for playing => false
					break;
				}
			}
			///create AddLineAction here

			break;

		case DRAWING_AREA:
			newAct = new SelectFigureAction(this,x,y);
			break;
		case PLAYING_AREA:
			pGUI->PrintMessage("playing Area");
			break;
		case TO_PLAY:
			if (FigCount != 0) {
				newAct = new ActionSave(this, false, true);//with loading => false //for playing => true
				pGUI->PrintMessage("playing");
				pGUI->CreatePlayToolBar();
			}
			else {
				pGUI->PrintMessage("draw figuers first");

			}

			

			break;

		case TO_DRAW:
			newAct = new ActionLoad(this,true);//with loading => false //for playing => true
			pGUI->CreateDrawToolBar();
			pGUI->PrintMessage("drwaing");
			break;

		case PLAY_FIGUERS :	 //play with figuer type
			pGUI->PrintMessage("PLAY_FIGUERS");
			newAct = new ActionPickFigure(this);

			break;

		case PLAY_COLORS:	 // play with color type
			pGUI->PrintMessage("PLAY_COLORS");

			break;

		case PLAY_FIG_COL: //play with figuer type and color 
			pGUI->PrintMessage("PLAY_FIG_COL");
			break;

		case RESIZE:
			for (int i = 0; i < FigCount; i++)
			{
				temp = FigList[i];
				if (temp->IsSelected()) {
					temp->changeFigureSize(pGUI);
					s = true;
					break;
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
void ApplicationManager::selectFigure(int& x, int& y)
{
	CFigure* temp;
	POINT p1, p2;
	int numberOfFiguresSelected = 0, previosFigure = 0;
	int length;
	bool s = false, clear = true;
	string figureName;
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
				clear = false;
				s = temp->IsSelected();
				numberOfFiguresSelected++;
				figureName = temp->getFigureName();
				s ? pGUI->ClearStatusBar() : pGUI->PrintMessage(figureName);
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
		clear ? pGUI->ClearStatusBar() : true;
	}
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
	bool flag = false;
	for (int i = 0; i < FigCount; i++) {


		if (FigList[i]->IsSelected()) {
			flag = true;
			delete 	FigList[i];

			FigList[i] = NULL;
			ShiftItem(i);
			FigCount--;
		}
	}
	if (!flag) {
		pGUI->PrintMessage("you must select  an item first");
	}
	else {
		pGUI->PrintMessage("Selected figuer Deleted");
		pGUI->ClearDrawArea();
		UpdateInterface();
	}
	

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
