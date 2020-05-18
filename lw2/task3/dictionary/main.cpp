#include "stdafx.h"
#include "dictionary.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	if (argc != ARGC)
	{
		cout << WRONG_ARGC << endl;
		return 1;
	}

	string dictionaryFile = argv[1];

	Dictionary dictionary;
	ReadDictionary(dictionaryFile, dictionary);

	bool changeDictionary = ProcessInput(dictionary);
	if (changeDictionary)
	{
		RecordToFile(dictionaryFile, dictionary);
	}
	return 0;
}
