#include "CFigure.h"
int CFigure::mainID = 0;
CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID= ++mainID;

	startingPoint.x = UI.wx;
	startingPoint.y = UI.wy + UI.ToolBarHeight;
	endingPoint.x = UI.wx + UI.width;
	endingPoint.y = UI.height - UI.StatusBarHeight;
}
CFigure::CFigure() {
	GfxInfo FigureGfxInfo;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	startingPoint.x = UI.wx;
	startingPoint.y = UI.wy + UI.ToolBarHeight;
	endingPoint.x = UI.wx + UI.width;
	endingPoint.y = UI.height - UI.StatusBarHeight;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
}
bool CFigure::IsFilled() const
{
	return FigGfxInfo.isFilled;
}

void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

void CFigure::changeFigureDrawClr(GUI* pGUI)
{
	ActionType ActType;
	int x, y;
	pGUI->PrintMessage("Select a color");
	pGUI->CreateColorToolBar();
	ActType = pGUI->MapInputToActionType(x,y);

	switch (ActType) {
	case SELECT_COLOR_CYAN:
		this->ChngDrawClr(CYAN);
		break;
	case SELECT_COLOR_GREEN:
		this->ChngDrawClr(GREEN);
		break;
	case SELECT_COLOR_RED:
		this->ChngDrawClr(RED);
		break;
	case SELECT_COLOR_BLACK:
		this->ChngDrawClr(BLACK);
		break;
	case SELECT_COLOR_YELLOW:
		this->ChngDrawClr(YELLOW);
		break;
	case SELECT_COLOR_BLUE:
		this->ChngDrawClr(BLUE);
		break;
	case SELECT_COLOR_PINK:
		this->ChngDrawClr(PINK);
		break;
	case SELECT_COLOR_BROWN:
		this->ChngDrawClr(BROWN);
		break;
	case SELECT_COLOR_ORANGE:
		this->ChngDrawClr(ORANGE);
		break;
	};
	pGUI->ClearStatusBar();
	pGUI->CreateDrawToolBar();
}


void CFigure::changeFigureFillClr(GUI* pGUI)
{
	ActionType ActType;
	int x, y;
	pGUI->PrintMessage("Select a color");
	pGUI->CreateColorToolBar();
	ActType = pGUI->MapInputToActionType(x, y);

	switch (ActType) {
	case SELECT_COLOR_CYAN:
		this->ChngFillClr(CYAN);
		break;
	case SELECT_COLOR_GREEN:
		this->ChngFillClr(GREEN);
		break;
	case SELECT_COLOR_RED:
		this->ChngFillClr(RED);
		break;
	case SELECT_COLOR_BLACK:
		this->ChngFillClr(BLACK);
		break;
	case SELECT_COLOR_YELLOW:
		this->ChngFillClr(YELLOW);
		break;
	case SELECT_COLOR_BLUE:
		this->ChngFillClr(BLUE);
		break;
	case SELECT_COLOR_PINK:
		this->ChngFillClr(PINK);
		break;
	case SELECT_COLOR_BROWN:
		this->ChngFillClr(BROWN);
		break;
	case SELECT_COLOR_ORANGE:
		this->ChngFillClr(ORANGE);
		break;
	};
	pGUI->ClearStatusBar();
	pGUI->CreateDrawToolBar();
}

color CFigure::ConvertToColor(string s)
{
	if (s == "BLACK")
		return BLACK;
	if (s == "BLUE")
		return BLUE;
	if (s == "WHITE")
		return WHITE;
	if (s == "RED")
		return RED;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "GREEN")
		return GREEN;
	if (s == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	if (s == "MAGENTA")
		return MAGENTA;
	if (s == "TURQUOISE")
		return TURQUOISE;
	if (s == "CYAN")
		return CYAN;
	if (s == "PINK")
		return PINK;
	if (s == "BROWN")
		return BROWN;
	if (s == "ORANGE")
		return ORANGE;
	return BLACK;
}

color CFigure::GetFigureFillColor() {
	return FigGfxInfo.FillClr;
}