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





ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp) {

}
void ActionLoad::Execute() {

	CFigure* figer;
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
		GUI* pGUI = pManager->GetGUI();
		pGUI->ClearDrawArea();
		pManager->DeleteFigures();
		ifstream MyReadFile(ofn.lpstrFile);

		string DrawColor, FillColor, BackColor, FigursNumber, FigureType;
		int FigNumbers = 0;


		MyReadFile >> DrawColor >> FillColor >> BackColor;
		std::cout << DrawColor << " " << FillColor << " " << BackColor << " " << endl;
		pGUI->setCrntDrawColor(ConvertToColor(DrawColor));
		pGUI->setCrntFillColor(ConvertToColor(FillColor));
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
	else {
		std::cout << "no file selected ";
	}
}
color ActionLoad::ConvertToColor(string s)
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
	return BLACK;
}
