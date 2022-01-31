#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
	
public:
	static int squarersNumber;
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	CSquare::CSquare();
	virtual void DrawMe(GUI* pOut) const;
	virtual int getFigureData(POINT& p1, POINT& p2);
	virtual string getFigureName();
	virtual void changeFigureSize(GUI* pGUI);
	virtual void Load(ifstream& file);
	virtual void Save(ofstream& MyFile);

	bool InsideAFigure(int x, int y);

};

#endif