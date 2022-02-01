#pragma once
#pragma once
#include "Action.h"
class ActionPickFig_Color : public Action
{
private:

public:
	ActionPickFig_Color(ApplicationManager* pApp);
	virtual void Execute();

};