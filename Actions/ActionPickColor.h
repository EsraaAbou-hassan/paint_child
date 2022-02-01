#pragma once
#include "Action.h"
class ActionPickColor : public Action
{
private:

public:
	ActionPickColor(ApplicationManager* pApp);
	virtual void Execute();

};