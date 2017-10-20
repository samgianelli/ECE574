#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "Module.h"


class Module;

using namespace std;

class IOWire {
	private:
		string name;
		string type;
		int bitWidth;
		

	public:
		Module *prev;
		vector<Module*> next;

		IOWire::IOWire();
		IOWire::IOWire(string name, string type);

		void IOWire::setNext(vector<Module*> next);
		void IOWire::addNext(Module *next);
		void IOWire::setPrev(Module *prev);
		string IOWire::getName();
		string IOWire::getType();
		int IOWire::getBitWidth();

		string IOWire::printIOWire();
		string IOWire::printBitWidth();


};