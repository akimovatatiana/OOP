#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iomanip>

using namespace std;

const string ENTRY_STR = "Enter numbers separeted by spaces:";
const string EMPTY_VECTOR = "Vector is empty.";
//const int PRECISION = 3;

void SortNumbers(vector<float>& vector);
vector<float> GetVector(istream& stream);
void MultiplyByMinNumber(vector<float>& vector);
void PrintNumbers(vector<float>& vector);
