#include "Module.h"

Module::Module()
{
	/*
		string operation;
		vector<string> inputs;
		string output;
		float delay;
	*/
	this->operation = "";
	//this->inputs = vector<string>(0);
	this->output = "";
	this->delay = 0;
}

Module::Module(string operation, vector<string> inputs, string output, float delay)
{
	cout << "In module overloaded constructor" << endl;
	cout << "Creating " << operation << " module" << endl;
	cout << "\t output: " << output << " delay: " << delay << endl;

	this->operation = operation;
	this->inputs = inputs;
	this->output = output;
	this->delay = delay;
}

void Module::PrintModule()
{

}