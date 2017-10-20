#include "TopModule.h"

TopModule::TopModule()
{
	this->inputs = vector<IOWire>(0);
	this->outputs = vector<IOWire>(0);
	this->wires = vector<IOWire>(0);
	this->modules = vector<Module>(0);
}

void TopModule::setInputs(vector<IOWire> inputs)
{
	this->inputs.insert(this->inputs.end(), inputs.begin(), inputs.end());
	return;
}

void TopModule::setOutputs(vector<IOWire> outputs)
{
	this->outputs.insert(this->outputs.end(), outputs.begin(), outputs.end());
	return;
}

void TopModule::setWires(vector<IOWire> wires)
{
	this->wires.insert(this->wires.end(), wires.begin(), wires.end());
	return;
}

void TopModule::addModule(Module module)
{
	this->modules.push_back(module);
}

IOWire* TopModule::findInputWire(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->inputs.size(); i++)
	{
		if (this->inputs.at(i).getName().compare(wireName) == 0)
		{
			return &(this->inputs.at(i));
		}
 	}

	for (i = 0; i < this->wires.size(); i++)
	{
		if (this->wires.at(i).getName().compare(wireName) == 0)
		{
			return &(this->wires.at(i));
		}
	}

	cout << "No Module input found for: " << wireName << endl;

	return new IOWire();
}

IOWire* TopModule::findOutputWire(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		if (this->outputs.at(i).getName().compare(wireName) == 0)
		{
			return &(this->outputs.at(i));
		}
	}

	for (i = 0; i < this->wires.size(); i++)
	{
		if (this->wires.at(i).getName().compare(wireName) == 0)
		{
			return &(this->wires.at(i));
		}
	}

	cout << "No Module output found for: " << wireName << endl;

	return new IOWire();
}

void TopModule::printInputs()
{
	unsigned int i = 0;

	cout << "\tinput clk, rst;" << endl;
	for (i = 0; i < this->inputs.size(); i++)
	{
		cout << "\tinput " << this->inputs.at(i).printIOWire() << endl;
	}
}

void TopModule::printOutputs()
{
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		cout << "\toutput " << this->outputs.at(i).printIOWire() << endl;
	}

}

void TopModule::printWires()
{
	unsigned int i = 0;

	for (i = 0; i < this->wires.size(); i++)
	{
		cout << "\twire " << this->wires.at(i).printIOWire() << endl;
	}
}

void TopModule::printModuleName()
{
	string CircuitName = "Circuit1";
	string inputOutputList = "(clk, rst, ";
	unsigned int i;

	for (i = 0; i < this->inputs.size(); i++)
	{
		inputOutputList += this->inputs.at(i).getName() + ", ";
		//cout << this->wires.at(i).printIOWire() << endl;
	}
	for (i = 0; i < this->outputs.size(); i++)
	{
		if (i != (this->outputs.size() - 1)) {
			inputOutputList += this->outputs.at(i).getName() + ", ";
		}
		else {
			inputOutputList += this->outputs.at(i).getName() + ");";
		}
			//cout << this->wires.at(i).printIOWire() << endl;
	}

	cout << "module " << CircuitName << inputOutputList << endl << endl;
}

void TopModule::printModules() {
	unsigned int i = 0;

	for (i = 0; i < this->modules.size(); i++)
	{
		cout << "\t";
		this->modules.at(i).PrintModuleStatement(i);
	}

}
