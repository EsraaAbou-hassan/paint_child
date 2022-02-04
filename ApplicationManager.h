#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* undoList[100][200] = {NULL};
	
	int figCountList[100];
	int undoCount=1;
	//CFigure** redoList[100] = {NULL};
	//int redoCount=0;
	//Pointers to Input and Output classes
	GUI* pGUI;
	

public:	

	ApplicationManager(); 
	~ApplicationManager();

	void Run();		//to run the application
	void reDrawBars() const;
	// -- Action-Related Functions
	Action* CreateAction(ActionType, int& x, int& y);
	int GetSelectedIndexFigure();
	void BringToFront(int selectedIndex);
	void SendToBack(int selectedIndex);
	void ExecuteAction(Action*&) ; //Execute an action
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	
	void selectFigure(int& x, int& y);
	void SaveAll(ofstream& MyFile);//Save all figures in figure list
	int getAtypefromFigureList();
	string getAcolorfromFigureList(int& count);
	string getAtypeWithAcolor(int & count,string & figColor );
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window	
	void DeleteFigures(); //remove all figures from array
	void DeleteSelectedItem() ; //remove selected figuer
	void ShiftItem(int figure) ;  //shift other figuer un the array
	void AddToUndoLIst();
	void Undo();
};

#endif