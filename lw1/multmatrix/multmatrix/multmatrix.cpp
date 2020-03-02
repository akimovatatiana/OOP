#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip> 
#include "multmatrix.h"
using namespace std;

const string ERR_OPEN_FILE = "Failed to open matrix file for reading";
const string INVALID_ARGS = "Invalid arguments count. Usage: findtext.exe <matrix file1> <matrix file2>";
const unsigned int SIZE = 3;
const unsigned int PRECISION = 3;
const unsigned int ARGC = 3;

typedef float matrix3x3[SIZE][SIZE];

bool readFile(const string& fileName, matrix3x3& matrix)
{
	ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		return false;
	}
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			inputFile >> matrix[i][j];
		}
	}
	return true;
}

void multMatrix(const matrix3x3& leftMatrix, const matrix3x3& rightMatrix, matrix3x3& resMatrix)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			float matrixElement = 0;
			for (int k = 0; k < SIZE; k++)
			{
				matrixElement += leftMatrix[i][k] * rightMatrix[k][j];
			}
			resMatrix[i][j] = matrixElement;
		}
	}
}

void printMatrix(matrix3x3& resMatrix)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << fixed << setprecision(PRECISION) << resMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != ARGC)
	{
		cout << INVALID_ARGS << endl;
		return 1;
	}
	matrix3x3 leftMatrix, rightMatrix, resMatrix;

	if (!readFile(argv[1], leftMatrix) || !readFile(argv[2], rightMatrix))
	{
		cout << ERR_OPEN_FILE << endl;
		return 1;
	}
	multMatrix(leftMatrix, rightMatrix, resMatrix);
	printMatrix(resMatrix);
	return 0;
}