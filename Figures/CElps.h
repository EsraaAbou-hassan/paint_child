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
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
	virtual void Load(ifstream& file);
	virtual void Save(ofstream& MyFile);
	void changeFigureSize(GUI* pGUI);
	bool InsideAFigure(int x, int y);

};

#endif#pragma once
