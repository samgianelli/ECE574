#pragma once

#include <iostream>
#include <vector>
#include <string>
//#include "IOWire.h"

using namespace std;


class Module
{
	private:
		string operation;
		vector<string> inputs;
		string output;
		float delay;

	public:
		Module::Module();
		Module::Module(string operation, vector<string> inputs, string output, float delay);
		void Module::PrintModule();
};