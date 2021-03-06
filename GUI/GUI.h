#ifndef GUI_H
#define GUI_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "../Figures/HexaStruct.h"


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window

	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType(int& x, int& y) const; //Read the user click and map to an action
	char GetKeyPressed() const;

	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateColorToolBar()const;
	void CreateStatusBar() const;	//create the status bar
	void CreateResizeToolBar() const;
	void CreateFiguresToolBar() const;

	void ClearStatusBar() const;	//Clears the status bar
	bool getCrntIsFilled() const;
	void setCrntDrawColor(color c) const;
	void setCrntFillColor(color c) const;
	void setCrntBackgroundColor(color c) const;


	void ClearBar()const;
	void ClearDrawArea() const;	//Clears the drawing area

	// -- Figures Drawing functions
	bool inDrawingArea(int x, int y) const;
	bool inDrawingArea(int* x, int* y, int vertexsNums) const;
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square
	void DrawElps(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a Elps
	void GetHexagonDrawingInfo(HexagonInfo& hexagon);
	void DrawHexagon(Point center, float rotation, int radius, GfxInfo RectGfxInfo, bool selected = true);
	//void DrawHex(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a Hex



	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	string ConvertColorToString(color c);

	int getCrntPenWidth() const;		//get current pen width


};


#endif