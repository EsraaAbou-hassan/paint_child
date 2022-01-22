#include "GUI.h"
#include "../Figures/HexaStruct.h"
#include <iostream>

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy = 5;

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = CYAN;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = VIOLET;
	UI.PenWidth = 3;	//width of the figures frames
	UI.isFilled = false;

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

char GUI::GetKeyPressed() const 
{
	char Key;
	pWind->WaitKeyPress(Key);
	return Key;
}
//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEX: return DRAW_HEX;
			case ITM_DRAW_CLR: return CHNG_DRAW_CLR;
			case ITM_FILL_CLR: return CHNG_FILL_CLR;
			case ITM_BACKGROUND_CLR: return CHNG_BK_CLR;
			case ITM_DEL: return DEL;
			case ITM_SENDBACK: return SEND_BACK;
			case ITM_BRINGFRONT: return BRNG_FRNT;
			case ITM_EXIT: return EXIT;	
			case ITM_CLR_CYAN: return SELECT_COLOR_CYAN;
			case ITM_CLR_GREEN: return SELECT_COLOR_GREEN;
			case ITM_CLR_RED: return SELECT_COLOR_RED;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	

}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
	
}

bool GUI::getCrntIsFilled() const {
	return UI.isFilled;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEX] = "images\\MenuItems\\Menu_Hex.jpg";
	MenuItemImages[ITM_DRAW_CLR] = "images\\MenuItems\\Border_Color.jpg";
	MenuItemImages[ITM_FILL_CLR] = "images\\MenuItems\\Fill_Color.jpg";
	MenuItemImages[ITM_BACKGROUND_CLR] = "images\\MenuItems\\Background_Color.jpg";
	MenuItemImages[ITM_DEL] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_SENDBACK] = "images\\MenuItems\\Send_Back.jpg";
	MenuItemImages[ITM_BRINGFRONT] = "images\\MenuItems\\Bring_Front.jpg";
	MenuItemImages[ITM_CLR_CYAN] = "images\\MenuItems\\cyan.jpg";
	MenuItemImages[ITM_CLR_GREEN] = "images\\MenuItems\\green.jpg";
	MenuItemImages[ITM_CLR_RED] = "images\\MenuItems\\red.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);	
}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Roboto");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntDrawColor(color c) const
{
	UI.DrawColor = c;
}

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntFillColor(color c) const
{
	UI.isFilled = true;
	UI.FillColor = c;
}
color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::setCrntBackgroundColor(color c) const
{
	UI.BkGrndColor = c;
}

//color GUI::getCrntBackgroundColor() const	//get current Background color
//{
//	return UI.BkGrndColor;
//}
//////////////////////////////////////////////////////////////////////////////////////////
	
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);

}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::DrawElps(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawEllipse(P1.x,P1.y,P2.x,P2.y, style);

}

//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetHexagonDrawingInfo(HexagonInfo& hexagon)
{
	if (hexagon.radius == NULL) {
		// Calculate the radius of the hexagon
		hexagon.radius = sqrt(pow(hexagon.center.x - hexagon.firstVertex.x, 2)
			+ pow(hexagon.center.y - hexagon.firstVertex.y, 2));
	}

	float angle = hexagon.rotation;

	if (angle == NULL) {
		// Get the rotation angle of the first point
		angle = atan2((float)hexagon.firstVertex.y - (float)hexagon.center.y,
			(float)hexagon.firstVertex.x - (float)hexagon.center.x);
		hexagon.rotation = angle;
	}

	// Find the hexagon vertex
	for (int i = 0; i < 6; i++) {
		hexagon.ipX[i] = (float)hexagon.center.x + (hexagon.radius * cos(angle));
		hexagon.ipY[i] = (float)hexagon.center.y + (hexagon.radius * sin(angle));

		angle += (3.14159265 / 3);
	}

}

void GUI::DrawHexagon(Point center, float rotation, int radius, GfxInfo RectGfxInfo, bool selected) 
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	HexagonInfo hexagon;
	hexagon.center = center;
	hexagon.rotation = rotation;
	hexagon.radius = radius;

	// Get the drawing info
	GetHexagonDrawingInfo(hexagon);

	pWind->DrawPolygon(hexagon.ipX, hexagon.ipY, 6, style);

}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

