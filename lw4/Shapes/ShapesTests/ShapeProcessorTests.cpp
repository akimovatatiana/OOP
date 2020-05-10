#include "stdafx.h"
#include <sstream>
#include <boost/optional.hpp>

#include <boost/algorithm/string/replace.hpp>
#include "../Shapes/ShapeProcessor.h"

using namespace std;
using boost::optional;
using boost::none;

struct ShapeProcessorDependencies
{
	stringstream input;
	stringstream output;
};

struct ShapeProcessorFixture : ShapeProcessorDependencies
{
	CShapeProcessor shapeProcessor;

	ShapeProcessorFixture()
		: shapeProcessor(input, output)
	{
	}
	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(shapeProcessor.HandleCommand());
		BOOST_CHECK(input.eof());
		shapeProcessor.Info();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};
BOOST_FIXTURE_TEST_SUITE(Shape_processor, ShapeProcessorFixture)

BOOST_AUTO_TEST_CASE(if_invalid_command_sent_handle_command_should_return_false)
{
	input << "invalid command";
	BOOST_CHECK(!shapeProcessor.HandleCommand());
}

BOOST_AUTO_TEST_CASE(can_add_line_segment_to_shapes_list)
{
	string expectedOutput = R"(Line segment:
	Area = 0.0000
	Perimeter = 20.3760
	Outline color = #808080
	Start point = (5.25, 10.75)
	End point = (25.1, 15.35)

)";
	VerifyCommandHandling("LineSegment 5.25 10.75 25.1 15.35 808080", expectedOutput);
}

BOOST_AUTO_TEST_CASE(cant_add_line_segment_to_shape_list_with_invalid_arguments_count)
{
	string expectedOutput = R"(Failed to create a line segment.
Usage: LineSegment <start point> <end point> ( <outline color> )
)";
	VerifyCommandHandling("LineSegment 5.25 10.75 25.1 15.35 15.12 808080", expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_add_triangle_to_shapes_list)
{
	string expectedOutput = R"(Triangle:
	Area = 6.0000
	Perimeter = 13.3006
	Outline color = #000000
	Fill color = #ffffff
	Vertex1 = (-2, 3)
	Vertex2 = (4, 3)
	Vertex3 = (2, 5)

)";
	VerifyCommandHandling("Triangle -2 3 4 3 2 5 000000 ffffff", expectedOutput);
}

BOOST_AUTO_TEST_CASE(cant_add_triangle_to_shape_list_with_invalid_arguments_count)
{
	string expectedOutput = R"(Failed to create a triangle.
Usage: Triangle <vertex1> <vertex2> <vertex3> ( <outline color> <fill color> )
)";
	VerifyCommandHandling("Triangle -2 3 4 3 2 5 6 000000 ffffff", expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_add_circle_to_shapes_list)
{
	string expectedOutput = R"(Circle:
	Area = 5026.5482
	Perimeter = 251.3274
	Outline color = #000000
	Fill color = #ffffff
	Center = (10, 9)
	Radius = 40.0000

)";
	VerifyCommandHandling("Circle 10 9 40 000000 ffffff", expectedOutput);
}

BOOST_AUTO_TEST_CASE(cant_add_circle_to_shape_list_with_invalid_arguments_count)
{
	string expectedOutput = R"(Failed to create a circle.
Usage: Circle <center point> <radius> ( <outline color> <fill color> )
)";
	VerifyCommandHandling("Circle 10 9 40 20 000000 ffffff", expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_add_rectangle_to_shapes_list)
{
	string expectedOutput = R"(Rectangle:
	Area = 1200.0000
	Perimeter = 160.0000
	Outline color = #000000
	Fill color = #ffffff
	Top left = (200, 100)
	Width = 60.0000
	Height = 20.0000

)";
	VerifyCommandHandling("Rectangle 200 100 60 20 000000 ffffff", expectedOutput);
}

BOOST_AUTO_TEST_CASE(cant_add_rectangle_to_shape_list_with_invalid_arguments_count)
{
	string expectedOutput = R"(Failed to create a rectangle.
Usage: Rectangle <top left point> <width> <height> ( <outline color> <fill color> )
)";
	VerifyCommandHandling("Rectangle 200 100 60 20 51 000000 ffffff", expectedOutput);
}

BOOST_AUTO_TEST_CASE(can_get_shape_with_min_perimeter)
{
	input << "Circle 10 9 40 000000 ffffff" << endl
		<< "Rectangle 200 100 60 20 000000 ffffff";
	while (!input.eof())
	{
		shapeProcessor.HandleCommand();
	}
	shapeProcessor.GetShapeWithMinPerimeter();
	string expectedOutput = R"(Shape with min perimeter is Rectangle:
	Area = 1200.0000
	Perimeter = 160.0000
	Outline color = #000000
	Fill color = #ffffff
	Top left = (200, 100)
	Width = 60.0000
	Height = 20.0000

)";
	BOOST_CHECK_EQUAL(output.str(), expectedOutput);
}
BOOST_AUTO_TEST_CASE(cant_get_shape_with_min_perimeter_if_shape_list_is_empty_should_print_message)
{
	shapeProcessor.GetShapeWithMinPerimeter();
	BOOST_CHECK_EQUAL(output.str(), "Failed to get the shape with min perimeter. Shapes list is empty.\n");
}

BOOST_AUTO_TEST_CASE(can_get_shape_with_max_area)
{
	input << "Circle 10 9 40 000000 ffffff" << endl
		<< "Rectangle 200 100 60 20 000000 ffffff";
	while (!input.eof())
	{
		shapeProcessor.HandleCommand();
	}
	shapeProcessor.GetShapeWithMaxArea();
	string expectedOutput = R"(Shape with max area is Circle:
	Area = 5026.5482
	Perimeter = 251.3274
	Outline color = #000000
	Fill color = #ffffff
	Center = (10, 9)
	Radius = 40.0000

)";
	BOOST_CHECK_EQUAL(output.str(), expectedOutput);
}
BOOST_AUTO_TEST_CASE(cant_get_shape_with_max_area_if_shape_list_is_empty_should_print_message)
{
	shapeProcessor.GetShapeWithMaxArea();
	BOOST_CHECK_EQUAL(output.str(), "Failed to get the shape with max area. Shapes list is empty.\n");
}
BOOST_AUTO_TEST_SUITE_END()
