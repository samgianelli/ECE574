#include "TopModule.h"

TopModule::TopModule()
{
	this->inputs = vector<IOWire>(0);
	this->outputs = vector<IOWire>(0);
	this->wires = vector<IOWire>(0);
	this->modules = vector<Module>(0);
}

void TopModule::setInputs(vector<IOWire> _inputs)
{
	cout << "Test1" << endl;
	this->inputs = _inputs;  // THIS LINE IS DYING
	cout << "Test2" << endl;
}

void TopModule::setOutputs(vector<IOWire> outputs)
{
	this->outputs = outputs;
}

void TopModule::printInputs()
{
	unsigned int i = 0;

	for (i = 0; i < this->inputs.size(); i++)
	{
		cout << this->inputs.at(i).printIOWire();
	}
}