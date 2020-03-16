#include "Header-test.h"
#include "vector/vector.h"

TEST_CASE("")
{
	vector<float> testVector = { 9.3, 5, -2, 6.8 };
	vector<float> res1Vector = { -18.6, -10, 4, -13.6 };
	vector<float> res2Vector = { -2, 5, 6.8, 9.3 };

	SECTION("Multipying elements of vector on its min element")
	{
		MultiplyByMinNumber(testVector);
		CHECK(testVector == res1Vector);
	}
	SECTION("Sorting elements of vector")
	{
		SortNumbers(testVector);
		CHECK(testVector == res2Vector);
	}
}