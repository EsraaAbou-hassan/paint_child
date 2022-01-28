
#ifndef ACTION_SAVE_H
#define ACTION_SAVE_H

#include "Action.h"

//SAVE SQUARE Action class
class ActionSave : public Action
{
public:
	bool loading;
	bool playing;
	ActionSave(ApplicationManager* pApp,bool withLoading, bool forPlay);

	//Save  to the ApplicationManager
	virtual void Execute();


};

#endif