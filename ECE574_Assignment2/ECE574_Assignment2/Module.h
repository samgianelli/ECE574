#pragma once

#include <string>;

using namespace std;

class Module
{
	private:
		string operation;
		string input1;
		string input2;
		string output;
		float delay;
	public:
		Module();
		Module(string operation, string input1, string input2, string output);
};