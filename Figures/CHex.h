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
	static int hexaNumber;
	CHex(Point _center, float _rotation, int _radius, GfxInfo FigureGfxInfo);
	CHex();
	virtual void DrawMe(GUI* pOut) const;
	int getFigureData(POINT& p1, POINT& p2);
	string getFigureName();
	virtual void Load(ifstream& file);
	virtual void Save(ofstream& MyFile);
	void changeFigureSize(GUI* pGUI);
	// Given three collinear points p, q, r, the function checks if
	// point q lies on line segment 'pr'
	bool onSegment(Point p, Point q, Point r);
	// To find orientation of ordered triplet (p, q, r).
	// The function returns following values
	// 0 --> p, q and r are collinear
	// 1 --> Clockwise
	// 2 --> Counterclockwise
	int orientation(Point p, Point q, Point r);

	// The function that returns true if line segment 'p1q1'
	// and 'p2q2' intersect.
	bool doIntersect(Point p1, Point q1, Point p2, Point q2);
	bool isInside(Point polygon[], int n, Point p);
	bool InsideAFigure(int x, int y, GUI* pGUI);
};

#endif#pragma once
