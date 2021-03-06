#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Parser.h"

using namespace std;

vector<string> readNetlist(string fileName);
void writeToFile(string circuitName, TopModule *topModule);

int main(int argc, char* argv[]) // Will add input arguments in at end of project
{
	if (argc != 3)
	{
		cout << "Error, incorrect number of input arguments." << endl << endl;
		cout << "Usage: dpgen netlistFile verilogFile" << endl;
		cout << "\tnetlistFile - The path to the netlist you wish to convert." << endl;
		cout << "\tverilogFile - The path to for the output verilogFile" << endl;
		return 0;
	}

	//vector<string> circuits = { "474a_circuit1", "474a_circuit2", "474a_circuit3", "474a_circuit4", "474a_circuit5", "574a_circuit6", "574a_circuit7", "574a_circuit8" };
	vector<string> circuits = { argv[1] };
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
		netlistContents = readNetlist(circuitName);
		if (netlistContents.size() == 0) {
			cout << "Cannot open file or empty file: " << circuitName << endl;
			return 1;
		}

		for (i = 0; i < netlistContents.size(); i++)
		{
			if (Parser::parseLine(netlistContents.at(i), topModule, m) == -1) {
				cout << "Error: Couldn't parse a line. Check the netlist for errors. Exiting." << endl;
				return 1;
			}
		}

		//Module *temp = new Module();
		//temp = &(topModule->modules.at(1));
		topModule->findCriticalPath();

		// Write to the .v file
		writeToFile(argv[2], topModule);

	}
}

vector<string> readNetlist(string fileName)
{
	string filePath = fileName;
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

	return netlistContents;
}

void writeToFile(string circuitName, TopModule *topModule) {
	ofstream circuitFile;
	circuitFile.open(circuitName);
	//cout << endl << endl;
	topModule->printModuleName(circuitFile, circuitName.substr(0, circuitName.size() - 2));
	topModule->printInputs(circuitFile);
	topModule->printOutputs(circuitFile);
	topModule->printWires(circuitFile);
	circuitFile << endl;
	topModule->printModules(circuitFile);
	circuitFile << "\nendmodule" << endl << endl;
	circuitFile.close();
}
