#pragma once
#ifndef ACTION_CHANGE_DRAW_COLOR_H
#define ACTION_CHANGE_DRAW_COLOR_H

#include "Action.h"

//Add Ellipse Action class
class ActionChangeDrawColor : public Action
{
public:
    ActionChangeDrawColor(ApplicationManager* pApp);

    //ActionChangeFillColor
    virtual void Execute();

};

#endif