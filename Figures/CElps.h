#ifndef CELPS_H
#define CELPS_H

#include "CFigure.h"

class CElps : public CFigure
{
private:
	Point TopLeftCorner;
	Point BottomRightCorner;
public:
	CElps(Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual int getFigureData(POINT& p1, POINT& p2);
	virtual string getFigureName();

};

#endif#pragma once
