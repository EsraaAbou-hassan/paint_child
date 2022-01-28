#include "ActionSave.h"
#include "ActionLoad.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
#include <string>
#include <fstream>


ActionSave::ActionSave(ApplicationManager* pApp,bool withLoading,bool forPlay) :Action(pApp)
{
	 loading = withLoading;
	 playing = forPlay;
}


//Execute the action
void ActionSave::Execute()
{

	
	GUI* g = pManager->GetGUI();
	GfxInfo gf;
	CFigure* f;
	ofstream MyFile;
	if (playing) {
		MyFile.open("playing.txt", ios::trunc);
	}
	else {
		g->PrintMessage("Enter your text File Name");
		string Filename = g->GetSrting();
		if (Filename == "")
		{
			g->PrintMessage("Wrong file name");
			return;
		}
		MyFile.open(Filename + ".txt", ios::app);
	}

	MyFile << g->ConvertColorToString(UI.DrawColor) << "\t" << g->ConvertColorToString(UI.FillColor) << "\t" << g->ConvertColorToString(UI.BkGrndColor)<< endl;


	pManager->SaveAll(MyFile);

	MyFile.close();
	g->ClearStatusBar();

	if (loading) {
		g->PrintMessage("load");
		Action* pAct = new ActionLoad(pManager,false);
		pAct->Execute();

	}
}
