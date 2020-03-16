// Каждый элемент массива должен быть умножен на минимальный элемент исходного массива
#include "vector.h"

vector<float> GetVector(istream& stream)
{
	cout << ENTRY_STR << endl;
	string str;
	getline(stream, str);
	istringstream strNumbers(str);
	float number;
	vector<float> vecNumbers;
	while (strNumbers >> number)
	{
		vecNumbers.push_back(number);
	}
	return vecNumbers;
	//return { std::istream_iterator<float>(stream), std::istream_iterator<float>() };
}

void MultiplyByMinNumber(vector<float>& vector)
{
	if (!vector.empty())
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
}

void SortNumbers(vector<float>& vector)
{
	sort(vector.begin(), vector.end());
}

void PrintNumbers(vector<float>& vector)
{
	//cout << fixed << setprecision(PRECISION);
	copy(vector.begin(), vector.end(), ostream_iterator<float>(cout, " "));
	cout << endl;
}