// Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
#include "vector.h"

vector<float> ReadNumbers(istream& stream)
{
	cout << "Enter an array of numbers separated by spaces:" << endl;
	float number;
	vector<float> numbers;

	while (stream >> number)
	{
		numbers.push_back(number);
	}
	return numbers;
}

void MultiplyByMinNumber(vector<float>& vector)
{
	float min = *min_element(vector.begin(), vector.end());
	for (size_t i = 0; i < vector.size(); ++i)
	{
		if (vector[i] != 0)
		{
			vector[i] *= min;
		}
	}
}

void SortNumbers(vector<float>& vector)
{
	sort(vector.begin(), vector.end());
}

void PrintNumbers(vector<float>& vector)
{
	copy(vector.begin(), vector.end(), ostream_iterator<float>(cout, " "));
	cout << endl;
}