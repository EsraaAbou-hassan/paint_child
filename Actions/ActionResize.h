#pragma once
#include "Action.h"
class ActionRsize : public Action
{
private:

public:
	ActionRsize(ApplicationManager* pApp);
	virtual void Execute();

};