#include "CHex.h"
#include "HexaStruct.h"
#include <fstream>
#include <iostream>
int CHex::hexaNumber = 0;
CHex::CHex(Point _center, float _rotation, int _radius, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = _center;
	rotation = _rotation;
	radius = _radius;
	hexaNumber++;
}
CHex::CHex() {
	hexaNumber++;
}

void CHex::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Hex on the screen	
	pGUI->DrawHexagon(center, rotation, radius, FigGfxInfo, Selected);
}



int CHex::getFigureData(POINT& p1, POINT& p2)
{
	p1.x = center.x - radius;
	p1.y = center.y - radius;
	p2.x = center.x + radius;
	p2.y = center.y + radius;
	return -1;
}

string CHex::getFigureName() {
	return "Hexagon selected  center  = ( " + to_string(center.x) +" , " + to_string(center.y) + " ) , radius = " + to_string(this->radius);
}
void CHex::Load(ifstream& file)
{

	string FigureColor;
	string FigureFill;

	//Get a Pointer to the Interface

	file >> ID >> center.x >> center.y >> rotation >> radius;
	std::cout << ID << " " << center.x <<  " " << center.y << " " << rotation << " " << radius << " ";
	file >> FigureColor >> FigureFill;
	std::cout << FigureColor << " " << FigureFill << endl;
	FigGfxInfo.DrawClr = ConvertToColor(FigureColor);
	FigGfxInfo.BorderWdth = UI.PenWidth;
	if (FigureFill == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}
	else {
		FigGfxInfo.FillClr = ConvertToColor(FigureFill);
		FigGfxInfo.isFilled = true;
	}

}

void CHex::Save(ofstream& MyFile)
{
	
	GUI* g = nullptr;

	string Fillcolor;
	if (this->FigGfxInfo.isFilled == true)
	{
		Fillcolor = g->ConvertColorToString(this->FigGfxInfo.FillClr);
	}
	else if (this->FigGfxInfo.isFilled != true) {
		Fillcolor = "NO_FILL";
	}
	// Write to the file
	int idd = 1;
	MyFile << "HEXA\t" <<idd<< "\t" << this->center.x <<"\t"<< this->center.y<<"\t"<<rotation<<"\t"<< this->radius << "\t" << g->ConvertColorToString(FigGfxInfo.DrawClr) << "\t" <<Fillcolor<< endl;
}



void CHex::changeFigureSize(GUI* pGUI)
{
	int x, y;
	ActionType ActType;
	pGUI->PrintMessage("resize");
	pGUI->CreateResizeToolBar();
	ActType = pGUI->MapInputToActionType(x, y);
	x = center.x;
	y = center.y;
	double factor = 0;
	switch (ActType) {

	case RESIZE_4:
		factor = 4;
		break;
	case RESIZE_2:
		factor = 2;
		break;
	case RESIZE_0_5:
		factor = 0.5;
		break;
	case RESIZE_0_25:
		factor = 0.25;
		break;
	case DRAWING_AREA:
		factor = 1;
		break;
	};

	this->radius = this->radius * factor;
	int x1 = x-radius;
	x += radius;
	int y2 = y - radius;
	y += radius;
	if ((factor == 2 || factor == 4) && x <= endingPoint.x && x >= startingPoint.x && y >= startingPoint.y && y <= endingPoint.y && x1 <= endingPoint.x && x1 >= startingPoint.x && y2 >= startingPoint.y && y2 <= endingPoint.y)
	{
		pGUI->PrintMessage("resize " + to_string(factor));
	}
	else if ((factor == 0.5 || factor == 0.25) && radius >10)
	{
		pGUI->PrintMessage("resize " + to_string(factor));
	}
	else
	{
		this->radius = this->radius / factor;
		if (factor == 4 || factor == 2) {
			pGUI->PrintMessage("exceeds the window limit");
		}
		else if (factor == 1) {
			pGUI->PrintMessage("Same Size");
		}
		else {
			pGUI->PrintMessage("Too small");
		}
	}
	pGUI->ClearDrawArea();
	pGUI->CreateDrawToolBar();
}

bool CHex::onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

int CHex::orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool CHex::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool CHex::isInside(Point polygon[], int n, Point p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3) return false;

	// Create a point for line segment from p to infinite
	Point extreme = { UI.wx+UI.width, p.y };
	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;
		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return (count % 2 == 1);
}

bool CHex::InsideAFigure(int x, int y, GUI* pGUI)
{

	HexagonInfo hexagonData;
	hexagonData.center.x = this->center.x;
	hexagonData.center.y = this->center.y;
	hexagonData.radius = this->radius;
	hexagonData.rotation = this->rotation;
	pGUI->GetHexagonDrawingInfo(hexagonData);
	Point hexVertices[6];
	
	for (int i = 0; i < 6; i++) {
		hexVertices[i].x = hexagonData.ipX[i];
		hexVertices[i].y = hexagonData.ipY[i];
	}
	Point p;
	p.x = x; p.y = y;
	return isInside(hexVertices,6,p);
}