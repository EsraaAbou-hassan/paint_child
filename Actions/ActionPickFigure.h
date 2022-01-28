#pragma once
#include "Action.h"
class ActionPickFigure : public Action
{
private:

public:
	ActionPickFigure(ApplicationManager* pApp);
	virtual void Execute();
	
};