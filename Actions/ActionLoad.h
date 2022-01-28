#pragma once
#include "Action.h"
class ActionLoad : public Action
{
private:

public:
	bool playing;
	ActionLoad(ApplicationManager* pApp,bool forPlaying);
	virtual void Execute();
	color ActionLoad::ConvertToColor(string s);
	void ActionLoad::loading(char file[100]);
};

