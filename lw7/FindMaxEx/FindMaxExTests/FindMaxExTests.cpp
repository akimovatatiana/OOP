// FindMaxExTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"
#include "../FindMaxEx/Sportsman.h"

using namespace std;

const vector<Sportsman> sportsmans = {
		{"Ivanov Alexey Ivanovich", 180, 75.87},
		{"Lezhina Anna Alexeevna", 165, 48.95},
		{"Alexeev Vladimir Nkolaevich", 182, 74.25},
};

const Sportsman maxValues = { "Lezhina Anna Alexeevna", 182, 75.87 };
const vector<Sportsman> emptyVector;
Sportsman sportsman;

BOOST_AUTO_TEST_SUITE(FindMax_)
BOOST_AUTO_TEST_CASE(with_empty_vector_return_false)
{
	BOOST_CHECK(emptyVector.empty());
	BOOST_CHECK(!FindMax(emptyVector, sportsman, IsNameLess));
	BOOST_CHECK(!FindMax(emptyVector, sportsman, IsHeightLess));
	BOOST_CHECK(!FindMax(emptyVector, sportsman, IsWeightLess));
}
BOOST_AUTO_TEST_CASE(can_find_max_string)
{
	string expectedString = maxValues.name;
	BOOST_CHECK(FindMax(sportsmans, sportsman, IsNameLess));
	BOOST_CHECK(expectedString == sportsman.name);
}
BOOST_AUTO_TEST_CASE(can_find_max_integer)
{
	int expectedInteger = maxValues.height;
	BOOST_CHECK(FindMax(sportsmans, sportsman, IsHeightLess));
	BOOST_CHECK(expectedInteger == sportsman.height);
}
BOOST_AUTO_TEST_CASE(can_find_max_double)
{
	double expectedDouble = maxValues.weight;
	BOOST_CHECK(FindMax(sportsmans, sportsman, IsWeightLess));
	BOOST_CHECK(expectedDouble == sportsman.weight);
}

BOOST_AUTO_TEST_CASE(cant_change_max_value_when_vector_is_empty)
{
	BOOST_CHECK(emptyVector.empty());
	Sportsman newSportsman = sportsman;
	BOOST_CHECK(!FindMax(emptyVector, sportsman, IsHeightLess));
	BOOST_CHECK(sportsman.name == newSportsman.name);
	BOOST_CHECK(sportsman.height == newSportsman.height);
	BOOST_CHECK(sportsman.weight == newSportsman.weight);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FindMax_without_comparator_)
BOOST_AUTO_TEST_CASE(can_find_max_in_double_vector)
{
	vector<double> vec = { 10.23, 1.25, 15.68, 56.21 };
	double maxValue;
	BOOST_CHECK(FindMax(vec, maxValue));
	BOOST_CHECK(maxValue == 56.21);
}
BOOST_AUTO_TEST_CASE(can_find_max_in_float_vector)
{
	vector<float> vec = { 10.23f, 1.25f, 15.68f, 56.21f };
	float maxValue;
	BOOST_CHECK(FindMax(vec, maxValue));
	BOOST_CHECK(maxValue == 56.21f);
}
BOOST_AUTO_TEST_CASE(can_find_max_in_char_vector)
{
	vector<char> vec = { 'a', 'b', 'c', 'd' };
	char maxValue;
	BOOST_CHECK(FindMax(vec, maxValue));
	BOOST_CHECK(maxValue == 'd');
}
BOOST_AUTO_TEST_SUITE_END()