#pragma once
#ifndef ACTION_CHANGE_FILL_COLOR_H
#define ACTION_CHANGE_FILL_COLOR_H

#include "Action.h"

//Add Ellipse Action class
class ActionChangeFillColor : public Action
{
public:
    ActionChangeFillColor(ApplicationManager* pApp);

    //ActionChangeFillColor
    virtual void Execute();

};

#endif