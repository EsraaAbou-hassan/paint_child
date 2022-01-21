#ifndef ACTION_ADD_HEX_H
#define ACTION_ADD_HEX_H

#include "Action.h"

//Add Hex Action class
class ActionAddHex : public Action
{
public:
	ActionAddHex(ApplicationManager* pApp);

	//Add Hex to the ApplicationManager
	virtual void Execute();

};

#endif#pragma once
#pragma once
