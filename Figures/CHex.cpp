#include "CHex.h"
#include "HexaStruct.h"

CHex::CHex(Point _center, float _rotation, int _radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = _center;
	rotation = _rotation;
	radius = _radius;
}


void CHex::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Hex on the screen	
	pGUI->DrawHexagon(center, rotation, radius, FigGfxInfo, Selected);
}



int CHex::getFigureData(POINT& p1, POINT& p2)
{
	p1.x = center.x - radius;
	p1.y = center.y - radius;
	p2.x = center.x + radius;
	p2.y = center.y + radius;
	return -1;
}

string CHex::getFigureName() {
	return "Hexagon selected";
}