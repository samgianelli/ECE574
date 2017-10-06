#pragma once
#include <iostream>
#include <sstream>
#include <string>

#define INPUT "input"
#define OUTPUT "output"
#define WIRE "wire"
#define COMMENT "//"
#define EMPTY "\0"

using namespace std;

class Parser
{
	private:

	public:
		static void parseLine(string line);
		static void parseInput(string inputString);
		static void parseOutput(string outputString);
		static void parseWire(string wireString);
		static void parseOperation(string operationString);
};