#pragma once

using namespace std;
#include <iostream>
#include <vector>
#include <string>

class Module
{
	private:
		string operation;
		vector<string> inputs;
		string output;
		float delay;
	public:
		Module();
		Module(string operation, vector<string> inputs, string output, float delay);
		void PrintModule();
};