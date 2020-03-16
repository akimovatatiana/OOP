#include "primeNumbers.h"

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> primeVector = FillVector(upperBound);
	set<int> primeNumbers;
	for (int i = MIN_PRIME; i <= upperBound; i++)
	{
		if (primeVector[i])
		{
			primeNumbers.emplace(i);
		}
	}
	return primeNumbers;
}

vector<bool> FillVector(int upperBound)
{
	vector<bool> numbers(upperBound + 1, true);
	for (size_t i = MIN_PRIME; i * i < numbers.size(); ++i)
	{
		if (numbers[i])
		{
			for (size_t j = i * i; j < numbers.size(); j += i)
			{
				numbers[j] = false;
			}
		}
	}
	return numbers;
}

void PrintPrimeNumbers(set<int>& primeNumbersSet)
{
	copy(primeNumbersSet.begin(), primeNumbersSet.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}