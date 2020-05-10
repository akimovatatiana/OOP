#include "stdafx.h"
#include "ShapeProcessor.h"
#include "Point.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

using namespace std::placeholders;

CShapeProcessor::CShapeProcessor(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		{"Triangle", bind(&CShapeProcessor::AddTriangle, this, _1)},
		{"Circle", bind(&CShapeProcessor::AddCircle, this, _1)},
		{"Rectangle", bind(&CShapeProcessor::AddRectangle, this, _1)},
		{"LineSegment", bind(&CShapeProcessor::AddLineSegment, this, _1)},
		})
{
}

bool CShapeProcessor::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CShapeProcessor::Info() const
{
	for (const auto shape : m_shapesList)
	{
		m_output << shape->ToString() << endl;
	}
}

void CShapeProcessor::AddLineSegment(std::istream& args)
{
	uint32_t lineColor = 0x000000;

	vector<string> shapeParametrs = ParseArgs(args);
	CPoint startPoint = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	CPoint endPoint = { stod(shapeParametrs[3]), stod(shapeParametrs[4]) };

	if (shapeParametrs.size() == 6 || shapeParametrs.size() == 5)
	{
		if (shapeParametrs.size() == 6)
		{
			lineColor = stoul(shapeParametrs[5], nullptr, 16);
		}
		auto lineSegment = make_shared<CLineSegment>(startPoint, endPoint, lineColor);
		m_shapesList.push_back(lineSegment);
	}
	else
	{
		m_output << "Failed to create a line segment." << endl
			<< "Usage: LineSegment <start point> <end point> ( <outline color> )" << endl;
	}
}

void CShapeProcessor::AddTriangle(std::istream& args)
{
	uint32_t outlineColor = 0x000000;
	uint32_t fillColor = 0xFFFFFF;

	vector<string> shapeParametrs = ParseArgs(args);

	CPoint vertex1 = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	CPoint vertex2 = { stod(shapeParametrs[3]), stod(shapeParametrs[4]) };
	CPoint vertex3 = { stod(shapeParametrs[5]), stod(shapeParametrs[6]) };
	if (shapeParametrs.size() == 7 || shapeParametrs.size() == 8 || shapeParametrs.size() == 9)
	{
		if (shapeParametrs.size() == 8)
		{
			outlineColor = stoul(shapeParametrs[7], nullptr, 16);
		}
		if (shapeParametrs.size() == 9)
		{
			outlineColor = stoul(shapeParametrs[7], nullptr, 16);
			fillColor = stoul(shapeParametrs[8], nullptr, 16);
		}

		auto triangle = make_shared<CTriangle>(vertex1, vertex2, vertex3, fillColor, outlineColor);
		m_shapesList.push_back(triangle);
	}
	else
	{
		m_output << "Failed to create a triangle." << endl
			<< "Usage: Triangle <vertex1> <vertex2> <vertex3> ( <outline color> <fill color> )" << endl;
	}
}

void CShapeProcessor::AddCircle(std::istream& args)
{
	uint32_t outlineColor = 0x000000;
	uint32_t fillColor = 0xFFFFFF;

	vector<string> shapeParametrs = ParseArgs(args);

	CPoint center = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	double radius = stod(shapeParametrs[3]);
	if (shapeParametrs.size() == 4 || shapeParametrs.size() == 5 || shapeParametrs.size() == 6)
	{
		if (shapeParametrs.size() == 5)
		{
			outlineColor = stoul(shapeParametrs[4], nullptr, 16);
		}
		if (shapeParametrs.size() == 6)
		{
			outlineColor = stoul(shapeParametrs[4], nullptr, 16);
			fillColor = stoul(shapeParametrs[5], nullptr, 16);
		}

		auto circle = make_shared<CCircle>(center, radius, fillColor, outlineColor);
		m_shapesList.push_back(circle);
	}
	else
	{
		m_output << "Failed to create a circle." << endl
			<< "Usage: Circle <center point> <radius> ( <outline color> <fill color> )" << endl;
	}
}

void CShapeProcessor::AddRectangle(std::istream& args)
{
	uint32_t outlineColor = 0x000000;
	uint32_t fillColor = 0xFFFFFF;

	vector<string> shapeParametrs = ParseArgs(args);

	CPoint topLeft = { stod(shapeParametrs[1]), stod(shapeParametrs[2]) };
	double width = stod(shapeParametrs[3]);
	double height = stod(shapeParametrs[4]);
	if (shapeParametrs.size() == 5 || shapeParametrs.size() == 6 || shapeParametrs.size() == 7)
	{
		if (shapeParametrs.size() == 6)
		{
			outlineColor = stoul(shapeParametrs[5], nullptr, 16);
		}
		if (shapeParametrs.size() == 7)
		{
			outlineColor = stoul(shapeParametrs[5], nullptr, 16);
			fillColor = stoul(shapeParametrs[6], nullptr, 16);
		}

		auto rectangle = make_shared<CRectangle>(topLeft, width, height, fillColor, outlineColor);
		m_shapesList.push_back(rectangle);
	}
	else
	{
		m_output << "Failed to create a rectangle." << endl
			<< "Usage: Rectangle <top left point> <width> <height> ( <outline color> <fill color> )" << endl;
	}
}

void CShapeProcessor::GetShapeWithMinPerimeter() const
{
	if (!CheckIfListIsEmpty())
	{
		auto shapeWithMinPerimeter = min_element(m_shapesList.begin(), m_shapesList.end(),
			[](shared_ptr<IShape> const& first, shared_ptr<IShape> const& second)
			{
				return second->GetPerimeter() > first->GetPerimeter();
			});
		m_output << "Shape with min perimeter is " << (*shapeWithMinPerimeter)->ToString() << endl;
	}
	else
	{
		m_output << "Failed to get the shape with min perimeter. Shapes list is empty." << endl;
	}

}

void CShapeProcessor::GetShapeWithMaxArea() const
{
	if (!CheckIfListIsEmpty())
	{
		auto shapeWithMaxArea = max_element(m_shapesList.begin(), m_shapesList.end(),
			[](shared_ptr<IShape> const& first, shared_ptr<IShape> const& second)
			{
				return second->GetArea() > first->GetArea();
			});
		m_output << "Shape with max area is " << (*shapeWithMaxArea)->ToString() << endl;
	}
	else
	{
		m_output << "Failed to get the shape with max area. Shapes list is empty." << endl;
	}
}

bool CShapeProcessor::CheckIfListIsEmpty() const
{
	if (m_shapesList.empty())
	{
		return true;
	}
	return false;
}

vector<string> CShapeProcessor::ParseArgs(std::istream& args)
{
	vector<string> shapeParameters;
	string parameter;

	while (getline(args, parameter, ' '))
	{
		shapeParameters.push_back(parameter);
	}
	return shapeParameters;
}