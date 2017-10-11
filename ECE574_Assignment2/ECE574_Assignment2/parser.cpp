#include "Parser.h"

void Parser::parseLine(string line, TopModule * topModule)
{
	istringstream lineStream(line);
	string identifier;

	lineStream >> identifier;
	
	if (identifier.compare(INPUT) == 0)
	{
		topModule->setInputs(Parser::parseInput(line));
	}
	else if (identifier.compare(OUTPUT) == 0)
	{
		topModule->setOutputs(Parser::parseOutput(line));
	}
	else if (identifier.compare(WIRE) == 0)
	{
		topModule->setWires(Parser::parseWire(line));
	}
	//All other lines must be operators, filter out whitespace and comments
	else if (identifier.compare(EMPTY) != 0 && identifier.substr(0,2).compare(COMMENT) != 0)
	{
		topModule->addModule(Parser::parseOperation(line));
	}
}

vector<IOWire> Parser::parseInput(string inputString)
{
	cout << "test input: " << inputString << endl;
	
	stringstream inputStream(inputString);
	vector<IOWire> inputs;
	IOWire bufferInput;
	string bufferName;
	string type;
	string dummy;

	inputStream >> dummy >> type;

	while (inputStream >> bufferName)
	{
		// if statement removes commas between inputs
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferInput = IOWire::IOWire(bufferName, type);
		inputs.push_back(bufferInput);
	}
	return inputs;
}

vector<IOWire> Parser::parseOutput(string outputString)
{
	cout << "test output: " << outputString << endl;

	stringstream outputStream(outputString);
	vector<IOWire> outputs;
	IOWire bufferOutput;
	string bufferName;
	string type;
	string dummy;

	outputStream >> dummy >> type;

	while (outputStream >> bufferName)
	{
		// if statement removes commas between inputs
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferOutput = IOWire::IOWire(bufferName, type);
		outputs.push_back(bufferOutput);
	}
	return outputs;
}

vector<IOWire> Parser::parseWire(string wireString)
{
	cout << "test wire: " << wireString << endl;

	stringstream wireStream(wireString);
	vector<IOWire> wires;
	IOWire bufferWire;
	string bufferName;
	string type;
	string dummy;

	wireStream >> dummy >> type;

	while (wireStream >> bufferName)
	{
		// if statement removes commas between inputs
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = IOWire::IOWire(bufferName, type);
		wires.push_back(bufferWire);
	}
	return wires;
}

Module Parser::parseOperation(string operationString)
{
	//d = a + b
	std::string dummy;			// Use this whenever you want to ignore a character in string stream
	std::string operatorChar;
	std::string inputChar1;
	std::string inputChar2;
	std::string inputChar3;
	std::string outputChar;
	std::vector<std::string> inputs;
	std::stringstream ss(operationString);
	Module opModule;
	
	
	ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3; 
	if (operatorChar.compare(ADD) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("ADD", inputs, outputChar, ADD_L);
	}
	else if(operatorChar.compare(SUB) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("ADD", inputs, outputChar, ADD_L);
	}
	else if(operatorChar.compare(MUL) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("MUL", inputs, outputChar, MUL_L);
	}
	else if(operatorChar.compare(GT) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("GT", inputs, outputChar, COMP_L);
	}
	else if(operatorChar.compare(LT) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("LT", inputs, outputChar, COMP_L);
	}
	else if(operatorChar.compare(EQ) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("EQ", inputs, outputChar, COMP_L);
	}
	else if(operatorChar.compare(SEL) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		inputs.push_back(inputChar3);
		opModule = Module("MUX", inputs, outputChar, SEL_L);
	}
	else if(operatorChar.compare(SHR) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("SHR", inputs, outputChar, SHR_L);
	}
	else if(operatorChar.compare(SHL) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("SHL", inputs, outputChar, SHL_L);
	}
	else if(operatorChar.compare(DIV) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("DIV", inputs, outputChar, DIV_L);
	}
	else if(operatorChar.compare(MOD) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		opModule = Module("MOD", inputs, outputChar, MOD_L);
	}
	return opModule;
}
