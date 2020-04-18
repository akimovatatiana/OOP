#include "TVSet.h"
#include "Header.h"
#include "RemoteControl.h"

using namespace std;
int main()
{
	CTVSet tv;
	CRemoteControl remoteControl(tv, cin, cout);

	while ((!cin.eof() && !cin.fail()))
	{
		cout << "Enter command: ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}