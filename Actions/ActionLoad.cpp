#include "ActionLoad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Figures/CSquare.h"
#include "../Figures/CElps.h"
#include "../Figures/CHex.h"
#include "../GUI/GUI.h"
#include "../ApplicationManager.h"
#include "../CMUgraphicsLib/colors.h"
#include <windows.h>
#include <Commdlg.h>





ActionLoad::ActionLoad(ApplicationManager* pApp, bool forPlaying) :Action(pApp) {
	playing = forPlaying;
}
void ActionLoad::Execute() {

	CSquare::squarersNumber = 0;
	CElps::ElpsNumber = 0;
	CHex::hexaNumber = 0;

	if (playing) {
		
		loading("playing.txt");
	}
	else {
		OPENFILENAME ofn;
		char szFile[100];

		// open a file name
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		/////////////////////

		// Read from the text file
		std::cout << (ofn.lpstrFile) << endl;

		if (GetOpenFileName(&ofn)) {
			loading(ofn.lpstrFile);
		}
		else {
			std::cout << "no file selected ";
		}
	}

}
color ActionLoad::ConvertToColor(string s)
{
	if (s == "BEIGE")
		return BEIGE;
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
}

void ActionLoad::loading(char file[100])
{
	CFigure* figer;
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearDrawArea();
	pManager->DeleteFigures();
	ifstream MyReadFile(file);
	string DrawColor, FillColor, BackColor, FigursNumber, FigureType;
	int FigNumbers = 0;


	MyReadFile >> DrawColor >> FillColor >> BackColor;
	std::cout << DrawColor << " " << FillColor << " " << BackColor << " " << endl;
	if (FillColor == "NO_FILL") {
		UI.isFilled = false;
	}
	else {
		UI.isFilled = true;
		pGUI->setCrntFillColor(ConvertToColor(FillColor));
	}
	pGUI->setCrntDrawColor(ConvertToColor(DrawColor));
	pGUI->setCrntBackgroundColor(ConvertToColor(BackColor));
	pGUI->ClearDrawArea();

	MyReadFile >> FigursNumber;
	std::cout << FigursNumber << endl;
	FigNumbers = std::stoi(FigursNumber);
	while (FigNumbers) {
		MyReadFile >> FigureType;
		std::cout << FigureType << " ";
		if (FigureType == "SQR") {
			figer = new CSquare;

		}
		else if (FigureType == "ELPS") {
			figer = new CElps;

		}
		else if (FigureType == "HEXA") {
			figer = new CHex;

		}
		figer->Load(MyReadFile);
		pManager->AddFigure(figer);
		FigNumbers--;
	}



	MyReadFile.close();
}



