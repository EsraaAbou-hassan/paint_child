#include "ActionSave.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
#include <string>
#include <fstream>


ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp)
{}


//Execute the action
void ActionSave::Execute()
{

	GUI* g = pManager->GetGUI();
	g->PrintMessage("Enter your text File Name");
	string Filename = g->GetSrting();
	if (Filename == "")
	{
		g->PrintMessage("Wrong file name");
		return;
	}
	GfxInfo gf;
	CFigure* f;
	ofstream MyFile;
	MyFile.open(Filename + ".txt", ios::app);
	MyFile << g->ConvertColorToString(UI.DrawColor) << "\t" << g->ConvertColorToString(UI.FillColor) << "\t" << g->ConvertColorToString(UI.BkGrndColor)<< endl;


	pManager->SaveAll(MyFile);

	MyFile.close();

}
