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
#include "Actions/ActionPickColor.h"
#include "Actions/ActionPickFig_Color.h"
#include "Actions/ActionResize.h"
#include"Actions/actionSelectFigure.h"
#include"Actions/ActionUndo.h"
#include "Figures/CSquare.h"
#include "Figures/CElps.h"
#include "Figures/CHex.h"
#include<iostream>
#include <fstream>
#include <Windows.h>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;

	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
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
	for (int i = 0; i < MaxFigCount; i++)
	{
		undoList[0][i] = FigList[i];
	}
	ActionType ActType;
	do
	{
		int x, y;
		//1- Read user action
		ActType = pGUI->MapInputToActionType(x, y);

		//2- Create the corresponding Action
		Action* pAct = CreateAction(ActType, x, y);

		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();
	} while (ActType != EXIT);

}

void ApplicationManager::reDrawBars() const {
	pGUI->CreateDrawToolBar();
	pGUI->CreateStatusBar();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType, int& x, int& y)
{
	Action* newAct = NULL;
	CFigure* temp;

	bool s = false, clear = true;
	bool resizeFlag = false;

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
		if (!s)
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
		if (!s)
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
			pGUI->PrintMessage("Do you want to save the figuers ? (Y = yes, N = no)");
			char choicing = pGUI->GetKeyPressed();
			if (choicing == 'Y' || choicing == 'y') {
				newAct = new ActionSave(this, false, false);//with loading => false //for playing => false
			}
			DeleteFigures();
		}


		break;

	case SAVE:
		newAct = new ActionSave(this, false, false);//with loading => false //for playing => false
		break;
	case LOAD:
		if (FigCount == 0) {
			pGUI->PrintMessage("load");
			newAct = new ActionLoad(this, false);
		}
		else {
			pGUI->PrintMessage("Do you want to save the figuers ? (Y = yes, N = no)");
			char choice = pGUI->GetKeyPressed();
			switch (choice) {
			case 'N':
			case 'n':
				pGUI->PrintMessage("load");
				newAct = new ActionLoad(this, false);
				break;
			case 'Y':
			case 'y':
				newAct = new ActionSave(this, true, false);//with loading => true //for playing => false
				break;
			}
		}
		///create AddLineAction here

		break;

	case DRAWING_AREA:
		newAct = new SelectFigureAction(this, x, y);
		break;
	case PLAYING_AREA:
		pGUI->PrintMessage("Playing Area");
		break;
	case TO_PLAY:
		if (FigCount != 0) {
			newAct = new ActionSave(this, false, true);//with loading => false //for playing => true
			pGUI->PrintMessage("Playing");
			pGUI->CreatePlayToolBar();
		}
		else {
			pGUI->PrintMessage("Draw figuers first");
		}
		break;

	case TO_DRAW:
		newAct = new ActionLoad(this, true);//with loading => false //for playing => true
		pGUI->CreateDrawToolBar();
		pGUI->PrintMessage("Drwaing");
		break;

	case PLAY_FIGUERS:	 //play with figuer type
		pGUI->PrintMessage("PLAY_FIGUERS");
		newAct = new ActionPickFigure(this);

		break;

	case PLAY_COLORS:	 // play with color type
		pGUI->PrintMessage("PLAY_COLORS");
		newAct = new ActionPickColor(this);
		break;

	case PLAY_FIG_COL: //play with figuer type and color 
		pGUI->PrintMessage("PLAY_FIG_COL");
		newAct = new ActionPickFig_Color(this);
		break;

	case RESIZE:
		pGUI->PrintMessage("You must select a figure first!");

		for (int i = 0; i < FigCount; i++)
		{
			resizeFlag = true;
			temp = FigList[i];
			if (temp->IsSelected()) {
				temp->changeFigureSize(pGUI);
				s = true;
				break;
			}
		}
		break;

	case UNDO:
		pGUI->PrintMessage("undo");
		//newAct = new ActionUndo(this);
		Undo();
		break;
	case REDO:
		pGUI->PrintMessage("redo");
		break;
	case STATUS:	//a click on the status bar ==> no action
		return NULL;
		break;
	}

	if (ActType != FIGURES && FigCount>0 && ActType != UNDO)
	{
		AddToUndoLIst();
	}
	//if (ActType == RESIZE||FigCount > 0  )
	//{
	//	AddToUndoLIst();
	//}
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
void ApplicationManager::ExecuteAction(Action*& pAct)
{
	//Execute the created action
	if (pAct != NULL)
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
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	
	CFigure* pFig;
	for (int i = 0; i < FigCount; i++) {
		pFig = FigList[i];
		if (pFig->IsSelected()) {
			return pFig;
		}

	}
	return NULL;

}
void ApplicationManager::selectFigure(int& x, int& y)
{
	CFigure* temp;
	int numberOfFiguresSelected = 0, previosFigure = 0;
	bool s = false, clear = true;
	if (FigCount == 0) {
		pGUI->PrintMessage("Please Draw figures first");
	}
	else {
		for (int i = 0; i < FigCount; i++)
		{
			temp = FigList[i];
			

			///- - - - - for multiple select - - -  -
			if (temp->InsideAFigure(x, y,pGUI) && (GetKeyState(VK_CONTROL) & 0x8000))
			{

				temp->SetSelected(true);
			}
			
			
			/// - - - - - Noraml Single Select ------------
			else if (temp->InsideAFigure(x,y,pGUI))
			{
				clear = false;
				numberOfFiguresSelected++;
				temp->IsSelected() ? pGUI->ClearStatusBar() : pGUI->PrintMessage(temp->getFigureName());
				s = temp->IsSelected();
				for (int j = 0; j < FigCount; j++)FigList[j]->SetSelected(false);
				s ? temp->SetSelected(false) : temp->SetSelected(true);
		     if (clear)
			{
				pGUI->ClearStatusBar();
			}
			if (numberOfFiguresSelected == 0)temp->SetSelected(false);
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
	int temp = FigCount;
	
	for (int i = 0; i < FigCount; i++) {


		if (FigList[i]->IsSelected()) {
			
			flag = true;
			delete 	FigList[i];

			FigList[i] = NULL;
			FigCount--;
			ShiftItem(i);
			i--;
			
		}
	}
	if (!flag) {
		pGUI->PrintMessage("You must select a figure first!");
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
int ApplicationManager::getAtypefromFigureList() {
	int i = rand() % FigCount;
	if (typeid(*FigList[i]) == typeid(CSquare)) {
		return 1;
	}
	else if (typeid(*FigList[i]) == typeid(CElps)) {
		return 2;
	}
	else if (typeid(*FigList[i]) == typeid(CHex)) {
		return 3;
	}

}
string ApplicationManager::getAcolorfromFigureList(int& count) {
	int fig = rand() % FigCount;
	if (FigList[fig]->IsFilled()) {
		for (int i = 0; i < FigCount; i++) {
			if (pGUI->ConvertColorToString(FigList[i]->GetFigureFillColor()) == pGUI->ConvertColorToString(FigList[fig]->GetFigureFillColor())) {
				count++;
			}
		}
		return  pGUI->ConvertColorToString(FigList[fig]->GetFigureFillColor());

	}
	else {
		for (int i = 0; i < FigCount; i++) {
			if (!FigList[i]->IsFilled()) {
				count++;
			}
		}
		return "NONE";

	}
}
string ApplicationManager::getAtypeWithAcolor(int& count, string& figColor) {
	int fig = rand() % FigCount;
	string type;

	if (typeid(*FigList[fig]) == typeid(CSquare)) {
		type = "Squers";
	}
	else if (typeid(*FigList[fig]) == typeid(CElps)) {
		type = "Elps";
	}
	else if (typeid(*FigList[fig]) == typeid(CHex)) {
		type = "Hexes";
	}
	if (FigList[fig]->IsFilled()) {
		figColor = pGUI->ConvertColorToString(FigList[fig]->GetFigureFillColor());
		for (int i = 0; i < FigCount; i++)
		{
			if ((typeid(*FigList[fig]) == typeid(*FigList[i])) && (pGUI->ConvertColorToString(FigList[i]->GetFigureFillColor()) == pGUI->ConvertColorToString(FigList[fig]->GetFigureFillColor()))) {
				count++;
			}
		}
	}
	else {
		figColor = "NONE";
		for (int i = 0; i < FigCount; i++) {
			if ((typeid(*FigList[fig]) == typeid(*FigList[i])) && (!FigList[i]->IsFilled())) {
				count++;
			}
		}
	}
	return type;
}

//==================================================================================//
//							      Undeo and redo functions   						//
//==================================================================================//

void ApplicationManager::AddToUndoLIst() {
	//CFigure* tempList[MaxFigCount];	//List of all figures (Array of pointers)

	for (int i = 0; i < FigCount; i++) {	
		 
		undoList[undoCount][i] = FigList[i];
	}

	//undoList[undoCount] = tempList;
	figCountList[undoCount] = FigCount;
	undoCount++;
	std::cout << "undoCount" << undoCount << endl;
	std::cout << "figcount" << FigCount << endl;
}

void ApplicationManager::Undo() {

	if (undoCount == 1) {
		pGUI->PrintMessage("UndoList Empty");
		FigCount = 0;
	}
	else {
		std::cout << "hamama" << endl;
		std::cout << " undo undoCount" << undoCount << endl;
		std::cout << " undo figcount" << FigCount << endl;
		/*for (int i = 0; i < 100; i++) {
			std::cout << "befor" <<undoList[i] << endl;
		}*/

		pGUI->PrintMessage("UndoList not Empty");
		//undoList[undoCount] = NULL;
		undoCount--;
		
			FigCount =	figCountList[undoCount];
		
			for (int i = 0; i < FigCount; i++) {

				FigList[i] = undoList[undoCount][i];
			}
		
		
	}

	pGUI->ClearDrawArea();
	UpdateInterface();

		std::cout << "undoCount from undo " << undoCount << endl;

	//pGUI->PrintMessage("Undo");

}




//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{

	for (int i = 0; i < FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)


}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI* ApplicationManager::GetGUI() const
{
	return pGUI;
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pGUI;

}
