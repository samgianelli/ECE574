#include "Module.h"

Module::Module()
{
	this->operation = "";
	this->inputs = vector<IOWire*>(0);
	this->output = new IOWire();
	this->delay = 0;
	this->maxBitWidth = 0;
}

Module::Module(string operation, vector<IOWire*> inputs, IOWire *output, float delay)
{
	cout << "In module overloaded constructor" << endl;
	cout << "Creating " << operation << " module" << endl;
	
	int tempMaxBitWidth = 0;

	this->operation = operation;
	this->inputs = inputs;
	this->output = output;
	this->delay = delay;

	int i = 0;
	for (i = 0; i < inputs.size(); i++)
	{
		this->inputs.at(i)->addNext(this);
		if (inputs.at(i)->getBitWidth() > tempMaxBitWidth) {
			tempMaxBitWidth = inputs.at(i)->getBitWidth();
		}
	}
	if (this->operation == "MUX") {
		tempMaxBitWidth = this->inputs.at(1)->getBitWidth() > this->inputs.at(2)->getBitWidth() ? this->inputs.at(1)->getBitWidth() : this->inputs.at(2)->getBitWidth();
	}

	this->output->setPrev(this);
	this->maxBitWidth = tempMaxBitWidth;
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

void Module::PrintModuleStatement(ofstream& circuitFile, int moduleNum)
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
	if (this->operation == "MUX") {
		inputs = this->inputs.at(2)->getName() + ", " + this->inputs.at(1)->getName() + ", " + this->inputs.at(0)->getName();
	}

	// Pars/Format output name
	output = this->output->getName();

	// Format final output statement
	// All of the hardcoded things because programming is hard
	if (this->operation == "GT") {
		statement = "COMP #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ", , );";
	}
	else if (this->operation == "LT") {
		statement = "COMP #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", ," + output + ", );";
	}
	else if (this->operation == "EQ") {
		statement = "COMP #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", , ," + output + ");";
	}
	else if (this->operation == "REG") {
		statement = "REG #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", clk, rst, " + output + ");";
	}
	else if (this->operation == "MUX") {
		statement = this->operation + "2x1" + " #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ");";
	}
	else {
		statement = this->operation + " #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ");";
	}
	circuitFile << statement << endl;
}

int Module::getMaxBitWidth()
{
	return this->maxBitWidth;
}