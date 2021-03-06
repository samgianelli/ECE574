#include "Module.h"

Module::Module()
{
	this->operation = "";
	this->inputs = vector<IOWire*>(0);
	this->output = new IOWire();
	this->delay = 0;
	this->maxBitWidth = 0;
	this->isSigned = false;
}

Module::Module(string operation) 
{
	this->operation = operation;
	this->inputs = vector<IOWire*>(0);
	this->output = new IOWire();
	this->delay = 0;
	this->maxBitWidth = 0;
	this->isSigned = false;
}

Module::Module(string operation, vector<IOWire*> inputs, IOWire *output, vector<double> latency)
{
	//cout << "In module overloaded constructor" << endl;
	//cout << "Creating " << operation << " module" << endl;
	
	int tempMaxBitWidth = 0;
	unsigned int i = 0;


	this->operation = operation;
	this->inputs = inputs;
	this->output = output;
	this->isSigned = false;
	tempMaxBitWidth = this->output->getBitWidth();

	for (i = 0; i < inputs.size(); i++) // Will set the isUnsigned equal to true of any input or output is unsigned
	{
		this->isSigned |= inputs.at(i)->getSigned();
	}
	this->isSigned |= output->getSigned();

	for (i = 0; i < inputs.size(); i++)
	{
		this->inputs.at(i)->addNext(this);
		if ((inputs.at(i)->getBitWidth() > tempMaxBitWidth) && (operation == "GT" || operation == "LT" || operation == "EQ")) {
			tempMaxBitWidth = inputs.at(i)->getBitWidth();
		}
	}
	if (this->operation == "MUX") {
		tempMaxBitWidth = this->inputs.at(1)->getBitWidth() > this->inputs.at(2)->getBitWidth() ? this->inputs.at(1)->getBitWidth() : this->inputs.at(2)->getBitWidth();
	}

	this->output->setPrev(this);
	this->maxBitWidth = tempMaxBitWidth;
	this->delay = calculateDelay(latency);
	//cout << this->operation << " Created Module with bitwidth: " << this->maxBitWidth << " and latency: " << this->delay << endl;
}

double Module::calculateDelay(vector<double> latency) {
	switch (this->maxBitWidth) {
	case 1:
		return latency.at(0);
	case 2:
		return latency.at(1);
	case 8:
		return latency.at(2);
	case 16:
		return latency.at(3);
	case 32:
		return latency.at(4);
	case 64:
		return latency.at(5);
	default:
		return 200;
	}
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

double Module::getDelay()
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
	string statement = ""; 
	unsigned int i = 0;
	
	// Parse/Format input names
	for (i = 0; i < this->inputs.size(); i++)
	{
		if (this->isSigned) {
			inputs += "$signed(" + this->inputs.at(i)->getName() + "), ";
		}
		else {
			inputs += this->inputs.at(i)->getName() + ", ";
		}
	}
	inputs = inputs.substr(0, inputs.length()-2);
	if (this->operation == "MUX") {
		inputs = this->inputs.at(2)->getName() + ", " + this->inputs.at(1)->getName() + ", " + this->inputs.at(0)->getName();
	}

	// Pars/Format output name
	output = this->output->getName();
	if (this->isSigned) 
	{
		statement = "S";
	}

	// Format final output statement
	// All of the hardcoded things because programming is hard
	if (this->operation == "GT") {
		statement += "COMP #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ", , );";
	}
	else if (this->operation == "LT") {
		statement += "COMP #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", ," + output + ", );";
	}
	else if (this->operation == "EQ") {
		statement += "COMP #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", , ," + output + ");";
	}
	else if (this->operation == "REG") {
		statement += "REG #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", clk, rst, " + output + ");";
	}
	else if (this->operation == "MUX") {
		statement += this->operation + "2x1" + " #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ");";
	}
	else {
		statement += this->operation + " #(" + to_string(this->getMaxBitWidth()) + ")" + this->operation + "_" + to_string(moduleNum) + "(" + inputs + ", " + output + ");";
	}
	circuitFile << statement << endl;
}

int Module::getMaxBitWidth()
{
	return this->maxBitWidth;
}

void Module::setOperation(string operation)
{
	this->operation = operation;
}
