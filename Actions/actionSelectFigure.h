
#include "Action.h"
#include "..\ApplicationManager.h"

//select Action class
class SelectFigureAction : public Action
{
    int x, y;
public:
    SelectFigureAction(ApplicationManager* pApp, int _x, int _y);

    //delete  ApplicationManager
    virtual void Execute();

};

