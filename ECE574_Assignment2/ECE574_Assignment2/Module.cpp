#include "Module.h"

Module::Module()
{
	this->operation = "";
	this->inputs = vector<IOWire*>(0);
	this->output = new IOWire();
	this->delay = 0;
}

Module::Module(string operation, vector<IOWire*> inputs, IOWire *output, float delay)
{
	cout << "In module overloaded constructor" << endl;
	cout << "Creating " << operation << " module" << endl;
	//cout << "\t output: " << output << " delay: " << delay << endl;

	this->operation = operation;
	this->inputs = inputs;
	this->output = output;
	this->delay = delay;

	int i = 0;
	for (i = 0; i < inputs.size(); i++)
	{
		this->inputs.at(i)->addNext(this);
	}
	this->output->setPrev(this);
}

string Module::getOperation()
{
	return this->operation;
}

vector<IOWire*> Module::getInputs()
{
	return this->inputs;
}

IOWire* Module::getOutputs()
{
	return this->output;
}

float Module::getDelay()
{
	return this->delay;
}

void Module::PrintModule()
{
	cout << "Module Name: " << this->operation << endl;
}

void Module::PrintModuleStatement(int moduleNum)
{
	string inputs;
	string output;
	string statement; 
	unsigned int i = 0;
	
	// Parse/Format input names
	for (i = 0; i < this->inputs.size(); i++)
	{
		inputs += this->inputs.at(i)->getName() + ", ";
	}
	inputs = inputs.substr(0, inputs.length()-2);

	// Pars/Format output name
	output = this->output->getName();

	// Format final output statement
	statement = this->operation + " " + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ");";
	cout << statement << endl;
}