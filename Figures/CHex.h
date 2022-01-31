#ifndef CHEX_H
#define CHEX_H

#include "CFigure.h"

class CHex : public CFigure
{
private:
	Point center; 
	float rotation;
	int radius;
public:
	CHex(Point _center, float _rotation, int _radius, GfxInfo FigureGfxInfo);
	CHex();
	virtual void DrawMe(GUI* pOut) const;
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
	virtual void Load(ifstream& file);
	virtual void Save(ofstream& MyFile);
	void changeFigureSize(GUI* pGUI);
	bool InsideAFigure(int x, int y);
};

#endif#pragma once
