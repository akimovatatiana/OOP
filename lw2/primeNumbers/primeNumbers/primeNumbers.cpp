// primeNumbers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "primeNumbers.h"
#include <ctime>

int main(int argc, char* argv[])
{
	if (argc != ARGC)
	{
		cout << INVALID_ARGC << endl;
		return 0;
	}

	int upperBound = atoi(argv[1]);
	if (upperBound < 1 || upperBound > MAX_BOUND)
	{
		cout << INVALID_UPPER_BOUND << endl;
		return 0;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	cout << primeNumbers.size() << endl;
	//PrintPrimeNumbers(primeNumbers);
	
	cout << '\n' << clock() << "ms" <<endl; // время работы программы
	return 0;
}



