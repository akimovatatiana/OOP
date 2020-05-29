// FindMaxEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sportsman.h"
#include "FindMaxEx.h"

using namespace std; 

Sportsman GetSportsman(const string& inputString)
{
	std::istringstream ss(inputString);
	Sportsman sportsman;
	string name[3];
	ss >> name[0] >> name[1] >> name[2] >> sportsman.height >> sportsman.weight;
	sportsman.name = name[0] + ' ' + name[1] + ' ' + name[2]; 
	
	if (!ss)
	{
		throw std::runtime_error("Invalid string. Usage: <surname> <first name <middle name> <height> <weight>\n");
	}
	
	return sportsman;
}

vector<Sportsman> InitSportsmen(istream& stream)
{
	vector<Sportsman> sportsmen;
	string input;
	while (getline(stream, input))
	{
		try
		{
			sportsmen.push_back(GetSportsman(input));
		}
		catch (exception const& e)
		{
			cout << e.what();
		}
	}
	return sportsmen;
}

void PrintMaxWeight(ostream& output, const vector<Sportsman>& sportsmen)
{
	Sportsman sportsmanWithMaxWeight;
	if (FindMax(sportsmen, sportsmanWithMaxWeight, IsWeightLess))
	{
		output << "Sportsman with max weight is " << sportsmanWithMaxWeight.name << endl
			<< "Weight: " << sportsmanWithMaxWeight.weight << endl
			<< "Height: " << sportsmanWithMaxWeight.height << endl;
	}
}

void PrintMaxHeight(ostream& output, const vector<Sportsman>& sportsmen)
{
	Sportsman sportsmanWithMaxHeight;
	if (FindMax(sportsmen, sportsmanWithMaxHeight, IsHeightLess))
	{
		output << "Sportsman with max height is " << sportsmanWithMaxHeight.name << endl
			<< "Weight: " << sportsmanWithMaxHeight.weight << endl
			<< "Height: " << sportsmanWithMaxHeight.height << endl;
	}
}

int main()
{
	cout << "Enter sportsman surname, first name, middle name, height and weight. Example: Ivanov Ivan Ivanovich 185 80.25" << endl;
	vector<Sportsman> sportsmen = InitSportsmen(cin);
	PrintMaxWeight(cout, sportsmen);
	PrintMaxHeight(cout, sportsmen);
	return 0;
}