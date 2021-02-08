#include <iostream>
using namespace std;

int main()
{
	int num;

	while (true)
	{
		while (cin >> num)
		{
			cout << num;
		}

		if (cin.bad())
		{
			break;
		}

		if (cin.eof())
		{
			break;
		}

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<stream_size>::max(), '\n');
			continue;
		}
	}

	return 0;
}
