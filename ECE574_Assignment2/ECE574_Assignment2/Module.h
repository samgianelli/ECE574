#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "IOWire.h"

class IOWire;

using namespace std;


class Module
{
	private:
		string operation;
		vector<IOWire*> inputs;
		IOWire* output;
		float delay;

	public:
		Module::Module();
		Module::Module(string operation, vector<IOWire*> inputs, IOWire *output, float delay);

		string Module::getOperation();
		vector<IOWire*> Module::getInputs();
		IOWire* Module::getOutputs();
		float Module::getDelay();
		void Module::PrintModule();
		void Module::PrintModuleStatement(int moduleNum);
};