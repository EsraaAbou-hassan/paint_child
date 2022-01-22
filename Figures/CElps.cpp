#include "CElps.h"
#include <fstream>
#include <iostream>

CElps::CElps(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
}
CElps::CElps() {}

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
void CElps::Load(ifstream& file)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface

	file >> ID >> TopLeftCorner.x >> TopLeftCorner.y >> BottomRightCorner.x >> BottomRightCorner.y;
	std::cout << TopLeftCorner.x << " " << TopLeftCorner.y << " " << BottomRightCorner.x << " " << BottomRightCorner.y << " ";
	file >> FigureColor >> FigureFill;
	std::cout << FigureColor << " " << FigureFill << endl;
	FigGfxInfo.DrawClr = ConvertToColor(FigureColor);
	FigGfxInfo.BorderWdth = UI.PenWidth;
	if (FigureFill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}
	else {
		FigGfxInfo.FillClr = ConvertToColor(FigureFill);
		FigGfxInfo.isFilled = true;
	}

}