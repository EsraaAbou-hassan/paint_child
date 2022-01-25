
#include "ActionDeleteItem.h"

#include "..\Figures\CSquare.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

#include <iostream>
ActionDeleteItem::ActionDeleteItem(ApplicationManager* pApp) :Action(pApp)
{ 
}

//Execute the action
void ActionDeleteItem::Execute()
{
	pManager->DeleteSelectedItem();
	
}
