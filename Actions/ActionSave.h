
#ifndef ACTION_SAVE_H
#define ACTION_SAVE_H

#include "Action.h"

//SAVE SQUARE Action class
class ActionSave : public Action
{
public:
	bool loading;
	ActionSave(ApplicationManager* pApp,bool withLoading);

	//Save  to the ApplicationManager
	virtual void Execute();


};

#endif