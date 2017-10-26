#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Parser.h"

using namespace std;

vector<string> readNetlist(string fileName);
void writeToFile(string circuitName, TopModule *topModule);

int main() // Will add input arguments in at end of project
{
	//vector<string> circuits = { "474a_circuit1", "474a_circuit2", "474a_circuit3", "474a_circuit4", "474a_circuit5", "574a_circuit6", "574a_circuit7", "574a_circuit8" };
	vector<string> circuits = { "474a_circuit5" };
	map<string, vector<double>> m;
	m["REG"] = { 2.616, 2.644, 2.879, 3.061, 3.602, 3.966 };
	m["ADD"] = { 2.704, 3.713, 4.924, 5.638, 7.270, 9.566 };
	m["SUB"] = { 3.024, 3.412, 4.890, 5.569, 7.253, 9.566 };
	m["MUL"] = { 2.438, 3.651, 7.453, 7.811, 12.395, 15.354, };
	m["COMP"] = { 3.031, 3.934, 5.949, 6.256, 7.264, 8.416 };
	m["MUX"] = { 4.083, 4.115, 4.815, 5.623, 8.079, 8.766 };
	m["SHR"] = { 3.644, 4.007, 5.178, 6.460, 8.819, 11.095 };
	m["SHL"] = { 3.614, 3.980, 5.152, 6.549, 8.565, 11.220 };
	m["DIV"] = { 0.619, 2.144, 15.439, 33.093, 86.312, 243.233 };
	m["MOD"] = { 0.758, 2.149, 16.078, 35.563, 88.142, 250.583 };
	m["INC"] = { 1.792, 2.218, 3.111, 3.471, 4.347, 6.200 };
	m["DEC"] = { 1.792, 2.218, 3.108, 3.701, 4.685, 6.503 };

	for (string circuitName : circuits) {
		unsigned int i = 0;
		vector<string> netlistContents;
		TopModule *topModule = new TopModule();
		netlistContents = readNetlist(circuitName + ".txt");

		for (i = 0; i < netlistContents.size(); i++)
		{
			Parser::parseLine(netlistContents.at(i), topModule, m);
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

		topModule->findCriticalPath();

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