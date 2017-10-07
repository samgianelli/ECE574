#include "Parser.h"
#include "Module.h"


void Parser::parseLine(string line)
{
	istringstream lineStream(line);
	string identifier;

	lineStream >> identifier;
	
	if (identifier.compare(INPUT) == 0)
	{
		Parser::parseInput(line);
	}
	else if (identifier.compare(OUTPUT) == 0)
	{
		Parser::parseOutput(line);
	}
	else if (identifier.compare(WIRE) == 0)
	{
		Parser::parseWire(line);
	}
	//All other lines must be operators, filter out whitespace and comments
	else if (identifier.compare(EMPTY) != 0 && identifier.substr(0,2).compare(COMMENT) != 0)
	{
		Parser::parseOperation(line);
	}
}

void Parser::parseInput(string inputString)
{
	cout << "test input: " << inputString << endl;
}

void Parser::parseOutput(string outputString)
{
	
	cout << "test output: " << outputString << endl;
}

void Parser::parseWire(string wireString)
{
	cout << "test wire: " << wireString << endl;
}

void Parser::parseOperation(string operationString)
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
	
	
	ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3; 
	if (operatorChar.compare(ADD) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("ADD", inputs, outputChar, ADD_L);
	}
	else if(operatorChar.compare(SUB) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("ADD", inputs, outputChar, ADD_L);
	}
	else if(operatorChar.compare(MUL) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("MUL", inputs, outputChar, MUL_L);
	}
	else if(operatorChar.compare(GT) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("GT", inputs, outputChar, COMP_L);
	}
	else if(operatorChar.compare(LT) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("LT", inputs, outputChar, COMP_L);
	}
	else if(operatorChar.compare(EQ) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("EQ", inputs, outputChar, COMP_L);
	}
	else if(operatorChar.compare(SEL) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		inputs.push_back(inputChar3);
		Module mod("MUX", inputs, outputChar, SEL_L);
	}
	else if(operatorChar.compare(SHR) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("SHR", inputs, outputChar, SHR_L);
	}
	else if(operatorChar.compare(SHL) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("SHL", inputs, outputChar, SHL_L);
	}
	else if(operatorChar.compare(DIV) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("DIV", inputs, outputChar, DIV_L);
	}
	else if(operatorChar.compare(MOD) == 0) {
		inputs.push_back(inputChar1);
		inputs.push_back(inputChar2);
		Module mod("MOD", inputs, outputChar, MOD_L);
	}
	
}
