#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"

using namespace std;

vector<string> readNetlist(string fileName);

int main() // Will add input arguments in at end of project
{
	unsigned int i = 0;
	vector<string> netlistContents;
	TopModule *topModule = new TopModule();
	netlistContents = readNetlist("474a_circuit1.txt");
	
	for (i = 0; i < netlistContents.size(); i++)
	{
		Parser::parseLine(netlistContents.at(i), topModule);
	}

	for (i = 0; i < topModule->wires.size(); i++)
	{
		//cout << topModule->wires.at(i).next->getOperation() << endl;
		if (topModule->wires.at(i).next.at(0) == NULL)
		{
			cout << "NULL NULL NULLY NULL" << endl;
		}
	}

	cout << "*******" << topModule->wires.size() << endl;
	//TODO: Ensure we can traverse the graph
	Module *temp = new Module();
	temp = &(topModule->modules.at(1));
	while (temp != NULL)
	{
		temp->PrintModule();
		if (temp->getOutputs()->next.size() > 0) { temp = temp->getOutputs()->next.at(0); }
		else { break; }
	}

	// Test Print Module statements
	cout << endl << endl;
	for (i = 0; i < topModule->modules.size(); i++)
	{
		topModule->modules.at(i).PrintModuleStatement(i);
	}

}

vector<string> readNetlist(string fileName)
{
	string filePath = "../assignment 2 circuits/" + fileName;
	ifstream netlistFile(filePath);
	vector<string> netlistContents;
	string line;

	if (netlistFile.is_open() && netlistFile.good())
	{
		while (getline(netlistFile, line))
		{
			netlistContents.push_back(line);
		}
		netlistFile.close();
	}

	else cout << "Cannot open file: " << fileName << endl;

	return netlistContents;
}