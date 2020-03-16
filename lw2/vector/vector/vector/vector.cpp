#include "vector.h"

int main()
{
	vector<float> vector = ReadNumbers(cin);
	MultiplyByMinNumber(vector);
	SortNumbers(vector);
	PrintNumbers(vector);
	return 0;
}