#pragma once

#include <iostream>
#include <string>
#include "Module.h"

using namespace std;

class IOWire {
	private:
		string name;
		string type;
		Module *prev;
		Module *next;
	public:
		IOWire();
		IOWire(string name, string type);

		string printIOWire();
};