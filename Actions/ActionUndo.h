#pragma once
#include "Action.h"
class ActionUndo : public Action
{
private:

public:
	ActionUndo(ApplicationManager* pApp);
	virtual void Execute();

};
