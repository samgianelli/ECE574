#include "Parser.h"

void Parser::parseLine(string line)
{
	istringstream lineStream(line);
	string identifier;

	lineStream >> identifier;
	
	if (identifier.compare("input") == 0)
	{
		Parser::parseInput(line);
	}
	else if (identifier.compare("output") == 0)
	{
		Parser::parseOutput(line);
	}
	else if (identifier.compare("wire") == 0)
	{
		Parser::parseWire(line);
	}
	else if (identifier.compare("\0") != 0)
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
