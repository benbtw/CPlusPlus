#include "findStuff.h"

int main()
{
	vector<int> vec;
	MMR doFunc;
	string input = "";
	cout << "What Number Would You Like To Add? ";
	cin >> input;
	while (input != "x")
	{
		cout << "Add more(x to end) ";
		cin >> input;
		if (input == "x")
			break;
		vec.push_back(atoi(input.c_str()));
	}
	doFunc.Mean(vec);
	doFunc.Range(vec);
	doFunc.Median(vec);
	doFunc.Mode(vec);
	return 0;
}