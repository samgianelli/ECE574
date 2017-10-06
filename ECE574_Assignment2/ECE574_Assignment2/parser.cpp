#include "Parser.h"

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
	cout << "test operation: " << operationString << endl;
}
