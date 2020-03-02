#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include "flipbyte.h"

using namespace std;

const int BIT = 8;
const int MAX_BYTE = 255;
const int ARGC = 2;
const string NO_BYTE = "There is no byte number entered";
const string INVALID_ARGS = "Invalid arguments count. Usage: flipbyte.exe <byte>";
const string WRONG_BYTE = "The byte number is not in range [0, 255]";
const string NO_DIGIT = "Error: unknown number";

void ReverseByte(int byteNumber)
{
	int flippedByte = 0;
	for (int i = 0; i < BIT; i++)
	{
		int bitMask = (1 << (BIT - 1 - i));
		if ((byteNumber & bitMask) != 0)
		{
			flippedByte |= (1 << i);
		}
	}
	cout << flippedByte << endl;
}

int main(int argc, char* argv[])
{
	if (argc != ARGC)
	{
		cout << INVALID_ARGS << endl;
		return 1;
	}

	string inputString = argv[1];
	if (inputString.empty())
	{
		cout << NO_BYTE << endl;
		return 1;
	}

	for (size_t i = 0; i < inputString.length(); i++)
	{
		if (isalpha(inputString[i]))
		{
			cout << NO_DIGIT << endl;
			return 1;
		}
	}

	int byteNumber = stoi(inputString);
	if (byteNumber < 0 || byteNumber > MAX_BYTE)
	{
		cout << WRONG_BYTE << endl;
		return 1;
	}
	ReverseByte(byteNumber);
	return 0;
}







