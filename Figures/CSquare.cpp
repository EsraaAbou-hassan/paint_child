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
	return "Square selected";
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