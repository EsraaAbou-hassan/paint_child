#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_SQUARE,	//Draw a Square
	DRAW_ELPS,		//Draw an Ellipse
	DRAW_HEX,		//Draw a Hexagon
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	CHNG_BK_CLR,	//Change background color
	DEL,			//Delete a figure(s)
	MOVE,			//Move a figure(s)
	RESIZE,			//Resize a figure(s)
	ROTATE,			//Rotate a figure(s)
	SEND_BACK,		//Send a figure to the back of all figures
	BRNG_FRNT,		//Bring a figure to the front of all figures
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application
	SELECT_COLOR_CYAN, //Cyan Color selection 
	SELECT_COLOR_BEIGE, //Begie Color selection 
	SELECT_COLOR_GREEN, //Green Color selection
	SELECT_COLOR_RED, //Red Color selection
	SELECT_COLOR_BLACK, //black Color selection
	SELECT_COLOR_YELLOW, //yellow Color selection
	SELECT_COLOR_BLUE, //blue Color selection
	SELECT_COLOR_PINK, //pink Color selection
	SELECT_COLOR_BROWN, //brown Color selection
	SELECT_COLOR_ORANGE, //Red Color selection
	DRAWING_AREA,	//A click on the drawing area
	PLAYING_AREA,	//A click on the playing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar
	RESIZE_4,			//Resize a figure(s) 
	RESIZE_2,			//Resize a figure(s)
	RESIZE_0_5,			//Resize a figure(s)
	RESIZE_0_25,			//Resize a figure(s)
	PLAY_FIGUERS,	 //play with figuer type
	PLAY_COLORS,	 // play with color type
	PLAY_FIG_COL,	//play with figuer type and color 
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	FIGURES,
	DRAWING,
	UNDO,
	REDO
	///TODO: Add more action types (if needed)
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif