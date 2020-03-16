#include "Header-test.h"
#include "primeNumbers/primeNumbers.h"

TEST_CASE("Generate set when upperBound is less than 1")
{
	set<int> requiredSet = {};
	CHECK(GeneratePrimeNumbersSet(-1) == requiredSet);
}

TEST_CASE("Generate set when upperBound is 0")
{
	set<int> requiredSet = {};
	CHECK(GeneratePrimeNumbersSet(0) == requiredSet);
} 

TEST_CASE("Generate set when upperBound is 1")
{
	set<int> requiredSet = {};
	CHECK(GeneratePrimeNumbersSet(1) == requiredSet);
}

TEST_CASE("Generate set when upperBound is 2")
{
	set<int> requiredSet = { 2 };
	CHECK(GeneratePrimeNumbersSet(2) == requiredSet);
}

TEST_CASE("Generate set when upperBound is 100")
{
	set<int> requiredSet = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
		37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	CHECK(GeneratePrimeNumbersSet(100) == requiredSet);
}

/*TEST_CASE("Generate set when upperBound is max")
{
	int requiredSize = 5761455;
	CHECK(GeneratePrimeNumbersSet(100000000).size() == requiredSize);
} */
