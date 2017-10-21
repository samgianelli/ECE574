#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"

using namespace std;

vector<string> readNetlist(string fileName);
void writeToFile(string circuitName, TopModule *topModule);

int main() // Will add input arguments in at end of project
{
	vector<string> circuits = { "474a_circuit1", "474a_circuit2", "474a_circuit3", "474a_circuit4", "474a_circuit5", "574a_circuit6", "574a_circuit7", "574a_circuit8" };
	//vector<string> circuits = { "474a_circuit1" };
	for (string circuitName : circuits) {
		unsigned int i = 0;
		vector<string> netlistContents;
		TopModule *topModule = new TopModule();
		netlistContents = readNetlist(circuitName + ".txt");

		for (i = 0; i < netlistContents.size(); i++)
		{
			Parser::parseLine(netlistContents.at(i), topModule);
		}

		for (i = 0; i < topModule->wires.size(); i++)
		{
			//cout << topModule->wires.at(i).next->getOperation() << endl;
			// TODO Fix, this was causing a crash with circuit 3
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

		// Write to the .v file
		writeToFile(circuitName, topModule);
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

void writeToFile(string circuitName, TopModule *topModule) {
	ofstream circuitFile;
	circuitFile.open(circuitName + ".v");
	cout << endl << endl;
	topModule->printModuleName(circuitFile, circuitName);
	topModule->printInputs(circuitFile);
	topModule->printOutputs(circuitFile);
	topModule->printWires(circuitFile);
	circuitFile << endl;
	topModule->printModules(circuitFile);
	circuitFile << "\nendmodule" << endl << endl;
	circuitFile.close();
}