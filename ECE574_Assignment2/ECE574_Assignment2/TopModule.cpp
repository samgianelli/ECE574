#include "TopModule.h"

TopModule::TopModule()
{
	this->inputs = vector<IOWire>(0);
	this->outputs = vector<IOWire>(0);
	this->wires = vector<IOWire>(0);
	this->modules = vector<Module>(0);
}

void TopModule::setInputs(vector<IOWire> &inputs)
{
	this->inputs.insert(this->inputs.end(), inputs.begin(), inputs.end());
	return;
}

void TopModule::setOutputs(vector<IOWire> &outputs)
{
	this->outputs.insert(this->outputs.end(), outputs.begin(), outputs.end());
	return;
}

void TopModule::setWires(vector<IOWire> &wires)
{
	this->wires.insert(this->wires.end(), wires.begin(), wires.end());
	return;
}

void TopModule::addModule(Module module)
{
	this->modules.push_back(module);
}

void TopModule::printInputs()
{
	unsigned int i = 0;

	for (i = 0; i < this->inputs.size(); i++)
	{
		cout << this->inputs.at(i).printIOWire();
	}
}