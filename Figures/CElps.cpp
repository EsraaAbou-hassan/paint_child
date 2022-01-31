#include "CElps.h"
#include <fstream>
#include <iostream>
int CElps::ElpsNumber = 0;
CElps::CElps(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	BottomRightCorner = P2;
	ElpsNumber++;
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
	int radiusX = (BottomRightCorner.x - TopLeftCorner.x)/2;
	int radiusY = (BottomRightCorner.y - TopLeftCorner.y) / 2;
	return "Elps selected  center  = ( " + to_string(TopLeftCorner.x+radiusX) + " , " + to_string(TopLeftCorner.y + radiusY) + " ) , radiusX = " + to_string(radiusX) + " , radiusY = " + to_string(radiusY);
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

void CElps::Save(ofstream& MyFile)
{
	
	GUI* g = nullptr;
	
	string Fillcolor;
	if (this->FigGfxInfo.isFilled==true )
	{
		Fillcolor = g->ConvertColorToString(this->FigGfxInfo.FillClr);
	}
	else if (this->FigGfxInfo.isFilled != true) {
		Fillcolor = "NO_FILL";	
	}
	

	// Write to the file
	int idd = 1;
	MyFile << "ELPS\t" << idd << "\t" <<this->TopLeftCorner.x << "\t" << this->TopLeftCorner.y << "\t" <<BottomRightCorner.x <<"\t"<< BottomRightCorner.y << "\t" << g->ConvertColorToString(FigGfxInfo.DrawClr) << "\t" << Fillcolor << endl;
}


void CElps::changeFigureSize(GUI* pGUI)
{
	int x, y;
	ActionType ActType;

	int radiusX = abs(BottomRightCorner.x - TopLeftCorner.x) / 2,
		radiusY = abs(BottomRightCorner.y - TopLeftCorner.y) / 2;
	Point center;
	center.x = TopLeftCorner.x + radiusX;
	center.y = TopLeftCorner.y + radiusY;
	double factor = 0;
	pGUI->PrintMessage("resize");
	pGUI->CreateResizeToolBar();
	ActType = pGUI->MapInputToActionType(x, y);
	switch (ActType) {

	case RESIZE_4:
		factor = 4;
		pGUI->PrintMessage("resize 4");
		break;
	case RESIZE_2:
		factor = 2;
		pGUI->PrintMessage("resize2");
		break;
	case RESIZE_0_5:
		factor = 0.5;
		pGUI->PrintMessage("resize 0.5");
		break;
	case RESIZE_0_25:
		factor = 0.25;
		pGUI->PrintMessage("resize 0.25");
		break;

	};

	radiusX *= factor;
	radiusY *= factor;
	Point p1, p2;
	p1.x = TopLeftCorner.x; p1.y = TopLeftCorner.y;
	p2.x = BottomRightCorner.x; p2.y = BottomRightCorner.y;
	this->TopLeftCorner.x = center.x - radiusX;
	this->TopLeftCorner.y = center.y - radiusY;
	this->BottomRightCorner.x = center.x + radiusX;
	this->BottomRightCorner.y = center.y + radiusY;
	
	if ( (factor==4||factor==2)&&BottomRightCorner.x <= endingPoint.x && TopLeftCorner.x >= startingPoint.x && TopLeftCorner.y >= startingPoint.y && BottomRightCorner.y <= endingPoint.y)
	{
	}
	else if((factor == 0.5 || factor == 0.25)&&radiusX>20&&radiusY>20){
	}
	else
	{
		pGUI->PrintMessage("exceeds the window limit");
		TopLeftCorner.x = p1.x; TopLeftCorner.y = p1.y;
		BottomRightCorner.y = p2.y; BottomRightCorner.x = p2.x;
	}
	pGUI->ClearDrawArea();
	pGUI->CreateDrawToolBar();
}

bool CElps::InsideAFigure(int x, int y)
{
	int radiusX = (BottomRightCorner.x-TopLeftCorner.x)/2;
	int radiusY = (BottomRightCorner.y - TopLeftCorner.y) / 2;
	Point center;
	center.x = TopLeftCorner.x + radiusX;
	center.y = TopLeftCorner.y + radiusY;
	if (pow(x - center.x, 2) / pow(radiusX, 2) + pow(y - center.y, 2) / pow(radiusY, 2) <= 1)
	{
		return true;
	}
	return false;
}
