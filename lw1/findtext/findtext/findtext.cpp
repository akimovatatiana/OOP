#include <iostream>
#include "findtext.h"
#include <fstream>
#include <string>

using namespace std;

const string NOT_FOUND = "Text not found";
const string EMPTY_STRING = "Search string is empty";
const string ERR_OPEN_FILE = "Failed to open input file for reading";
const string INVALID_ARGS = "Invalid arguments count. Usage: findtext.exe <input file> <search string>";

bool searchForString(ifstream& fileToSearch, const string& searchString)
{
	bool stringFound = false;
	string line;
	int i = 1;
	while (!fileToSearch.eof())
	{
		getline(fileToSearch, line);
		if (line.find(searchString) != string::npos)
		{
			cout << i << endl;
			stringFound = true;
		}
		i++;
	}
	return stringFound;
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 3)
	{
		cout << INVALID_ARGS << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);

	if (!inputFile.is_open())
	{
		cout << ERR_OPEN_FILE << endl;
		return 1;
	}

	string searchString = argv[2];
	if (searchString.empty())
	{
		cout << EMPTY_STRING << endl;
		return 1;
	}
	if (!searchForString(inputFile, searchString))
	{
		cout << NOT_FOUND << endl;
		return 1;
	}
	return 0;
}