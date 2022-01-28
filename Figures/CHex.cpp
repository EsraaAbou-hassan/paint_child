#include "CHex.h"
#include "HexaStruct.h"
#include <fstream>
#include <iostream>
CHex::CHex(Point _center, float _rotation, int _radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = _center;
	rotation = _rotation;
	radius = _radius;
}
CHex::CHex() {}

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
	return "Hexagon selected  center  = ( " + to_string(center.x) +" , " + to_string(center.y) + " ) , radius = " + to_string(this->radius);
}
void CHex::Load(ifstream& file)
{

	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface

	file >> ID >> center.x >> center.y >> rotation >> radius;
	std::cout << ID << " " << center.x <<  " " << center.y << " " << rotation << " " << radius << " ";
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

void CHex::Save(ofstream& MyFile)
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
	MyFile << "HEXA\t" <<idd<< "\t" << this->center.x <<"\t"<< this->center.y<<"\t"<<rotation<<"\t"<< this->radius << "\t" << g->ConvertColorToString(FigGfxInfo.DrawClr) << "\t" <<Fillcolor<< endl;
}



void CHex::changeFigureSize(GUI* pGUI)
{
	int x, y;
	ActionType ActType;
	pGUI->PrintMessage("resize");
	pGUI->CreateResizeToolBar();
	ActType = pGUI->MapInputToActionType(x, y);
	switch (ActType) {

	case RESIZE_4:
		this->radius = this->radius * 4;
		pGUI->PrintMessage("resize 4");
		break;
	case RESIZE_2:
		this->radius = this->radius * 2;
		pGUI->PrintMessage("resize 2");
		break;
	case RESIZE_0_5:
		this->radius = this->radius * 0.5;
		pGUI->PrintMessage("resize 0.5");
		break;
	case RESIZE_0_25:
		this->radius = this->radius * 0.25;
		pGUI->PrintMessage("resize 0.25");
		break;

	};

	pGUI->ClearStatusBar();
	pGUI->ClearDrawArea();
	pGUI->CreateDrawToolBar();
}