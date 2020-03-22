#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <Windows.h>
#include <conio.h>
using namespace std;

const int ARGC = 2;
const string ERROR_FILE = "Ошибка открытия файла с названием: ";
const string WRONG_ARGC = "Неправильное количество аргументов: miniDictionary.exe <dictionaryFile>";
const string INSERT_TRANS = "Введите перевод слова:";
const string SAVE_CHANGES = "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
const string AGREE_SAVE_L = "y";
const string AGREE_SAVE_H = "Y";
const string SAVED = "Изменения сохранены. До свидания.";
const string UNSAVED = "Изменения не сохранены. До свидания.";
const string END_WORK = "...";
const char DELIMETER = '-';
typedef map<string, string> Dictionary;

void ReadDictionary(const string& inputFile, Dictionary& dictionary);
bool ProcessInput(Dictionary& dictionary);
bool SearchForTranslation(Dictionary& dictionary, const string& searchString);
bool AddTranslation(const string& inputWord, Dictionary& dictionary);
bool GetTranslation(const string& inputWord, string& translation);
void InsertInDictionary(Dictionary& dictionary, const string& inputWord, const string& translation);
void RecordToFile(const string& outputFile, Dictionary& dictionary);
string ToLowerCase(string inputWord);
string ReadLine();