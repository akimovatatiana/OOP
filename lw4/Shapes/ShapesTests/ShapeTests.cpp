#include "stdafx.h"
#include <boost/algorithm/string/replace.hpp>
#include "../Shapes/Point.h"
#include "../Shapes/LineSegment.h"
#include "../Shapes/IShape.h"
#include "../Shapes/ISolidShape.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Circle.h"

struct PointFixture
{
	double x = 10.05;
	double y = 15.26;

	CPoint point;
	PointFixture()
		: point(x, y)
	{}
};
BOOST_FIXTURE_TEST_SUITE(CPoint_tests, PointFixture)
BOOST_AUTO_TEST_CASE(can_get_x_value)
{
	BOOST_CHECK_EQUAL(point.x, 10.05);
}
BOOST_AUTO_TEST_CASE(can_get_y_value)
{
	BOOST_CHECK_EQUAL(point.y, 15.26);
}
BOOST_AUTO_TEST_CASE(can_get_x_and_y_values)
{
	string expectedString = "(10.05, 15.26)";
	BOOST_CHECK_EQUAL(expectedString, point.ToString());
}
BOOST_AUTO_TEST_SUITE_END()

struct LineSegmentFixture
{
	CPoint startPoint = { 5.25, 10.75 };
	CPoint endPoint = { 25.10, 15.35 };
	uint32_t outlineColor = 0x808080;

	CLineSegment lineSegment;
	LineSegmentFixture()
		: lineSegment(startPoint, endPoint, outlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(CLineSegment_tests, LineSegmentFixture)

BOOST_AUTO_TEST_CASE(gets_zero_area)
{
	double expectedArea = 0;
	BOOST_CHECK_EQUAL(expectedArea, lineSegment.GetArea());
}
BOOST_AUTO_TEST_CASE(can_get_perimeter)
{
	double expectedPerimeter = 20.376027581449726;
	BOOST_CHECK_EQUAL(expectedPerimeter, lineSegment.GetPerimeter());
}
BOOST_AUTO_TEST_CASE(can_get_outline_color)
{
	uint32_t expectedOutlineColor = 0x808080;
	BOOST_CHECK_EQUAL(expectedOutlineColor, lineSegment.GetOutlineColor());
}
BOOST_AUTO_TEST_CASE(can_be_get_as_a_string)
{
	string expectedString = R"(Line segment:
	Area = 0.0000
	Perimeter = 20.3760
	Outline color = #808080
	Start point = (5.25, 10.75)
	End point = (25.1, 15.35)
)";
	BOOST_CHECK_EQUAL(expectedString, lineSegment.ToString());
}

BOOST_AUTO_TEST_CASE(can_get_start_point)
{
	BOOST_CHECK(lineSegment.GetStartPoint().x == 5.25);
	BOOST_CHECK(lineSegment.GetStartPoint().y == 10.75);
}
BOOST_AUTO_TEST_CASE(can_get_end_point)
{
	BOOST_CHECK(lineSegment.GetEndPoint().x == 25.10);
	BOOST_CHECK(lineSegment.GetEndPoint().y == 15.35);
}

BOOST_AUTO_TEST_SUITE_END()

struct TriangleFixture
{
	CPoint vertex1 = { -2, 3 };
	CPoint vertex2 = { 4, 3 };
	CPoint vertex3 = { 2, 5 };
	uint32_t outlineColor = 0x000000;
	uint32_t fillColor = 0xffffff;

	CTriangle triangle;
	TriangleFixture()
		: triangle(vertex1, vertex2, vertex3, fillColor, outlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(CTriangle_tests, TriangleFixture)

BOOST_AUTO_TEST_CASE(can_get_area)
{
	double expectedArea = 5.9999999999999991;
	BOOST_CHECK_EQUAL(expectedArea, triangle.GetArea());
}
BOOST_AUTO_TEST_CASE(can_get_perimeter)
{
	double expectedPerimeter = 13.300563079745769;
	BOOST_CHECK_EQUAL(expectedPerimeter, triangle.GetPerimeter());
}
BOOST_AUTO_TEST_CASE(can_get_outline_color)
{
	uint32_t expectedOutlineColor = 0x000000;
	BOOST_CHECK_EQUAL(expectedOutlineColor, triangle.GetOutlineColor());
}
BOOST_AUTO_TEST_CASE(can_get_fill_color)
{
	uint32_t expectedFillColor = 0xffffff;
	BOOST_CHECK_EQUAL(expectedFillColor, triangle.GetFillColor());
}
BOOST_AUTO_TEST_CASE(tringle_can_be_get_as_a_string)
{
	string expectedString = R"(Triangle:
	Area = 6.0000
	Perimeter = 13.3006
	Outline color = #000000
	Fill color = #ffffff
	Vertex1 = (-2, 3)
	Vertex2 = (4, 3)
	Vertex3 = (2, 5)
)";
	BOOST_CHECK_EQUAL(expectedString, triangle.ToString());
}
BOOST_AUTO_TEST_CASE(can_get_vertex1)
{
	BOOST_CHECK(triangle.GetVertex1().x == -2);
	BOOST_CHECK(triangle.GetVertex1().y == 3);
}
BOOST_AUTO_TEST_CASE(can_get_vertex2)
{
	BOOST_CHECK(triangle.GetVertex2().x == 4);
	BOOST_CHECK(triangle.GetVertex2().y == 3);
}
BOOST_AUTO_TEST_CASE(can_get_vertex3)
{
	BOOST_CHECK(triangle.GetVertex3().x == 2);
	BOOST_CHECK(triangle.GetVertex3().y == 5);
}

BOOST_AUTO_TEST_SUITE_END()

struct CircleFixture
{
	CPoint center = { 10, 9 };
	double radius = 40;
	uint32_t outlineColor = 0x000000;
	uint32_t fillColor = 0xffffff;

	CCircle circle;
	CircleFixture()
		: circle(center, radius, fillColor, outlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(CCircle_tests, CircleFixture)

BOOST_AUTO_TEST_CASE(can_get_area)
{
	double expectedArea = 5026.5482457436692;
	BOOST_CHECK_EQUAL(expectedArea, circle.GetArea());
}

BOOST_AUTO_TEST_CASE(can_get_perimeter)
{
	double expectedPerimeter = 251.32741228718345;
	BOOST_CHECK_EQUAL(expectedPerimeter, circle.GetPerimeter());
}
BOOST_AUTO_TEST_CASE(can_get_outline_color)
{
	uint32_t expectedOutlineColor = 0x000000;
	BOOST_CHECK_EQUAL(expectedOutlineColor, circle.GetOutlineColor());
}
BOOST_AUTO_TEST_CASE(can_get_fill_color)
{
	uint32_t expectedFillColor = 0xffffff;
	BOOST_CHECK_EQUAL(expectedFillColor, circle.GetFillColor());
}
BOOST_AUTO_TEST_CASE(can_be_get_as_a_string)
{
	string expectedString = R"(Circle:
	Area = 5026.5482
	Perimeter = 251.3274
	Outline color = #000000
	Fill color = #ffffff
	Center = (10, 9)
	Radius = 40.0000
)";
	BOOST_CHECK_EQUAL(expectedString, circle.ToString());
}
BOOST_AUTO_TEST_CASE(can_get_center)
{
	BOOST_CHECK(circle.GetCenter().x == 10);
	BOOST_CHECK(circle.GetCenter().y == 9);
}
BOOST_AUTO_TEST_CASE(can_get_radius)
{
	double expectedRadius = 40;
	BOOST_CHECK_EQUAL(expectedRadius, circle.GetRadius());
}
BOOST_AUTO_TEST_SUITE_END()

struct RectangleFixture
{
	CPoint topLeft = { 200 , 100 };
	double width = 60;
	double height = 20;
	uint32_t outlineColor = 0x000000;
	uint32_t fillColor = 0xffffff;

	CRectangle rectangle;
	RectangleFixture()
		: rectangle(topLeft, width, height, fillColor, outlineColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(CRectangle_tests, RectangleFixture)

BOOST_AUTO_TEST_CASE(can_get_area)
{
	double expectedArea = 1200;
	BOOST_CHECK_EQUAL(expectedArea, rectangle.GetArea());
}
BOOST_AUTO_TEST_CASE(can_get_perimeter)
{
	double expectedPerimeter = 160;
	BOOST_CHECK_EQUAL(expectedPerimeter, rectangle.GetPerimeter());
}
BOOST_AUTO_TEST_CASE(can_get_outline_color)
{
	uint32_t expectedOutlineColor = 0x000000;
	BOOST_CHECK_EQUAL(expectedOutlineColor, rectangle.GetOutlineColor());
}
BOOST_AUTO_TEST_CASE(can_get_fill_color)
{
	uint32_t expectedFillColor = 0xffffff;
	BOOST_CHECK_EQUAL(expectedFillColor, rectangle.GetFillColor());
}
BOOST_AUTO_TEST_CASE(can_be_get_as_a_string)
{
	string expectedString = R"(Rectangle:
	Area = 1200.0000
	Perimeter = 160.0000
	Outline color = #000000
	Fill color = #ffffff
	Top left = (200, 100)
	Width = 60.0000
	Height = 20.0000
)";
	BOOST_CHECK_EQUAL(expectedString, rectangle.ToString());
}
BOOST_AUTO_TEST_CASE(can_get_top_left_point)
{
	BOOST_CHECK(rectangle.GetTopLeft().x == 200);
	BOOST_CHECK(rectangle.GetTopLeft().y == 100);
}
BOOST_AUTO_TEST_CASE(can_get_width)
{
	double expectedWidth = 60;
	BOOST_CHECK_EQUAL(expectedWidth, rectangle.GetWidth());
}
BOOST_AUTO_TEST_CASE(can_get_height)
{
	double expectedHeight = 20;
	BOOST_CHECK_EQUAL(expectedHeight, rectangle.GetHeight());
}
BOOST_AUTO_TEST_SUITE_END()