#include"actionSelectFigure.h"


SelectFigureAction::SelectFigureAction(ApplicationManager* pApp,int _x,int _y) : Action(pApp)
{
	x = _x; y = _y;
}

void SelectFigureAction::Execute() {
	pManager->selectFigure(x,y);
}