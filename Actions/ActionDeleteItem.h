#pragma once

#ifndef ACTION_DELETE_ITEM_H
#define ACTION_DELETE_ITEM_H

#include "Action.h"

//delete Action class
class ActionDeleteItem : public Action
{
public:
    ActionDeleteItem(ApplicationManager* pApp);

    //delete  ApplicationManager
    virtual void Execute();

};

#endif#pragma once
