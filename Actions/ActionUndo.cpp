#include "ActionUndo.h"
#include "../ApplicationManager.h"
ActionUndo::ActionUndo(ApplicationManager* pApp):Action(pApp)
{
}

void ActionUndo::Execute()
{
	pManager->Undo();
}
