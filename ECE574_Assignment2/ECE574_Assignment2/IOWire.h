#pragma once

#include <iostream>
#include <string>
#include "Module.h"

using namespace std;

class IOWire {
	private:
		string name;
		string type;
		

	public:
		Module *prev;
		Module *next;
		IOWire::IOWire();
		IOWire::IOWire(string name, string type);

		string IOWire::printIOWire();

};