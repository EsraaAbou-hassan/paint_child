#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\GUI.h"

//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	static int mainID;
	/// Add more parameters if needed.
protected:
	Point startingPoint; //drawing area starting coordinates
	Point endingPoint; //drawing area ending coordinates
public:
	CFigure(GfxInfo FigureGfxInfo);
	CFigure();
	
	void SetSelected(bool);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual bool InsideAFigure(int x, int y, GUI* pGUI) = 0;
	virtual void DrawMe(GUI*) const = 0;		//Draw the figure

	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void changeFigureDrawClr(GUI* pGUI);
	void changeFigureFillClr(GUI* pGUI);
	virtual void changeFigureSize(GUI* pGUI) = 0;;

	virtual int getFigureData(POINT& p1, POINT& p2) = 0;
	virtual string getFigureName() = 0;

	color ConvertToColor(string s);
	color GetFigureFillColor();
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif