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


	//TODO: Ensure we can traverse the graph
	Module *temp = &(topModule->modules.at(0));
	while (temp != NULL)
	{
		cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
		temp->PrintModule();
		temp = temp->getOutputs().next;
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