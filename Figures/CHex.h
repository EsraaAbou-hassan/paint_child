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
	virtual void DrawMe(GUI* pOut) const;
	virtual int getFigureData(POINT& p1, POINT& p2);
	virtual string getFigureName();

};

#endif#pragma once
