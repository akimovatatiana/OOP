#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

const array<pair<string, string>, 5> HTML_OBJECTS = { {
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "&", "&amp;" }
} };

string ReadHTML(istream& stream);
string Replace(string& htmlString, const string& replacedCh, const string& searchString);
string HtmlDecode(const string& html);