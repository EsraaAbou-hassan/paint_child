#include "ActionAddHex.h"
#include "..\Figures\CHex.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddHex::ActionAddHex(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddHex::Execute()
{
    Point Center, FirstVertex;

    //Get a Pointer to the Interface
    GUI* pGUI = pManager->GetGUI();

    //get drawing, filling colors and pen width from the interface
    GfxInfo SqrGfxInfo;
    SqrGfxInfo.isFilled = pGUI->getCrntIsFilled();	//default is not filled
    //get drawing, filling colors and pen width from the interface
    SqrGfxInfo.DrawClr = pGUI->getCrntDrawColor();
    SqrGfxInfo.FillClr = pGUI->getCrntFillColor();
    SqrGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


    //Step 1 - Read Hexagon data from the user

    pGUI->PrintMessage("New Hexagon: Click at center point");
    //Read 1st point and store in point Center
        pGUI->GetPointClicked(Center.x, Center.y);

        if (!isValid(Center))
        {
            Center.x = 0;
            Center.y = 0;
            (pManager->GetGUI())->PrintMessage("Invalid point, please select another action");
            return;
        }

    pGUI->PrintMessage("New Hexagon: Click at First Vertex point");
    //Read 2nd point and store in point FirstVertex
        pGUI->GetPointClicked(FirstVertex.x, FirstVertex.y);

        while (FirstVertex.x == FirstVertex.y)
        {
            (pManager->GetGUI())->PrintMessage("Invalid point, please select another point");
            pGUI->GetPointClicked(FirstVertex.x, FirstVertex.y);
        }
        if (!isValid(FirstVertex))
        {
            FirstVertex.x = 0;
            FirstVertex.y = 0;
            (pManager->GetGUI())->PrintMessage("Invalid point, please select another action");
            return;
        }
    pGUI->ClearStatusBar();

    HexagonInfo hexagon;
    hexagon.inBounds = false;
    hexagon.rotation = NULL;
    hexagon.radius = NULL;
    hexagon.center = Center;
    hexagon.firstVertex = FirstVertex;

    // Get the drawing info
    pGUI->GetHexagonDrawingInfo(hexagon);

    //check if it's inBounds
    if (hexagon.inBounds) {
        //Step 3 - Create a Hexagon with the parameters read from the user
        CHex* R = new CHex(hexagon.center, hexagon.rotation, hexagon.radius, SqrGfxInfo);

        //Step 4 - Add the Hexagon to the list of figures
        pManager->AddFigure(R);
    }
    else
    {
        pGUI->PrintMessage("Can't draw outside the drawing area!");
    }


}
