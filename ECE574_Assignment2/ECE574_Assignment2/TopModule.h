#pragma once
#include <iostream>
#include <vector>
#include "Module.h"
#include "IOWire.h"

using namespace std;

class TopModule {
	private:
		float criticalPathDelay;
	public:
		vector<Module> modules;
		vector<IOWire> inputs;
		vector<IOWire> outputs;
		vector<IOWire> wires;

		TopModule::TopModule();

		void TopModule::setInputs(vector<IOWire> inputs);
		void TopModule::setOutputs(vector<IOWire> outputs);
		void TopModule::setWires(vector<IOWire> wires);
		void TopModule::addModule(Module module);
		IOWire* TopModule::findInputWire(string wireName);
		IOWire* TopModule::findOutputWire(string wireName);

		void TopModule::printInputs();
};
