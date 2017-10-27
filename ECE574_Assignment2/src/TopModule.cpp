#include "TopModule.h"

TopModule::TopModule()
{
	this->inputs = vector<IOWire>(0);
	this->outputs = vector<IOWire>(0);
	this->wires = vector<IOWire>(0);
	this->registers = vector<IOWire>(0);
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

void TopModule::setRegisters(vector<IOWire> registers)
{
	this->registers.insert(this->registers.end(), registers.begin(), registers.end());
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

	return NULL;
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

	return NULL;
}

IOWire* TopModule::findOutputRegister(string wireName)
{
	unsigned int i = 0;

	for (i = 0; i < this->registers.size(); i++)
	{
		if (this->registers.at(i).getName().compare(wireName) == 0)
		{
			return &(this->registers.at(i));
		}
	}
	//cout << "No Module register found for: " << wireName << endl;

	return NULL;
}

void TopModule::printInputs(ofstream& circuitFile)
{
	unsigned int i = 0;

	circuitFile << "\tinput clk, rst;" << endl;
	for (i = 0; i < this->inputs.size(); i++)
	{
		circuitFile << "\tinput " << this->inputs.at(i).printIOWire() << ";" << endl;
	}
}

void TopModule::printOutputs(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		circuitFile << "\toutput " << this->outputs.at(i).printIOWire() << ";" << endl;
	}

}

void TopModule::printWires(ofstream& circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->wires.size(); i++)
	{
		circuitFile << "\twire " << this->wires.at(i).printIOWire() << ";" << endl;
	}
}

void TopModule::printRegisters(ofstream & circuitFile)
{
	unsigned int i = 0;

	for (i = 0; i < this->registers.size(); i++)
	{
		circuitFile << "\registers " << this->registers.at(i).printIOWire() << ";" << endl;
	}
}

void TopModule::addWire(IOWire& wire)
{
	this->wires.push_back(wire);
}

void TopModule::printModuleName(ofstream& circuitFile, string CircuitName)
{
	if (CircuitName.substr(0, 5) == "474a_" || CircuitName.substr(0, 5) == "574a_") {
		CircuitName.erase(0, 5);
	}
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

	circuitFile << "module " << CircuitName << inputOutputList << endl << endl;
}

void TopModule::printModules(ofstream& circuitFile) {
	unsigned int i = 0;

	for (i = 0; i < this->modules.size(); i++)
	{
		circuitFile << "\t";
		this->modules.at(i).PrintModuleStatement(circuitFile, i);
	}

}

double TopModule::findInputDelay(Module module)
{
	vector<double> inputDelays;
	unsigned int i = 0;

	for (i = 0; i < module.getInputs().size(); i++)
	{
		if (module.getInputs().at(i)->prev == NULL)
		{
			inputDelays.push_back(0);
		}
		else {
			inputDelays.push_back(findInputDelay(*module.getInputs().at(i)->prev));
		}
	}

	double largestDelay = 0;
	for (i = 0; i < inputDelays.size(); i++)
	{
		if (inputDelays.at(i) > largestDelay)
		{
			cout << inputDelays.at(i) << endl;
			largestDelay = inputDelays.at(i);
		}
	}
	return largestDelay + module.getDelay();
}

void TopModule::findCriticalPath()
{
	vector<Module> outputModules;
	double totalDelay = 0;
	unsigned int i = 0;

	for (i = 0; i < this->outputs.size(); i++)
	{
		outputModules.push_back(*this->outputs.at(i).prev);
	}

	for (i = 0; i < outputModules.size(); i++)
	{
		cout << "Critical path for output " << i << endl;
		double delay = findInputDelay(outputModules.at(i));
		if (delay > totalDelay)
		{
			totalDelay = delay;
		}
	}

	cout << "$$$$$$$$$$ CRITICAL PATH : " << totalDelay << "  $$$$$$$$$$$$$$" << endl;
	//return totalDelay;
}
