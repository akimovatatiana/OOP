#include "HTMLDecode.h"

int main()
{
	string html = ReadHTML(cin);
	cout << HtmlDecode(html) << endl;
	return 0;
}