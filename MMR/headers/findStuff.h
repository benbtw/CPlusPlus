#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MMR
{
public:
	MMR();
	void Mean(vector<int>);
	void Median(vector<int>);
	void Range(vector<int>);
	void Mode(vector<int>);
	~MMR();
private:
	int oldTotal;
	int Total;
	int number;
	int mode;
	int count;
	int countMode;
	double mean;
};