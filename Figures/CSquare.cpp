#include "CSquare.h"
#include <fstream>
#include <iostream>
int CSquare::squarersNumber= 0;
CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	squarersNumber++;
}
CSquare::CSquare() {
	squarersNumber++;

}
CSquare::~CSquare() {
	squarersNumber--;
	std::cout << "deleted";
}

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
	int x, y;
	ActionType ActType;
	pGUI->PrintMessage("resize");
	pGUI->CreateResizeToolBar();
	ActType = pGUI->MapInputToActionType(x, y);
	float factor = 0;
	switch (ActType) {

	case RESIZE_4:
		factor = 4;
		break;
	case RESIZE_2:
		factor = 2;
		break;
	case RESIZE_0_5:
		factor = 0.5;
		break;
	case RESIZE_0_25:
		factor = 0.25;
		break;
	case DRAWING_AREA:
		factor = 1;
		break;

	};



	//result that get print out: 122.34



	this->length = this->length * factor;
	x = this->length + this->TopLeftCorner.x;
	y = this->length + this->TopLeftCorner.y;
	if ((factor==2||factor==4) && x <= endingPoint.x && x >= startingPoint.x && y >= startingPoint.y && y <= endingPoint.y)
	{
		pGUI->PrintMessage("resize "+to_string(factor));
	}
	else if ((factor == 0.5 || factor == 0.25) &&  (TopLeftCorner.x + 10) < x && (TopLeftCorner.y + 10) < y)
	{
		pGUI->PrintMessage("resize "+to_string(factor));
	}
	else
	{
		this->length = this->length / factor;
		if (factor == 4 || factor == 2) {
			pGUI->PrintMessage("exceeds the window limit");
		}
		else if (factor == 1) {
			pGUI->PrintMessage("Same Size");
		}
		else {
			pGUI->PrintMessage("Too small");
		}
	}
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

	
	GUI* g = nullptr;

	string Fillcolor;

	if (this->FigGfxInfo.isFilled == true)
	{
		Fillcolor = g->ConvertColorToString(this->FigGfxInfo.FillClr);
	}
	else if (this->FigGfxInfo.isFilled != true) {
		Fillcolor = "NO_FILL";
	}

	// Write to the file
	int idd = 1;
	MyFile <<"SQR\t"<<idd<<"\t"<<this->TopLeftCorner.x<< "\t"<< this->TopLeftCorner.y <<"\t"<< this->length <<"\t"<< g->ConvertColorToString(FigGfxInfo.DrawClr) <<"\t"<<Fillcolor<< endl;

}

bool CSquare::InsideAFigure(int x, int y, GUI* pGUI)
{
	if (x >= TopLeftCorner.x && x <= TopLeftCorner.x+length && y >= TopLeftCorner.y && y <= TopLeftCorner.y+length)
	{
		return true;
	}
	return false;
}