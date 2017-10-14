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
		topModule->addModule(Parser::parseOperation(line, *topModule));
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
		// if statement removes commas between outputs
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
		// if statement removes commas between wires
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = IOWire::IOWire(bufferName, type);
		wires.push_back(bufferWire);
	}
	return wires;
}

Module Parser::parseOperation(string operationString, TopModule &topModule)
{
	//d = a + b
	std::string dummy;			// Use this whenever you want to ignore a character in string stream
	std::string operatorChar;
	std::string inputChar1;
	std::string inputChar2;
	std::string inputChar3;
	std::string outputChar;
	vector<string> inputs;
	std::vector<IOWire> inputWires;
	IOWire outputWire;
	std::stringstream ss(operationString);
	Module opModule;
	
	ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3;

	inputWires.push_back(topModule.findInputWire(inputChar1));
	if (inputChar2.compare("\0") != 0) { inputWires.push_back(topModule.findInputWire(inputChar2)); }
	if (inputChar3.compare("\0") != 0) { inputWires.push_back(topModule.findInputWire(inputChar3)); }
	
	outputWire = topModule.findOutputWire(outputChar);

	if (operatorChar.compare(ADD) == 0) {
		opModule = Module("ADD", inputWires, outputWire, ADD_L);
	}
	else if(operatorChar.compare(SUB) == 0) {
		opModule = Module("SUB", inputWires, outputWire, ADD_L);
	}
	else if(operatorChar.compare(MUL) == 0) {
		opModule = Module("MUL", inputWires, outputWire, MUL_L);
	}
	else if(operatorChar.compare(GT) == 0) {
		opModule = Module("GT", inputWires, outputWire, COMP_L);
	}
	else if(operatorChar.compare(LT) == 0) {
		opModule = Module("LT", inputWires, outputWire, COMP_L);
	}
	else if(operatorChar.compare(EQ) == 0) {
		opModule = Module("EQ", inputWires, outputWire, COMP_L);
	}
	else if(operatorChar.compare(SEL) == 0) {
		opModule = Module("MUX", inputWires, outputWire, SEL_L);
	}
	else if(operatorChar.compare(SHR) == 0) {
		opModule = Module("SHR", inputWires, outputWire, SHR_L);
	}
	else if(operatorChar.compare(SHL) == 0) {
		opModule = Module("SHL", inputWires, outputWire, SHL_L);
	}
	else if(operatorChar.compare(DIV) == 0) {
		opModule = Module("DIV", inputWires, outputWire, DIV_L);
	}
	else if(operatorChar.compare(MOD) == 0) {
		opModule = Module("MOD", inputWires, outputWire, MOD_L);
	}
	else  {
		opModule = Module("REG", inputWires, outputWire, 0);   // TODO: Find Reg latency
	}
	return opModule;
}
