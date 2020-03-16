#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

const string INVALID_ARGC = "Invalid arguments count. Usage: primeNumbers.exe <upper bound>";
const string INVALID_UPPER_BOUND = "Invalid upper bound. Upper bound must be in [1, 100000000]";
const int ARGC = 2;
const int MIN_PRIME = 2;
const int MAX_BOUND = 100000000;

set<int> GeneratePrimeNumbersSet(int upperBound);
vector<bool> FillVector(int upperBound);
void PrintPrimeNumbers(set<int>& primeNumbersSet);