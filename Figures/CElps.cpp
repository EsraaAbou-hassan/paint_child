#include "CElps.h"

CElps::CElps(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
}


void CElps::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Elps on the screen	
	pGUI->DrawElps(TopLeftCorner, BottomRightCorner, FigGfxInfo, Selected);


}

int CElps::getFigureData(POINT& p1, POINT& p2)
{
	p1.x = TopLeftCorner.x;
	p1.y = TopLeftCorner.y;
	p2.x = BottomRightCorner.x;
	p2.y = BottomRightCorner.y;
	return BottomRightCorner.y - TopLeftCorner.y;
}

string CElps::getFigureName() {
	return "Elps selected";
}