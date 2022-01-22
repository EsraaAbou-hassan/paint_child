#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"
#include "..\GUI\UI_Info.h"

class ApplicationManager; //forward class declaration


//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job

public:

	Action(ApplicationManager *pApp) { pManager = pApp; }	//constructor

	//Execute action (code depends on action type)
	virtual void Execute() =0;
	

	protected: bool isValid(Point P) //utility function to check if point is inside drawing area
	{
		if (P.x > UI.width || P.x < 0)
			return false;
		if (P.y > (UI.height - UI.StatusBarHeight) || P.y < UI.ToolBarHeight)
			return false;
		return true;
	}
	//To undo this action (code depends on action type)
	//virtual void Undo()=0;

	//To redo this action (code depends on action type)
	//virtual void Redo()=0;

};

#endif