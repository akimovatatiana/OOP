// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ShapeProcessor.h"

int main()
{
	//fstream inputFile("input.txt");
	CShapeProcessor shapes(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
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