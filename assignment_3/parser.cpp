#include "Parser.h"

int Parser::parseLine(string line, TopModule * topModule, map<string, vector<double>> m)
{
	istringstream lineStream(line);
	string identifier;
	Module *temp = new Module();
	lineStream >> identifier;
	
	if (identifier.compare(INPUT) == 0)
	{
		topModule->setInputs(Parser::parseInput(line));
	}
	else if (identifier.compare(OUTPUT) == 0)
	{
		topModule->setOutputs(Parser::parseOutput(line));
	}
	else if (identifier.compare(WIRE) == 0)
	{
		topModule->setWires(Parser::parseWire(line));
	}
	else if (identifier.compare(REGISTER) == 0 || identifier.compare(VARIABLE) == 0)
	{
		topModule->setRegisters(Parser::parseRegister(line));
		topModule->setWires(Parser::parseRegister(line));

	}
	//All other lines must be operators, filter out whitespace and comments
	else if (identifier.compare(EMPTY) != 0 && identifier.substr(0,2).compare(COMMENT) != 0)
	{
		temp = Parser::parseOperation(line, *topModule, m);
		//cout << "Temp is: " << temp->getOperation() << endl;
		if (temp->getOperation().compare(ERROR) == 0) {
			cout << "Error in parseLine" << endl;
			return -1; // report error
		}
		else {
			topModule->addModule(temp);
		}
		
	}

	return 0; // return no error
}

int Parser::parseContent(vector<string> lines, TopModule * topModule, map<string, vector<double>> m)
{

	for (int i = 0; i < lines.size(); i++)
	{
		istringstream lineStream(lines.at(i));
		string identifier;
		lineStream >> identifier;
		int j = 0;
		
		/*
		Right now, just creates a vector of computations if true, and a vector of computations if false. Will have to create the operations, and
		then connect the outputs to the muxes according to the names of the inputs. Will need to then rename the outputs to {var_name}True or {var_name}False
		and have the output of the mux be {var_name}.
		*/
		if (identifier.compare(IF) == 0)
		{
			i = ifFinder(i, lines, topModule, m) + 1;
		}
		else {
			if (Parser::parseLine(lines.at(i), topModule, m) == -1) {
				return -1;
			}
		}
	}


}

int Parser::ifFinder(int index, vector<string> lines, TopModule * topModule, map<string, vector<double>> m)
{
	cout << "Called ifFinder " << index << endl;
	//vector<string> trueComputations;
	//vector<string> falseComputations;
	map<int, string> trueComputations;
	map<int, string> falseComputations;

	int j;
	string elseIdentifier = "";
	stringstream variable(lines.at(index));
	string if_dummy, parenthesis_dummy, ifVariable;
	variable >> if_dummy >> parenthesis_dummy >> ifVariable;
	cout << "Variable in if statement is: " << ifVariable << endl;
	for (j = index + 1; j < lines.size(); j++) {
		stringstream lineStream2(lines.at(j));
		string nextIdentifier;
		lineStream2 >> nextIdentifier;
		if (nextIdentifier.compare("}") == 0) {
			cout << "have " << trueComputations.size() << " statements in if" << endl;
			index = j + 1;
			stringstream lineStream3(lines.at(index));
			lineStream3 >> elseIdentifier;
			break;
		}
		else if (nextIdentifier.compare(EMPTY) == 0 || nextIdentifier.substr(0, 2).compare(COMMENT) == 0) {
			// If it is a empty line or a comment
			continue;
		}
		else if (nextIdentifier.compare(IF) == 0) {
			j = ifFinder(j, lines, topModule, m);
		}
		else
		{
			//trueComputations.push_back(lines.at(j));
			trueComputations[j] = lines.at(j);
			cout << "IF: " << lines.at(j) << endl;
			// make wires for true
		}
	}
	if (elseIdentifier.compare(ELSE) == 0) {
		cout << "WE HAVE AN ELSE" << endl;
		for (j = index + 1; j < lines.size(); j++) {
			stringstream lineStream2(lines.at(j));
			string nextIdentifier;
			lineStream2 >> nextIdentifier;
			if (nextIdentifier.compare("}") == 0) {
				cout << "have " << falseComputations.size() << " statements in else" << endl;
				cout << "Returning with else" << j << endl;
				break;
			}
			else if (nextIdentifier.compare(EMPTY) == 0 || nextIdentifier.substr(0, 2).compare(COMMENT) == 0) {
				// If it is a empty line or a comment
				continue;
			}
			else if (nextIdentifier.compare(IF) == 0) {
				j = ifFinder(j, lines, topModule, m);
			}
			else
			{
				//falseComputations.push_back(lines.at(j));
				falseComputations[j] = lines.at(j);
				cout << "ELSE: " << lines.at(j) << endl;
			}
		}
	}
	else {
		cout << "Returning because no else " << j << endl;		
		//return j - 1;
		/*
		Here, we are going to have get the false inputs of the mux from actual outside of the if_statement. Either before or after.
		*/
	}
	
	cout << endl;
	vector<IOWire*> trueWires;
	vector<IOWire*> falseWires;
	bool inBoth = false;

	// See if they have any terms that are in both of them. 
	for (auto& operationLine1 : trueComputations) {
		inBoth = false;
		stringstream inputStream1(operationLine1.second);
		string outputName1;
		inputStream1 >> outputName1;
		IOWire* output1 = topModule->findOutputWire(outputName1);
		for (auto& operationLine2 : falseComputations) {
			stringstream inputStream2(operationLine2.second);
			string outputName2;
			inputStream2 >> outputName2;
			IOWire* output2 = topModule->findOutputWire(outputName2);
			if (outputName1 == outputName2) {
				inBoth = true;
				cout << output1->getName() << " "  << output2->getName() << endl;
				operationLine1.second.replace(operationLine1.second.find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_True =");
				operationLine2.second.replace(operationLine2.second.find(outputName2 + " ="), string(outputName2 + " =").length(), outputName2 + "_False =");

				// Make new wires and add them to the list of wires
				IOWire* trueWire = new IOWire(outputName1 + "_True", output1->getType());
				IOWire* falseWire = new IOWire(outputName1 + "_False", output2->getType());
				topModule->addWire(*trueWire);
				topModule->addWire(*falseWire);

				// Make the modules and wire
				Module* trueModule = parseOperation(operationLine1.second, *topModule, m);
				Module* falseModule = parseOperation(operationLine2.second, *topModule, m);
				trueWire->setPrev(trueModule);
				falseWire->setPrev(falseModule);
				topModule->addModule(trueModule);
				topModule->addModule(falseModule);

				// Creating the Mux
				vector<IOWire*> inputWires = {trueWire, falseWire, topModule->findInputWire(ifVariable)};
				IOWire* outputWire = topModule->findOutputWire(outputName1);
				string operationString = outputName1 + " = " + ifVariable + " ? " + outputName1 + "_True" + " : " + outputName1 + "_False";
				Module* mux = new  Module("MUX", inputWires, outputWire, m["MUX"], operationString);
				topModule->addModule(mux);
				
				cout << endl;
			}
		}
		if (!inBoth) {
			for (int i = 0; i < lines.size(); i++) {
				stringstream inputStream2(lines.at(i));
				string outputName2;
				inputStream2 >> outputName2;
				IOWire* output2 = topModule->findOutputWire(outputName2);
				if (outputName1 == outputName2 && i != operationLine1.first) {
					if (i < operationLine1.first) {
						cout << "WE FOUND THE MATCH BEFORE FOR " << outputName1 << endl;
						// Create the True module and wire and the false wire
						operationLine1.second.replace(operationLine1.second.find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_True =");
						IOWire* trueWire = new IOWire(outputName1 + "_True", output1->getType());
						IOWire* falseWire = new IOWire(outputName1 + "_False", output2->getType());
						falseWire->setNext(topModule->findOutputWire(outputName1)->next);
						falseWire->setPrev(topModule->findOutputWire(outputName1)->prev);
						topModule->addWire(*falseWire);
						topModule->addWire(*trueWire);

						Module* trueModule = parseOperation(operationLine1.second, *topModule, m);
						trueWire->setPrev(trueModule);
						topModule->addModule(trueModule);
						
						// Creating the mux
						vector<IOWire*> inputWires = { trueWire, falseWire, topModule->findInputWire(ifVariable) };
						IOWire* outputWire = topModule->findOutputWire(outputName1);
						string operationString = outputName1 + " = " + ifVariable + " ? " + outputName1 + "_True" + " : " + outputName1 + "_False";
						Module* mux = new  Module("MUX", inputWires, outputWire, m["MUX"], operationString);
						topModule->addModule(mux);

					}
					else {
						cout << "WE FOUND THE MATCH AFTER FOR " << outputName1 << endl;
						// Create the True and False modules and wires
						operationLine1.second.replace(operationLine1.second.find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_True =");
						lines.at(i).replace(lines.at(i).find(outputName1 + " ="), string(outputName1 + " =").length(), outputName1 + "_True =");
						
						IOWire* trueWire = new IOWire(outputName1 + "_True", output1->getType());
						IOWire* falseWire = new IOWire(outputName1 + "_False", output2->getType());
						topModule->addWire(*trueWire);
						topModule->addWire(*falseWire);

						Module* trueModule = parseOperation(operationLine1.second, *topModule, m);
						Module* falseModule = parseOperation(lines.at(i), *topModule, m);
						trueWire->setPrev(trueModule);
						falseWire->setPrev(falseModule);
						topModule->addModule(trueModule);
						topModule->addModule(falseModule);

						// Creating the Mux
						vector<IOWire*> inputWires = { trueWire, falseWire, topModule->findInputWire(ifVariable) };
						IOWire* outputWire = topModule->findOutputWire(outputName1);
						string operationString = outputName1 + " = " + ifVariable + " ? " + outputName1 + "_True" + " : " + outputName1 + "_False";
						Module* mux = new  Module("MUX", inputWires, outputWire, m["MUX"], operationString);
						topModule->addModule(mux);
						//lines.erase(lines.begin() + i);

					}
					break;
				}
			}
		}
	}
	
	for (IOWire* trueIOWire : trueWires) {
		for (IOWire* falseIOWire : falseWires) {
			if (trueIOWire == falseIOWire) {
				//Module* newMux = new Module("MUX", inputWires, outputWire, m["MUX"], operationString);
			}
		}
	}

	return j;
}

vector<IOWire> Parser::parseInput(string inputString)
{
	//cout << "test input: " << inputString << endl;
	
	stringstream inputStream(inputString);
	vector<IOWire> inputs;
	IOWire bufferInput;
	string bufferName;
	string type;
	string dummy;

	inputStream >> dummy >> type;

	while (inputStream >> bufferName)
	{
		// if statement removes commas between inputs
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferInput = IOWire(bufferName, type);
		inputs.push_back(bufferInput);
	}
	return inputs;
}

vector<IOWire> Parser::parseOutput(string outputString)
{
	//cout << "test output: " << outputString << endl;

	stringstream outputStream(outputString);
	vector<IOWire> outputs;
	IOWire bufferOutput;
	string bufferName;
	string type;
	string dummy;

	outputStream >> dummy >> type;

	while (outputStream >> bufferName)
	{
		// if statement removes commas between outputs
		if (!isalpha(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferOutput = IOWire(bufferName, type);
		outputs.push_back(bufferOutput);
	}
	return outputs;
}

vector<IOWire> Parser::parseWire(string wireString)
{
	//cout << "test wire: " << wireString << endl;

	stringstream wireStream(wireString);
	vector<IOWire> wires;
	IOWire bufferWire;
	string bufferName;
	string type;
	string dummy;

	wireStream >> dummy >> type;

	while (wireStream >> bufferName)
	{
		// if statement removes commas between wires
		if (!isalnum(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = IOWire(bufferName, type);
		wires.push_back(bufferWire);
	}
	return wires;
}

vector<IOWire> Parser::parseRegister(string registerString)
{
	//cout << "test register: " << registerString << endl;

	stringstream registerStream(registerString);
	vector<IOWire> registers;
	IOWire bufferWire;
	string bufferName;
	string type;
	string dummy;

	registerStream >> dummy >> type;

	while (registerStream >> bufferName)
	{
		// if statement removes commas between wires
		if (!isalnum(bufferName.back()))
		{
			bufferName = bufferName.substr(0, bufferName.length() - 1);
		}
		bufferWire = IOWire(bufferName, type);
		registers.push_back(bufferWire);
	}
	return registers;
}

Module* Parser::parseOperation(string operationString, TopModule &topModule, map<string, vector<double>> m)
{
	//d = a + b
	std::string dummy;			// Use this whenever you want to ignore a character in string stream
	std::string operatorChar;
	std::string inputChar1;
	std::string inputChar2;
	std::string inputChar3;
	std::string outputChar;
	vector<string> inputs;
	std::vector<IOWire*> inputWires;
	IOWire* outputWire;
	IOWire* outputWire2;
	IOWire* tempInput = NULL;
	std::stringstream ss(operationString);
	Module *opModule = NULL;
	
	ss >> outputChar >> dummy >> inputChar1 >> operatorChar >> inputChar2 >> dummy >> inputChar3;

	inputWires.push_back(topModule.findInputWire(inputChar1));
	if (inputChar2.compare("\0") != 0 && inputChar2.compare("1") != 0) 
	{ 
		tempInput = topModule.findInputWire(inputChar2);
		if (tempInput == NULL) {
			opModule = new Module("ERROR"); // This was easier than messing with what the function returned
			return opModule;
		}
		inputWires.push_back(tempInput); 
	}
	if (inputChar3.compare("\0") != 0) 
	{ 
		tempInput = topModule.findInputWire(inputChar3);
		if (tempInput == NULL) {
			opModule = new Module("ERROR"); // This was easier than messing with what the function returned
			return opModule;
		}
		inputWires.push_back(tempInput); 
	}
	
	outputWire = topModule.findOutputRegister(outputChar);
	/*if (outputWire != NULL) {
		if (operatorChar.compare("\0") == 0) {
			outputWire = topModule.findOutputWire(outputChar);
			opModule = new Module("REG", inputWires, outputWire, m["REG"], operationString);
			return opModule;
		}
		else {
			outputWire2 = new IOWire(outputWire->getName() + "_0", outputWire->getType());
			
			if (operatorChar.compare(ADD) == 0) {
				if (inputChar2 == "1") {
					opModule = new Module("INC", inputWires, outputWire2, m["INC"], operationString);
				}
				else {
					opModule = new Module("ADD", inputWires, outputWire2, m["ADD"], operationString);
				}
			}
			else if (operatorChar.compare(SUB) == 0) {
				if (inputChar2 == "1") {
					opModule = new Module("DEC", inputWires, outputWire2, m["DEC"], operationString);
				}
				else {
					opModule = new Module("SUB", inputWires, outputWire2, m["SUB"], operationString);
				}
			}
			else if (operatorChar.compare(MUL) == 0) {
				opModule = new Module("MUL", inputWires, outputWire2, m["MUL"], operationString);
			}
			else if (operatorChar.compare(GT) == 0) {
				opModule = new Module("GT", inputWires, outputWire2, m["COMP"], operationString);
			}
			else if (operatorChar.compare(LT) == 0) {
				opModule = new Module("LT", inputWires, outputWire2, m["COMP"], operationString);
			}
			else if (operatorChar.compare(EQ) == 0) {
				opModule = new Module("EQ", inputWires, outputWire2, m["COMP"], operationString);
			}
			else if (operatorChar.compare(SEL) == 0) {
				opModule = new Module("MUX", inputWires, outputWire2, m["MUX"], operationString);
			}
			else if (operatorChar.compare(SHR) == 0) {
				opModule = new Module("SHR", inputWires, outputWire2, m["SHR"], operationString);
			}
			else if (operatorChar.compare(SHL) == 0) {
				opModule = new Module("SHL", inputWires, outputWire2, m["SHL"], operationString);
			}
			else if (operatorChar.compare(DIV) == 0) {
				opModule = new Module("DIV", inputWires, outputWire2, m["DIV"], operationString);
			}
			else if (operatorChar.compare(MOD) == 0) {
				opModule = new Module("MOD", inputWires, outputWire2, m["MOD"], operationString);
			}
//			outputWire2->setPrev(opModule);
			topModule.addModule(opModule);
			outputWire = topModule.findOutputWire(outputChar);
			vector<IOWire*> temp;
			temp.push_back(outputWire2);
			opModule = new Module("REG", temp, outputWire, m["REG"], operationString);
//			outputWire2->addNext(opModule);
			topModule.addWire(*outputWire2);
			return opModule;
		}
	}*/
	outputWire = topModule.findOutputWire(outputChar);
	if (outputWire == NULL) {
		//cout << "WARNING: OUTPUT OR WIRE NOT IN OUTPUT OF MODULE" << endl;
		opModule = new Module("ERROR"); // This was easier than messing with what the function returned
		return opModule;
	}
	if (operatorChar.compare(ADD) == 0) {
		if (inputChar2 == "1") {
			opModule = new Module("INC", inputWires, outputWire, m["INC"], operationString);
		}
		else {
			opModule = new Module("ADD", inputWires, outputWire, m["ADD"], operationString);
		}
	}
	else if(operatorChar.compare(SUB) == 0) {
		if (inputChar2 == "1") {
			opModule = new Module("DEC", inputWires, outputWire, m["DEC"], operationString);
		}
		else {
			opModule = new Module("SUB", inputWires, outputWire, m["SUB"], operationString);
		}
	}
	else if(operatorChar.compare(MUL) == 0) {
		opModule = new Module("MUL", inputWires, outputWire, m["MUL"], operationString);
	}
	else if(operatorChar.compare(GT) == 0) {
		opModule = new Module("GT", inputWires, outputWire, m["COMP"], operationString);
	}
	else if(operatorChar.compare(LT) == 0) {
		opModule = new Module("LT", inputWires, outputWire, m["COMP"], operationString);
	}
	else if(operatorChar.compare(EQ) == 0) {
		opModule = new Module("EQ", inputWires, outputWire, m["COMP"], operationString);
	}
	else if(operatorChar.compare(SEL) == 0) {
		opModule = new Module("MUX", inputWires, outputWire, m["MUX"], operationString);
	}
	else if(operatorChar.compare(SHR) == 0) {
		opModule = new Module("SHR", inputWires, outputWire, m["SHR"], operationString);
	}
	else if(operatorChar.compare(SHL) == 0) {
		opModule = new Module("SHL", inputWires, outputWire, m["SHL"], operationString);
	}
	else if(operatorChar.compare(DIV) == 0) {
		opModule = new Module("DIV", inputWires, outputWire, m["DIV"], operationString);
	}
	else if(operatorChar.compare(MOD) == 0) {
		opModule = new Module("MOD", inputWires, outputWire, m["MOD"], operationString);
	}
	else if(operatorChar.compare(REG) == 0) {
		opModule = new Module("REG", inputWires, outputWire, m["REG"], operationString);
	}
	else {
		//cout << "** Unrecognized computation **" << endl;
		opModule = new Module("ERROR"); // This was easier than messing with what the function returned
	}



	return opModule;
}
