// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ShapeProcessor.h"

int main()
{
	CShapeProcessor shapes(cin, cout);

	cout << "Enter this commands to create shapes:" << endl
		<< "LineSegment <start point> <end point> ( <outline color> )" << endl
		<< "Triangle <vertex1> <vertex2> <vertex3> ( <outline color> <fill color> )" << endl
		<< "Circle <center point> <radius> ( <outline color> <fill color> )" << endl
		<< "Rectangle <top left point> <width> <height> ( <outline color> <fill color> )" << endl
		<< "Example: Rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00" << endl;

	while (!cin.eof() && !cin.fail())
	{
		cout << ">";
		if (!shapes.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	shapes.Info();
	shapes.GetShapeWithMaxArea();
	shapes.GetShapeWithMinPerimeter();

	return 0;
}