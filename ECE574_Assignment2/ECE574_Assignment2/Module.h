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
		vector<IOWire> inputs;
		IOWire output;
		float delay;

	public:
		Module::Module();
		Module::Module(string operation, vector<IOWire> &inputs, IOWire &output, float delay);

		vector<IOWire> Module::getInputs();
		IOWire Module::getOutputs();
		float Module::getDelay();
		void Module::PrintModule();
};