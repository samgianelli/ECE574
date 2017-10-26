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
	else if (identifier.compare(REGISTER) == 0) 
	{
		topModule->setRegisters(Parser::parseRegister(line));
		topModule->setWires(Parser::parseRegister(line));

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
		bufferInput = IOWire(bufferName, type);
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
		bufferOutput = IOWire(bufferName, type);
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
		bufferWire = IOWire(bufferName, type);
		wires.push_back(bufferWire);
	}
	return wires;
}

vector<IOWire> Parser::parseRegister(string registerString)
{
	cout << "test register: " << registerString << endl;

	stringstream registerStream(registerString);
	vector<IOWire> registers;
	IOWire bufferWire;
	string bufferName;
	string type;
	string dummy;

	registerStream >> dummy >> type;

	while (registerStream >> bufferName)
	{
		// if statement removes commas between wires
		if (!isalnum(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = IOWire(bufferName, type);
		registers.push_back(bufferWire);
	}
	return registers;
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
	IOWire* outputWire2;
	std::stringstream ss(operationString);
	Module *opModule = NULL;
	
	ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3;

	inputWires.push_back(topModule.findInputWire(inputChar1));
	if (inputChar2.compare("\0") != 0 && inputChar2.compare("1") != 0) { inputWires.push_back(topModule.findInputWire(inputChar2)); }
	if (inputChar3.compare("\0") != 0) { inputWires.push_back(topModule.findInputWire(inputChar3)); }
	
	outputWire = topModule.findOutputRegister(outputChar);
	if (outputWire != NULL) {
		if (operatorChar.compare("\0") == 0) {
			outputWire = topModule.findOutputWire(outputChar);
			opModule = new Module("REG", inputWires, outputWire, m["REG"]);
			return *opModule;
		}
		else {
			outputWire2 = new IOWire(outputWire->getName() + "_0", outputWire->getType());
			
			if (operatorChar.compare(ADD) == 0) {
				if (inputChar2 == "1") {
					opModule = new Module("INC", inputWires, outputWire2, m["INC"]);
				}
				else {
					opModule = new Module("ADD", inputWires, outputWire2, m["ADD"]);
				}
			}
			else if (operatorChar.compare(SUB) == 0) {
				if (inputChar2 == "1") {
					opModule = new Module("DEC", inputWires, outputWire2, m["DEC"]);
				}
				else {
					opModule = new Module("SUB", inputWires, outputWire2, m["SUB"]);
				}
			}
			else if (operatorChar.compare(MUL) == 0) {
				opModule = new Module("MUL", inputWires, outputWire2, m["MUL"]);
			}
			else if (operatorChar.compare(GT) == 0) {
				opModule = new Module("GT", inputWires, outputWire2, m["COMP"]);
			}
			else if (operatorChar.compare(LT) == 0) {
				opModule = new Module("LT", inputWires, outputWire2, m["COMP"]);
			}
			else if (operatorChar.compare(EQ) == 0) {
				opModule = new Module("EQ", inputWires, outputWire2, m["COMP"]);
			}
			else if (operatorChar.compare(SEL) == 0) {
				opModule = new Module("MUX", inputWires, outputWire2, m["MUX"]);
			}
			else if (operatorChar.compare(SHR) == 0) {
				opModule = new Module("SHR", inputWires, outputWire2, m["SHR"]);
			}
			else if (operatorChar.compare(SHL) == 0) {
				opModule = new Module("SHL", inputWires, outputWire2, m["SHL"]);
			}
			else if (operatorChar.compare(DIV) == 0) {
				opModule = new Module("DIV", inputWires, outputWire2, m["DIV"]);
			}
			else if (operatorChar.compare(MOD) == 0) {
				opModule = new Module("MOD", inputWires, outputWire2, m["MOD"]);
			}
//			outputWire2->setPrev(opModule);
			topModule.addModule(*opModule);
			outputWire = topModule.findOutputWire(outputChar);
			vector<IOWire*> temp;
			temp.push_back(outputWire2);
			opModule = new Module("REG", temp, outputWire, m["REG"]);
//			outputWire2->addNext(opModule);
			topModule.addWire(*outputWire2);
			return *opModule;
		}
	}
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
		opModule = new Module("REG", inputWires, outputWire, m["REG"]); 
	}



	return *opModule;
}
