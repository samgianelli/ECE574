#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INPUT "input"
#define OUTPUT "output"
#define WIRE "wire"
#define COMMENT "//"
#define EMPTY "\0"
#define ADD "+"
#define SUB "-"
#define MUL "*"
#define GT ">"
#define LT "<"
#define EQ	"=="
#define SEL "?"
#define SHR ">>"
#define SHL "<<"
#define DIV "/"
#define MOD "%"

#define ADD_L 9.566 // As of now just doing 64 bits 
#define SUB_L 9.566
#define MUL_L 15.354
#define COMP_L 8.416
#define SEL_L 8.766
#define SHR_L 11.095
#define SHL_L 11.220
#define DIV_L 243.233
#define MOD_L 250.583


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