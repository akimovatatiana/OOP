// HttpUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpUrl.h"

using namespace std; 

int main()
{
	string urlString;
	while (!cin.eof() && !cin.fail())
	{
		cout << "Enter URL: ";
		getline(cin, urlString);
		try
		{
			CHttpUrl url(urlString);
			cout << GetInfo(url);
		}
		catch (exception const& e)
		{
			cout << e.what();
		}
		cout << endl;
	}
	return 0;
}

