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
	return "Elps selected  top left corner  = ( " + to_string(TopLeftCorner.x) + " , " + to_string(TopLeftCorner.y) + " ) , bottom right corner = ( " + to_string(BottomRightCorner.x) + " , " + to_string(BottomRightCorner.y) + " )";
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

}
void CElps::changeFigureSize(GUI* pGUI)
{
	int x, y;
	ActionType ActType;
	pGUI->PrintMessage("resize");
	pGUI->CreateResizeToolBar();
	ActType = pGUI->MapInputToActionType(x, y);
	switch (ActType) {

	case RESIZE_4:
		pGUI->PrintMessage("resize 4");
		break;
	case RESIZE_2:
		pGUI->PrintMessage("resize 2");
		break;
	case RESIZE_0_5:
		pGUI->PrintMessage("resize 0.5");
		break;
	case RESIZE_0_25:
		pGUI->PrintMessage("resize 0.25");
		break;

	};

	pGUI->ClearStatusBar();
	pGUI->CreateDrawToolBar();
}