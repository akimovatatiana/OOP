#include "Header-test.h"
#include "vector/vector.h"

TEST_CASE("Proccesing an empty vector")
{
	vector<float> empty;
	MultiplyByMinNumber(empty);
	CHECK(empty.empty());
}

TEST_CASE("Multipling vector on zero")
{
	vector<float> testVector = { 0, 2, 3, 4 };
	vector<float> resVector = { 0, 0, 0, 0 };
	MultiplyByMinNumber(testVector);
	CHECK(testVector == resVector);
}

TEST_CASE("Proccesing vector of one element")
{
	vector<float> testVector = { 4 };
	vector<float> resVector = { 16 };
	MultiplyByMinNumber(testVector);
	CHECK(testVector == resVector);
}

TEST_CASE("Proccesing vector with repeating values")
{
	vector<float> testVector = { 2, 2, 2, 2 };
	vector<float> resVector = { 4, 4, 4, 4 };
	MultiplyByMinNumber(testVector);
	CHECK(testVector == resVector);
}

TEST_CASE("Prossesing usual vectors")
{
	vector<float> testVector = { 9.3f, 5, -2, 6.8f };
	vector<float> res1Vector = { -18.6f, -10, 4, -13.6f };
	vector<float> res2Vector = { -18.6f, -13.6f, -10, 4 };

	//Multipying elements of vector on its min element
	MultiplyByMinNumber(testVector);
	CHECK(testVector == res1Vector);

	//Sorting elements of vector
	SortNumbers(testVector);
	CHECK(testVector == res2Vector);
	
}