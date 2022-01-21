
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
    //Get a Pointer to the Interface
    GUI* pGUI = pManager->GetGUI();
	pGUI->ClearDrawArea();
	CFigure* temp;
	/*bool check = temp->IsSelected();

		if(check==true){
			cout << "hhhhhh";
		}*/
		
		
	
}
