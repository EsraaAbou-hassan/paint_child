#pragma once
#include "Action.h"
class ActionLoad : public Action
{
private:

public:
	ActionLoad(ApplicationManager* pApp);
	virtual void Execute();
	color ActionLoad::ConvertToColor(string s);

};

