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
	CElps();
	virtual void DrawMe(GUI* pOut) const;
	virtual int getFigureData(POINT& p1, POINT& p2);
	virtual string getFigureName();
	virtual void Load(ifstream& file);
	virtual void Save(ofstream& MyFile);


};

#endif#pragma once
