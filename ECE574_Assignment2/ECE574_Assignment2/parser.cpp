#include "Parser.h"

void Parser::parseLine(string line, TopModule * topModule, map<string, vector<double>> m)
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
		topModule->addModule(Parser::parseOperation(line, *topModule, m));
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
		if (!isalnum(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = IOWire::IOWire(bufferName, type);
		wires.push_back(bufferWire);
	}
	return wires;
}

Module Parser::parseOperation(string operationString, TopModule &topModule, map<string, vector<double>> m)
{
	//d = a + b
	std::string dummy;			// Use this whenever you want to ignore a character in string stream
	std::string operatorChar;
	std::string inputChar1;
	std::string inputChar2;
	std::string inputChar3;
	std::string outputChar;
	vector<string> inputs;
	std::vector<IOWire*> inputWires;
	IOWire* outputWire;
	std::stringstream ss(operationString);
	Module *opModule;
	
	ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3;

	inputWires.push_back(topModule.findInputWire(inputChar1));
	if (inputChar2.compare("\0") != 0 && inputChar2.compare("1") != 0) { inputWires.push_back(topModule.findInputWire(inputChar2)); }
	if (inputChar3.compare("\0") != 0) { inputWires.push_back(topModule.findInputWire(inputChar3)); }
	
	outputWire = topModule.findOutputWire(outputChar);

	if (operatorChar.compare(ADD) == 0) {
		if (inputChar2 == "1") {
			opModule = new Module("INC", inputWires, outputWire, m["INC"]);
		}
		else {
			opModule = new Module("ADD", inputWires, outputWire, m["ADD"]);
		}
	}
	else if(operatorChar.compare(SUB) == 0) {
		if (inputChar2 == "1") {
			opModule = new Module("DEC", inputWires, outputWire, m["DEC"]);
		}
		else {
			opModule = new Module("SUB", inputWires, outputWire, m["SUB"]);
		}
	}
	else if(operatorChar.compare(MUL) == 0) {
		opModule = new Module("MUL", inputWires, outputWire, m["MUL"]);
	}
	else if(operatorChar.compare(GT) == 0) {
		opModule = new Module("GT", inputWires, outputWire, m["COMP"]);
	}
	else if(operatorChar.compare(LT) == 0) {
		opModule = new Module("LT", inputWires, outputWire, m["COMP"]);
	}
	else if(operatorChar.compare(EQ) == 0) {
		opModule = new Module("EQ", inputWires, outputWire, m["COMP"]);
	}
	else if(operatorChar.compare(SEL) == 0) {
		opModule = new Module("MUX", inputWires, outputWire, m["MUX"]);
	}
	else if(operatorChar.compare(SHR) == 0) {
		opModule = new Module("SHR", inputWires, outputWire, m["SHR"]);
	}
	else if(operatorChar.compare(SHL) == 0) {
		opModule = new Module("SHL", inputWires, outputWire, m["SHL"]);
	}
	else if(operatorChar.compare(DIV) == 0) {
		opModule = new Module("DIV", inputWires, outputWire, m["DIV"]);
	}
	else if(operatorChar.compare(MOD) == 0) {
		opModule = new Module("MOD", inputWires, outputWire, m["MOD"]);
	}
	else  {
		opModule = new Module("REG", inputWires, outputWire, m["REG"]);   // TODO: Find Reg latency
	}
	return *opModule;
}
