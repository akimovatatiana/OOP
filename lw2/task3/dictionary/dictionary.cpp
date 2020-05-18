#include "stdafx.h"
#include "dictionary.h"

using namespace std;

void ReadDictionary(const string& fIn, Dictionary& dictionary)
{
	ifstream inputFile(fIn);
	string inputString, translation;
	char delimeter(DELIMETER);
	while (getline(inputFile, inputString, delimeter))
	{
		getline(inputFile, translation);
		dictionary[inputString] = translation;
	}
}

string ToLowerCase(string inputWord)
{
	transform(inputWord.begin(), inputWord.end(), inputWord.begin(),
		[](unsigned char c) { return tolower(c); });
	return inputWord;
}

string ReadLine()
{
	string inputString;
	getline(cin, inputString);
	return inputString;
}

bool ProcessInput(Dictionary& dictionary)
{
	cout << ">";
	string inputWord = ReadLine();
	bool change = false;
	while (inputWord != END_WORK)
	{
		if (!SearchForTranslation(dictionary, inputWord))
		{
			if (AddTranslation(inputWord, dictionary))
			{
				change = true;
			}
		}
		cout << ">";
		inputWord = ReadLine();
	}
	return change;
}

bool SearchForTranslation(Dictionary& dictionary, const string& searchString)
{
	string lowerCaseString = ToLowerCase(searchString);
	for (const auto& pair : dictionary)
	{
		if (pair.first == lowerCaseString)
		{
			cout << pair.second << endl;
			return true;
		}
		if (pair.second == lowerCaseString)
		{
			cout << pair.first << endl;
			return true;
		}
	}
	return false;
}

bool AddTranslation(const string& inputWord, Dictionary& dictionary)
{
	string translation;
	if (GetTranslation(inputWord, translation))
	{
		InsertInDictionary(dictionary, inputWord, translation);
		cout << "Слово \"" << inputWord << "\" сохранено в словаре как \"" << translation << "\"." << endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool GetTranslation(const string& inputWord, string& translation)
{
	cout << "Неизвестное слово \"" << inputWord << "\". Введите перевод или пустую строку для отказа." << endl;
	cout << ">";
	translation = ReadLine();
	if (translation.empty())
	{
		cout << "Слово \"" << inputWord << "\" проигнорировано." << endl;
		return false;
	}
	return true;
}

void InsertInDictionary(Dictionary& dictionary, const string& inputWord, const string& translation)
{
	string inputWordInLowerCase = ToLowerCase(inputWord);
	pair<string, string> newPair;
	newPair = make_pair(inputWordInLowerCase, translation);
	dictionary.insert(newPair);
}

void RecordToFile(const string& fOut, Dictionary& dictionary)
{
	if (!dictionary.empty())
	{
		cout << SAVE_CHANGES << endl;
		string ch = ReadLine();
		if ((ch == AGREE_SAVE_L) || (ch == AGREE_SAVE_H))
		{
			ofstream dictionaryFile(fOut);
			for (const auto& record : dictionary)
			{
				dictionaryFile << record.first << "-" << record.second << endl;
			}
			cout << SAVED << endl;
		}
		else
		{
			cout << UNSAVED << endl;
		}
	}
}