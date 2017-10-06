#pragma once

#include <vector>
#include <string>;

using namespace std;

class Module
{
	private:
		string operation;
		vector<string> inputs;
		string output;
		float delay;
	public:
		Module();
		Module(string operation, vector<string> inputs, string output);
		void PrintModule();
};