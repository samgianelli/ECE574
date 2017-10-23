#pragma once
#include <iostream>
#include <vector>
#include <fstream>
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
		vector<IOWire> registers;

		TopModule::TopModule();

		void TopModule::setInputs(vector<IOWire> inputs);
		void TopModule::setOutputs(vector<IOWire> outputs);
		void TopModule::setWires(vector<IOWire> wires);
		void TopModule::setRegisters(vector<IOWire> registers);
		void TopModule::addModule(Module module);
		IOWire* TopModule::findInputWire(string wireName);
		IOWire* TopModule::findOutputWire(string wireName);

		void TopModule::printInputs(ofstream& circuitFile);
		void TopModule::printOutputs(ofstream& circuitFile);
		void TopModule::printWires(ofstream& circuitFile);
		void TopModule::printRegisters(ofstream& circuitFile);
		void TopModule::printModuleName(ofstream& circuitFile, string CircuitName);
		void TopModule::printModules(ofstream& circuitFile);

};
