#include "ActionSave.h"
#include "ActionLoad.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include <iostream>
#include <windows.h>
#include <string.h>
#include <fstream>


ActionSave::ActionSave(ApplicationManager* pApp,bool withLoading,bool forPlay) :Action(pApp)
{
	 loading = withLoading;
	 playing = forPlay;
}

// Open Save File
void ActionSave::SaveFileName()
{
	
	char* Name = NULL;
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	Name = new char[MAX_PATH];
	Name[0] = 0;
	ofn.lpstrFile = Name;
	ofn.hwndOwner = NULL;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Text\0*.TXT\0";
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "conf";
	if (GetSaveFileName(&ofn)) {
		Filename = Name;
	}
	else {
		printf("No Name");
	};
	delete[] Name;
	Name = NULL;


}



//Execute the action
void ActionSave::Execute()
{


	GUI* g = pManager->GetGUI();
	GfxInfo gf;
	CFigure* f;
	ofstream MyFile;
	
	
	// - - - - - Playing Mode Behaviour - - - - -
	if (playing) {
		MyFile.open("playing.txt", ios::trunc);

	}


	/// - - - - - Normal Save Behaviour - - - - - 

	else {


		g->PrintMessage("Create Save File");
		 SaveFileName();
		g->PrintMessage("Save succesfull to " + Filename);

		if (Filename == "")
		{
			g->PrintMessage("Wrong file name");
			return;
		}


		MyFile.open(Filename, ios::out | ios::trunc);
		string FillColor;
		if (UI.isFilled == false) {
			FillColor = "NO_FILL";
		}
		else {
			FillColor = g->ConvertColorToString(UI.FillColor);
		}
		MyFile << g->ConvertColorToString(UI.DrawColor) << "\t" << FillColor << "\t" << g->ConvertColorToString(UI.BkGrndColor) << endl;

		pManager->SaveAll(MyFile);
		MyFile.close();
		g->ClearStatusBar();

		
		
	}
	


		if (loading) {
			g->PrintMessage("load");
			Action* pAct = new ActionLoad(pManager, false);
			pAct->Execute();

		}
	}
