#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Parser.h"

using namespace std;

vector<string> readNetlist(string fileName);
void writeToFile(string circuitName, TopModule *topModule);
void makeOutputFile(string circuitName, TopModule *topModule);

int main(int argc, char* argv[]) // Will add input arguments in at end of project
{
	cout << argv[0] << endl;
	/*
	if (argc != 3)
	{
		cout << "Error, incorrect number of input arguments." << endl << endl;
		cout << "Usage: dpgen netlistFile verilogFile" << endl;
		cout << "\tnetlistFile - The path to the netlist you wish to convert." << endl;
		cout << "\tverilogFile - The path to for the output verilogFile" << endl;
		return 0;
	}
	*/
	//vector<string> circuits = { "474a_circuit1", "474a_circuit2", "474a_circuit3", "474a_circuit4", "474a_circuit5", "574a_circuit6", "574a_circuit7", "574a_circuit8" };
	vector<string> circuits; //= { argv[1] };
	circuits.push_back("test_if1.c");
	map<string, vector<double>> m;
	for (int i = 0; i < 5; i++)
	{
		m["REG"].push_back(1); //= { 2.616, 2.644, 2.879, 3.061, 3.602, 3.966 };
		m["ADD"].push_back(1); //= { 2.704, 3.713, 4.924, 5.638, 7.270, 9.566 };
		m["SUB"].push_back(1); //= { 3.024, 3.412, 4.890, 5.569, 7.253, 9.566 };
		m["MUL"].push_back(1); //= { 2.438, 3.651, 7.453, 7.811, 12.395, 15.354, };
		m["COMP"].push_back(1); //= { 3.031, 3.934, 5.949, 6.256, 7.264, 8.416 };
		m["MUX"].push_back(1); //= { 4.083, 4.115, 4.815, 5.623, 8.079, 8.766 };
		m["SHR"].push_back(1); //= { 3.644, 4.007, 5.178, 6.460, 8.819, 11.095 };
		m["SHL"].push_back(1); //= { 3.614, 3.980, 5.152, 6.549, 8.565, 11.220 };
		m["DIV"].push_back(1); //= { 0.619, 2.144, 15.439, 33.093, 86.312, 243.233 };
		m["MOD"].push_back(1); //= { 0.758, 2.149, 16.078, 35.563, 88.142, 250.583 };
		m["INC"].push_back(1); //= { 1.792, 2.218, 3.111, 3.471, 4.347, 6.200 };
		m["DEC"].push_back(1); //= { 1.792, 2.218, 3.108, 3.701, 4.685, 6.503 };
	}
	

	for (string circuitName : circuits) {
		unsigned int i = 0;
		vector<string> netlistContents;
		TopModule *topModule = new TopModule();
		netlistContents = readNetlist(circuitName);
		if (netlistContents.size() == 0) {
			cout << "Cannot open file or empty file: " << circuitName << endl;
			return 1;
		}
		vector<string> input_output_reg;

		if (Parser::parseContent(netlistContents, topModule, m) == -1) {
			cout << "Error: Couldn't parse a line. Check the netlist for errors. Exiting." << endl;
			return 1;
		}

		int latency = 6;

		//Module *temp = new Module();
		//temp = &(topModule->modules.at(1));
		topModule->findCriticalPath();
		topModule->calculateTimeFrames(latency);
		for (i = 0; i < topModule->modules.size(); i++)
		{
			topModule->forceSchedule(latency);
			for (int j = 0; j < topModule->modules.size(); j++)
			{
				//cout << topModule->modules.at(j)->getOperation() << " [" << topModule->modules.at(j)->getTimeFrame().at(0) << ", " <<  topModule->modules.at(j)->getTimeFrame().at(1) << "]" << endl;
			}
		}

		for (int j = 0; j < topModule->modules.size(); j++)
			{
				cout << topModule->modules.at(j)->getOperation() << " [" << topModule->modules.at(j)->getTimeFrame().at(0) << ", " <<  topModule->modules.at(j)->getTimeFrame().at(1) << ", " << topModule->modules.at(j)->getTimeFrame().at(2) << "]" << endl;
			}


		//topModule->forceSchedule(latency);
		//topModule->populateGraph(latency);

		// Write to the .v file
		makeOutputFile(/*argv[2]*/"output.v", topModule);

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

void makeOutputFile(string circuitName, TopModule *topModule) {
	int maxSize = 0;

	for (Module* a : topModule->modules) {
		if (a->getTimeFrame().at(0) > maxSize) {
			maxSize = a->getTimeFrame().at(0);
		}
	}
	maxSize = maxSize + 2; // Since we also have a wait state and a final state
	cout << "MaxSize: " << maxSize << " " << ceil(log2(maxSize)) << endl;
	ofstream circuitFile;
	circuitFile.open(circuitName);

	topModule->printModuleName(circuitFile, "HLSM ");
	circuitFile << "\tinput Clk, Rst, Start;" << endl;
	circuitFile << "\toutput reg Done;" << endl;
	circuitFile << "\treg [" << ceil(log2(maxSize)) << ":0] Case;" << endl << endl;
	topModule->printInputs(circuitFile);
	topModule->printOutputs(circuitFile);
	topModule->printWires(circuitFile);
	circuitFile << endl << "\tinitial begin" << endl;
	circuitFile << "\t\tDone <= 0;" << endl;
	circuitFile << "\t\tCase <= 0;" << endl;
	circuitFile << "\tend" << endl << endl;
	circuitFile << "\talways @(posedge Clk) begin" << endl;
	circuitFile << "\t\tif (Rst) begin" << endl;
	circuitFile << "\t\t\tDone <= 0;" << endl;
	circuitFile << "\t\t\tCase <= 0;" << endl;
	circuitFile << "\t\tend" << endl << endl;
	circuitFile << "\t\tif (Start && Case == 0) begin" << endl;
	circuitFile << "\t\t\tCase <= Case + 1;" << endl;
	circuitFile << "\t\t\tDone <= 0;" << endl;
	circuitFile << "\t\tend" << endl;
	
	for (unsigned int i = 1; i < maxSize - 1; i++) {
		circuitFile << "\t\telse if (Case == " << i << ") begin" << endl;
		for (auto module : topModule->modules) {
			if (i == module->getTimeFrame().at(0)) {
				circuitFile << "\t\t\t" << module->getOperationLine() << ";" << endl;
			}
		}
		circuitFile << "\t\t\tCase <= Case + 1;" << endl;
		circuitFile << "\t\tend" << endl;
	}
	circuitFile << "\t\telse if (Case == " << maxSize - 1 << ") begin" << endl;
	circuitFile << "\t\t\tDone <= 1;" << endl;
	circuitFile << "\t\t\tCase <= 0;" << endl;
	circuitFile << "\t\tend" << endl;
	circuitFile << "\tend" << endl << endl;
	circuitFile << "endmodule" << endl;
	circuitFile.close();
}