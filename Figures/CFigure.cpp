#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

void CFigure::SetSelected(bool s)
{
	Selected = s;
}

bool CFigure::IsSelected() const
{
	return Selected;
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
void CFigure::changeFigureFillClr(GUI* pGUI)
{
	ActionType ActType;
	pGUI->PrintMessage("Select a color");
	ActType = pGUI->MapInputToActionType();

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
	};
	pGUI->ClearStatusBar();
}
