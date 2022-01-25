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
	virtual int getFigureData(POINT& p1, POINT& p2);
	virtual string getFigureName();
	virtual void Load(ifstream& file);
	virtual void Save(ofstream& MyFile);

};

#endif#pragma once
