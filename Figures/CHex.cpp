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
	/*p1.x = TopLeftCorner.x;
	p1.y = TopLeftCorner.y;
	p2.x = TopLeftCorner.x + length;
	p2.y = TopLeftCorner.y + length;*/
	return 0;
}

string CHex::getFigureName() {
	return "Hexagon selected";
}