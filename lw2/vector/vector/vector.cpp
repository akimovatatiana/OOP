#include "vector.h"

int main()
{
	vector<float> vector = GetVector(cin);
	MultiplyByMinNumber(vector);
	SortNumbers(vector);
	PrintNumbers(vector);
	return 0;
}