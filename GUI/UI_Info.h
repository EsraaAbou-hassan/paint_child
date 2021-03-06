#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_COLOR,
	MODE_RESIZE,
	MODE_FIGURES

};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	ITM_FIGURES,		//Hexa item in menu
	ITM_DRAW_CLR,	//Draw Color item in menu
	ITM_FILL_CLR,	//Fill Color item in menu
	ITM_BACKGROUND_CLR,	//Background Color item in menu
	ITM_DEL,
	ITM_SENDBACK,
	ITM_BRINGFRONT,
	ITM_SAVE,
	ITM_LOAD,
	ITM_REDO,
	ITM_UNDO,
	ITM_RESIZE,
	ITM_EXIT,		//Exit item
	ITM_PLAY,
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{

	ITM_FIGURE,
	ITM_COLOR,
	ITM_FIG_COL,
	ITM_DRAW,
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};
enum ColorMenuItm
{
	ITM_CLR_BEIGE_T,
	ITM_CLR_CYAN_T,
	ITM_CLR_GREEN_T,
	ITM_CLR_RED_T,
	ITM_CLR_YELLOW_T,
	ITM_CLR_BLACK_T,
	ITM_CLR_BLUE_T,
	ITM_CLR_PINK_T,
	ITM_CLR_BROWN_T,
	ITM_CLR_ORANGE_T,
	Color_ITM_COUNT  //no. of menu items ==> This should be the last line in this enum
};
enum ResizeMenuItm {
	ITM_4_SIZE,
	ITM_2_SIZE,
	ITM_0_5_SIZE,
	ITM_0_25_SIZE,
	Resize_ITM_COUNT //no. of menu items ==> This should be the last line in this enum
};
enum FigureMenuItm {
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEX,
	ITM_DRAWING,
	Figures_ITM_COUNT //no. of menu items ==> This should be the last line in this enum
};




__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth,		//Width of each item in toolbar menu
		ColorsPalleteSize;
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	bool isFilled;
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	
}UI;	//create a global object UI

#endif