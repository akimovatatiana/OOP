#include "HTMLDecode.h"

string ReadHTML(istream& stream)
{
	/*string html;
	string line;
	while (getline(stream, line))
	{
		html.append(line);
		html.append("\n");
	}*/
	string html;
	getline(stream, html);
	return html;
}

string Replace(string& htmlString, const string& replacedCh, const string& searchString)
{
	if (htmlString.empty())
	{
		return htmlString;
	}
	string result;
	size_t position = 0;
	while (position != string::npos)
	{
		size_t foundPosition = htmlString.find(searchString, position);
		result.append(htmlString, position, foundPosition - position);
		if (foundPosition != string::npos)
		{
			result.append(replacedCh);
			position = foundPosition + searchString.size();
		}
		else
		{
			break;
		}
	}
	return result;
}

string HtmlDecode(const string& html)
{
	string resString = html;
	for (auto& htmlEntity : HTML_OBJECTS)
	{
		resString = Replace(resString, htmlEntity.first, htmlEntity.second);
	}
	return resString;
}
