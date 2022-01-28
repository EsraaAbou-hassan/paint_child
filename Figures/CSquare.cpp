#include "CSquare.h"
#include <fstream>
#include <iostream>

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}
CSquare::CSquare() {}

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	

}


int CSquare::getFigureData(POINT& p1, POINT& p2)
{
	p1.x = TopLeftCorner.x;
	p1.y = TopLeftCorner.y;
	p2.x = TopLeftCorner.x + length;
	p2.y = TopLeftCorner.y + length;
	return length;
}

string CSquare::getFigureName() {
	return "Square selected  top left corner = ( " + to_string(TopLeftCorner.x)+" , "+ to_string(TopLeftCorner.y) + " ) side length = " + to_string(length);
}
void CSquare::changeFigureSize(GUI* pGUI)
{
	Point startingPoint; //drawing area starting coordinates
	Point endingPoint; //drawing area ending coordinates
	startingPoint.x = UI.wx;
	endingPoint.x = UI.wx + UI.width;
	startingPoint.y = UI.wy+UI.ToolBarHeight;
	endingPoint.y = UI.height - UI.StatusBarHeight;


	int x, y;
	ActionType ActType;
	pGUI->PrintMessage("resize");
	pGUI->CreateResizeToolBar();
	ActType = pGUI->MapInputToActionType(x, y);
	switch (ActType) {

	case RESIZE_4:
		this->length = this->length * 4;
		x = this->length + this->TopLeftCorner.x;
		y = this->length + this->TopLeftCorner.y;
		if (x <= endingPoint.x && x >= startingPoint.x && y >= startingPoint.y && y <= endingPoint.y)
		{
			pGUI->PrintMessage("resize 4");
		}
		else
		{
			this->length = this->length / 4;
			pGUI->PrintMessage("exceeds the window limit");
		}
		break;
	case RESIZE_2:
		this->length = this->length * 2;
		x = this->length + this->TopLeftCorner.x;
		y = this->length + this->TopLeftCorner.y;
		if (x <= endingPoint.x && x >= startingPoint.x&& y >= startingPoint.y&& y <= endingPoint.y)
		{
			pGUI->PrintMessage("resize 2");
		}
		else
		{
			this->length = this->length / 2;
			pGUI->PrintMessage("exceeds the window limit");
		}
		break;
	case RESIZE_0_5:
		this->length = this->length * 0.5;
		x = this->length + this->TopLeftCorner.x;
		y = this->length + this->TopLeftCorner.y;
		if ((TopLeftCorner.x +10)<x&&(TopLeftCorner.y+10)<y)
		{
			pGUI->PrintMessage("resize 0.5");
		}
		else
		{
			this->length = this->length * 2;
			pGUI->PrintMessage("too small");
		}
		break;
	case RESIZE_0_25:
		this->length = this->length * 0.25;
		x = this->length + this->TopLeftCorner.x;
		y = this->length + this->TopLeftCorner.y;
		if ((TopLeftCorner.x + 10) < x && (TopLeftCorner.y + 10) < y)
		{
			pGUI->PrintMessage("resize 0.0.25");
		}
		else
		{
			this->length = this->length * 4;
			pGUI->PrintMessage("too small");
		}
		break;

	};

	pGUI->CreateDrawToolBar();
	pGUI->ClearDrawArea();
}
void CSquare::Load(ifstream& file)
{
	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface

	file >> ID >> TopLeftCorner.x >> TopLeftCorner.y >> length;
	std::cout << TopLeftCorner.x << " " << TopLeftCorner.y << " " << length << " ";
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
void CSquare::Save(ofstream& MyFile)
{

	// Create and open a text file
	GUI* g = nullptr;
	// Write to the file
	MyFile <<"SQR\t"<<ID<<"\t" << this->TopLeftCorner.x << "\t" << this->TopLeftCorner.y << "\t" << this->length << "\t" << g->ConvertColorToString(FigGfxInfo.DrawClr) << "\t" << g->ConvertColorToString(FigGfxInfo.FillClr) << endl;

}