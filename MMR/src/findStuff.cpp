#include "findStuff.h"

MMR::MMR()
{

}

void MMR::Mean(vector<int> v)
{
	mean = 0;
	for (int i = 0; i < v.size(); i++)
		mean += v[i];
	cout << "Mean: " << mean / v.size() << endl;
}

void MMR::Median(vector<int> v)
{
	sort(v.begin(), v.end());
	if (v.size() % 2 == 0) {
		Total = v[v.size() / 2];
	}
	else{
		Total = v[v.size() / 2 + 0.5];
	}	
	cout << "Median: " << Total << endl;
}

void MMR::Mode(vector<int> v)
{
	sort(v.begin(), v.end());
	number = v[0];
	mode = number;
	count = 1;
	countMode = 1;
	for (int i = 1; i < v.size(); i++)
	{
		if (v[i] == number)
		{
			count++;
		}
		else
		{
			if (count > countMode)
			{
				countMode = count;
				mode = number;
			}
			count = 1;
			number = v[i];
		}
	}

	cout << "Mode: " << mode << endl;
}

void MMR::Range(vector<int> v)
{
	oldTotal = v[0];
	Total = v[0];
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < oldTotal)
			oldTotal = v[i];
		if (v[i] > Total)
			Total = v[i];
	}
	cout << "Range: " << Total - oldTotal << endl;
}

MMR::~MMR()
{
}