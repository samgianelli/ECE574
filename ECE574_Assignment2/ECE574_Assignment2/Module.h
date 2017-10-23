#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "IOWire.h"

class IOWire;

using namespace std;


class Module
{
	private:
		string operation;
		vector<IOWire*> inputs;
		IOWire* output;
		double delay;
		int maxBitWidth;

	public:
		Module::Module();
		Module::Module(string operation, vector<IOWire*> inputs, IOWire *output, vector<double> latency);

		double Module::calculateDelay(vector<double> latency);
		string Module::getOperation();
		vector<IOWire*> Module::getInputs();
		IOWire* Module::getOutputs();
		double Module::getDelay();
		int Module::getMaxBitWidth();
		void Module::PrintModule();
		void Module::PrintModuleStatement(ofstream& circuitFile, int moduleNum);
};