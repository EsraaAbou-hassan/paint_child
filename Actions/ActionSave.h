
#ifndef ACTION_SAVE_H
#define ACTION_SAVE_H

#include "Action.h"

//SAVE SQUARE Action class
class ActionSave : public Action
{
	string Filename;
public:
	bool loading;
	bool playing;
	ActionSave(ApplicationManager* pApp,bool withLoading, bool forPlay);

	//Save  to the ApplicationManager
	virtual void SaveFileName();
	virtual void Execute();


};

#endif