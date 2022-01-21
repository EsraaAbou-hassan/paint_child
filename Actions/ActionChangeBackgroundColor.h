#pragma once
#ifndef ACTION_CHANGE_BACKGROUND_COLOR_H
#define ACTION_CHANGE_BACKGROUND_COLOR_H

#include "Action.h"

//Add Ellipse Action class
class ActionChangeBackgroundColor : public Action
{
public:
    ActionChangeBackgroundColor(ApplicationManager* pApp);

    //ActionChangeFillColor
    virtual void Execute();

};

#endif